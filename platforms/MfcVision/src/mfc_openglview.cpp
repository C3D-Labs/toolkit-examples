#include "mfc_openglview.h"
#include "mfc_scenerenderer.h"
#include <tool_enabler.h>
#include <last.h>

VSN_BEGIN_NAMESPACE

namespace MfcVision {

IMPLEMENT_DYNCREATE(COpenGLView, CView)
BEGIN_MESSAGE_MAP(COpenGLView, CView)
    //{{AFX_MSG_MAP(COpenGLView)
    ON_WM_CREATE()
    ON_WM_DESTROY()
    ON_WM_PAINT()
    ON_WM_SIZE()
    ON_WM_SETCURSOR()
    ON_WM_SHOWWINDOW()
    ON_WM_SETFOCUS()
    ON_WM_KILLFOCUS()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
// Конструктор по умолчанию.
// ---
COpenGLView::COpenGLView()
    : m_pSceneRenderer(new CSceneRenderer)
{
}

//-----------------------------------------------------------------------------
// Деструктор OpenGLWidget освобождает созданные ресурсы
// ---
COpenGLView::~COpenGLView()
{
    VSN_DELETE_AND_NULL(m_pSceneRenderer);
}

//-----------------------------------------------------------------------------
//
// ---
void COpenGLView::MakeCurrent()
{
    m_pSceneRenderer->MakeCurrent();
}

//-----------------------------------------------------------------------------
//
// ---
void COpenGLView::DoneCurrent()
{
    m_pSceneRenderer->DoneCurrent();
}

//-----------------------------------------------------------------------------
// Вернуть указатель на источник освешения сцены.
// ---
Light* COpenGLView::GetMainLight() const
{
    return m_pSceneRenderer->GetMainLight();
}

//-----------------------------------------------------------------------------
// Вернуть указатель на Viewport для отображения сцены.
// ---
Viewport* COpenGLView::GetViewport() const
{
    return m_pSceneRenderer->GetViewport();
}

//-----------------------------------------------------------------------------
// Вернуть указатель на содержимое сцены.
// ---
SceneContentPtr COpenGLView::GetSceneContent() const
{
    return m_pSceneRenderer->GetSceneContent();
}

//-----------------------------------------------------------------------------
// Вернуть указатель на содержимое сцены.
// ---
ObjectPickSelection* COpenGLView::GetObjectPickSelection() const
{  
    return m_pSceneRenderer->GetGraphicsView()->GetSceneEngine()->GetObjectPickSelection();
}

//-----------------------------------------------------------------------------
// Вернуть указатель на содержимое сцены
// ---
GraphicsScene* COpenGLView::GetGraphicsScene() const
{
    return m_pSceneRenderer->GetGraphicsScene();
}

//-----------------------------------------------------------------------------
// Функция вызывается после инициализации Vision
// ---
void COpenGLView::InitializeOpenGL()
{
}

//-------------------------------------------------------------------------------
//
// ---
#ifdef _UNICODE
BOOL COpenGLView::Create(wchar_t const * lpszClassName, wchar_t const * lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
    dwStyle = (dwStyle | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS /*| WS_OVERLAPPED*/);
    return CView::Create((LPCTSTR)lpszClassName, (LPCTSTR)lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}
BOOL COpenGLView::Create(unsigned short const * lpszClassName, unsigned short const * lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
    dwStyle = (dwStyle | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPED);
    return CView::Create((LPCTSTR)lpszClassName, (LPCTSTR)lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}
#else
BOOL COpenGLView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
    dwStyle = (dwStyle | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPED);
    return CView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}
#endif

//-----------------------------------------------------------------------------
// Создать окно и захватить ресурсы OpenGL, а также произвести инициализацию Vision
// ---
int COpenGLView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;
    m_pSceneRenderer->DoCreate(m_hWnd);
    InitializeOpenGL();
    return 0;
}

//-----------------------------------------------------------------------------
//
// ---
void COpenGLView::OnDestroy()
{
    m_pSceneRenderer->DoDestroy();
    CView::OnDestroy();
}

//-------------------------------------------------------------------------------
//
// ---
void COpenGLView::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    m_pSceneRenderer->DoDraw();
}

//-----------------------------------------------------------------------------
//
// ---
void COpenGLView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
/*
    if (COpenGLView* pDeactiveGlView = dynamic_cast<COpenGLView*>(pDeactiveView))
    {
        pDeactiveGlView->DoneCurrent();
        pDeactiveGlView->UpdateWindow();
    }

    if (COpenGLView* pActivateGlView = dynamic_cast<COpenGLView*>(pActivateView))
    {
        pActivateGlView->MakeCurrent();
        pActivateGlView->UpdateWindow();
    }
*/
    if (bActivate)
        m_pSceneRenderer->DoPreparingToDisplay();
    else
        m_pSceneRenderer->DoDraw();
    CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

//-----------------------------------------------------------------------------
//
// ---
void COpenGLView::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CView::OnShowWindow(bShow, nStatus);
    if (bShow)
        m_pSceneRenderer->DoPreparingToDisplay();
}

//-----------------------------------------------------------------------------
//
// ---
void COpenGLView::OnDraw(CDC* pDC)
{
    VSN_UNUSED(pDC);
}

//-----------------------------------------------------------------------------
// for translating Windows messages in main message pump
// ---
BOOL COpenGLView::PreTranslateMessage(MSG* pMsg)
{
    long* resul = nullptr;
    m_pSceneRenderer->OnWinEvent(pMsg, resul);
    return CView::PreTranslateMessage(pMsg);
}

//-------------------------------------------------------------------------------
//
// ---
BOOL COpenGLView::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.lpszClass = AfxRegisterWndClass(CS_OWNDC | CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW);
    return CView::PreCreateWindow(cs);
}

//-----------------------------------------------------------------------------
//
// ---
void COpenGLView::OnSize(UINT nType, int cx, int cy)
{
    if (0 >= cx || 0 >= cy || nType == SIZE_MINIMIZED)
        return;
    m_pSceneRenderer->DoResize(cx, cy);
    CView::OnSize(nType, cx, cy);
}

//-----------------------------------------------------------------------------
//
// ---
BOOL COpenGLView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
    ::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
    // let the processing continue - a child window may want to set one of its own
    return FALSE;
}

//-----------------------------------------------------------------------------
//
// ---
void COpenGLView::OnSetFocus(CWnd* pOldWnd)
{
    CView::OnSetFocus(pOldWnd);
    m_pSceneRenderer->DoSetFocus(pOldWnd);
}

//-----------------------------------------------------------------------------
//
// ---
void COpenGLView::OnKillFocus(CWnd* pNewWnd)
{
    CView::OnKillFocus(pNewWnd);
    m_pSceneRenderer->DoKillFocus(pNewWnd);
}

} // namespace MfcVision

VSN_END_NAMESPACE