#include "mfc_exampletools.h"
#include <functional>

VSN_BEGIN_NAMESPACE
namespace MfcVision {

BEGIN_MESSAGE_MAP(CExampleTools, CWnd)
    ON_WM_SIZE()
    ON_WM_CREATE()
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

void CExampleTools::addItem(std::shared_ptr<MFCExampleInputIterface> ptr)
{
    m_items.push_back(ptr);

    if (GetSafeHwnd())
    {
        if (HWND hwnd = ptr->Create(this))
        {
            m_events[hwnd] = std::weak_ptr<MFCExampleInputIterface>(ptr);
            updateLayout();
        }
    }
}

void CExampleTools::updateLayout()
{
    const int border = 4;
    CRect client;
    GetClientRect(client);

    const int w = client.Width();
    int top = border;
    int elHeight = 20;

    for (auto & item : m_items)
        top += item->SetPosition(top, w, elHeight) + 4;
}

void CExampleTools::changeSelect(CWnd * pwnd)
{
    if (pwnd)
    {
        auto it = m_events.find(pwnd->GetSafeHwnd());
        if (it != m_events.end())
        {
            if (auto ptr = it->second.lock())
                ptr->RunCommand();
        }
    }
}

void CExampleTools::OnSize(UINT nType, int cx, int cy)
{
    if(GetSafeHwnd())
        updateLayout();
}

BOOL CExampleTools::OnEraseBkgnd(CDC* pDC)
{
    CRect windRect;
    GetClientRect(windRect);
    CBrush brushWnd;
    brushWnd.CreateSolidBrush(GetSysColor(COLOR_3DFACE));

    pDC->FillRect(windRect, &brushWnd);
    return TRUE;
}

BOOL CExampleTools::OnCreate(LPCREATESTRUCT)
{
    BOOL sucsess = TRUE;

    if (sucsess)
    {
        for( auto & item : m_items )
        {
            if (HWND hwnd = item->Create(this))
                m_events[hwnd] = std::weak_ptr<MFCExampleInputIterface>(item);
        }
    }

    return sucsess;
}

BOOL CExampleTools::OnCommand(WPARAM wParam, LPARAM lParam)
{
    BOOL isOk = FALSE;

    switch (HIWORD(wParam))
    {
    case CBN_SELCHANGE:
        changeSelect(CWnd::FromHandle((HWND)lParam));
        return TRUE;
    }
   
    return CWnd::OnCommand(wParam, lParam);
}

BEGIN_MESSAGE_MAP(ExampleWindow, CFrameWnd)
    ON_WM_SIZE()
    ON_WM_CREATE()
    ON_MESSAGE(WM_ActivateLicense, OnActivateLicense)
END_MESSAGE_MAP()

ExampleWindow::ExampleWindow(ExampleView * pView)
    :m_pView(pView)
{
    Create(NULL, _T("Example window"), WS_OVERLAPPEDWINDOW);
}

ExampleWindow::~ExampleWindow()
{

}

int ExampleWindow::OnCreate(LPCREATESTRUCT)
{
    bool sucsess = true;
    sucsess = sucsess && !!m_licenceWnd.Create(NULL, NULL, WS_CHILD|WS_VISIBLE, { 0,0,1,1 }, this, 0);

    // activate license
    if (sucsess && m_licenceWnd.activateLicense())
        showExampleView();

    return sucsess ? 0 : -1;
}

ExampleInput<int> & ExampleWindow::comboBox(const std::string & label, const std::vector<std::string> & items, int default)
{
    std::shared_ptr<MFCExampleInput<CComboBox, int>> combobox(new MFCExampleInput<CComboBox, int>(label, [items, default](CComboBox& combobox, CWnd * parent){

        bool res = combobox.Create(CBS_DROPDOWNLIST | CBS_SORT | WS_VSCROLL | WS_TABSTOP | WS_VISIBLE, { 0,0,1,1 }, parent, 1) != FALSE;

        if(res)
        {
            for (auto & el : items)
                combobox.AddString(CString(el.c_str()));
        }

        combobox.SetCurSel(default);

        return res;
    }));

    m_inputPanel.addItem(combobox);
    showExampleInput();

    return static_cast<ExampleInput<int>&>(*combobox);
}

void ExampleWindow::OnSize(UINT nType, int cx, int cy)
{
    updateLayout();
}

LRESULT  ExampleWindow::OnActivateLicense(WPARAM, LPARAM)
{
    showExampleView();

    return TRUE;
}

void ExampleWindow::updateLayout()
{
    CRect client;
    GetClientRect(client);

    if (m_pView->GetSafeHwnd())
    {
        const int propertyWidth = m_inputPanel.GetSafeHwnd()? 250 : 0;

        if (propertyWidth > 0)
            m_inputPanel.SetWindowPos(NULL, client.Width() - propertyWidth, 0, propertyWidth, client.Height(), SWP_NOZORDER|SWP_NOREDRAW);

        m_pView->SetWindowPos(NULL, 0, 0, client.Width() - propertyWidth, client.Height(), SWP_NOZORDER|SWP_NOREDRAW);
    }
    else
        m_licenceWnd.SetWindowPos(NULL, 0, 0, client.Width(), client.Height(), SWP_NOZORDER);
}

void ExampleWindow::SetSceneLoader(std::function<void(GraphicsScene * pScene)> callback)
{
    if (m_pView->GetSafeHwnd())
    {
        callback(m_pView->GetGraphicsView()->GetGraphicsScene());
        m_pView->GetViewport()->ZoomToFit(m_pView->GetSceneContent()->GetBoundingBox());
    }
    else
        m_loadSceneCallback = callback;
}

void ExampleWindow::showExampleView()
{
    if (m_pView)
    {
        if (m_pView && !m_pView->GetSafeHwnd())
        {
            CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS, ::LoadCursor(nullptr, IDC_ARROW), nullptr, ::LoadIcon(nullptr, IDI_WINLOGO));
            m_pView->Create(className, NULL, WS_CHILD, CRect{ 0,0,1,1 }, this, 0);

            if (!m_inputPanel.IsEmpty())
                m_inputPanel.Create(NULL, NULL, WS_CHILD | WS_VISIBLE, { 0,0,1,1 }, this, 0);

            if (m_loadSceneCallback)
            {
                m_loadSceneCallback(m_pView->GetGraphicsView()->GetGraphicsScene());
                m_pView->GetViewport()->ZoomToFit(m_pView->GetSceneContent()->GetBoundingBox());
            }
        }

        if (m_licenceWnd.GetSafeHwnd())
            m_licenceWnd.ShowWindow(SW_HIDE);

        if (m_pView->GetSafeHwnd())
        {
            updateLayout();
            m_pView->ShowWindow(SW_SHOW);
        }
    }
}


void ExampleWindow::showExampleInput()
{
    if (!m_inputPanel.GetSafeHwnd() && !m_inputPanel.IsEmpty())
    {
        m_inputPanel.Create(NULL, NULL,  WS_CHILD | WS_VISIBLE, { 0,0,600,600 }, this, 0);
        updateLayout();
    }
}

} // namespace MfcVision
VSN_END_NAMESPACE