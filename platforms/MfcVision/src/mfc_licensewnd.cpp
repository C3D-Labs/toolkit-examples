#include "mfc_licensewnd.h"
#include "tool_enabler.h"
#include <last.h>

VSN_BEGIN_NAMESPACE

namespace MfcVision {

BEGIN_MESSAGE_MAP(LicenceWnd, CWnd)
    ON_WM_SIZE()
    ON_WM_CREATE()
    ON_WM_ERASEBKGND()
    ON_COMMAND(CM_ActivateLicense, OnActivateLicense)
END_MESSAGE_MAP()

LicenceWnd::LicenceWnd()
{}

LicenceWnd::~LicenceWnd()
{

}

int LicenceWnd::OnCreate(LPCREATESTRUCT)
{
    bool sucsess = true;
    sucsess = sucsess && m_signature.Create(WS_CHILD|WS_BORDER|WS_VISIBLE|ES_AUTOHSCROLL, RECT{ 0,0,1,1 }, this, 0);
    sucsess = sucsess && m_key.Create(WS_CHILD|WS_BORDER|WS_VISIBLE|ES_AUTOHSCROLL, RECT{ 0,0,1,1 }, this, 0);
    sucsess = sucsess && m_message.Create(L"The current license key is missing or wrong.Please enter your license key to activate.", WS_CHILD|SS_CENTER|WS_VISIBLE, RECT{ 0,0,1,1 }, this);
    sucsess = sucsess && m_labelKey.Create(L"Key", WS_CHILD|WS_VISIBLE, RECT{ 0,0,1,1 }, this);
    sucsess = sucsess && m_labelSig.Create(L"Signature", WS_CHILD|WS_VISIBLE, RECT{ 0,0,1,1 }, this);
    sucsess = sucsess && m_activate.Create(L"Activate", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, RECT{ 0,0,1,1 }, this, CM_ActivateLicense);
    sucsess = sucsess && m_save.Create(L"save key", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, RECT{ 0,0,1,1 }, this, 0);

    //m_activate.SetOwner(GetParent());

    std::string key, signature;
    if ( sucsess && loadLicense(signature, key) )
    {
        if (m_signature.GetSafeHwnd())
            m_signature.SetWindowText(CString(signature.c_str()));

        if (m_key.GetSafeHwnd())
            m_key.SetWindowText(CString(key.c_str()));
    }
    //GetSysColor. COLOR_3DFACE

    return sucsess ? 0 : -1;
}

void LicenceWnd::OnSize(UINT nType, int cx, int cy)
{
    updateLayout();
}

BOOL LicenceWnd::OnEraseBkgnd(CDC* pDC)
{
    CRect windRect;
    GetClientRect(windRect);
    CBrush brushWnd;
    brushWnd.CreateSolidBrush(GetSysColor(COLOR_3DFACE));

    pDC->FillRect(windRect, &brushWnd);
    return TRUE;
}

void LicenceWnd::OnActivateLicense()
{
    if (activateLicense())
    {
        auto pMainWnd = ::AfxGetMainWnd();
        if (pMainWnd && pMainWnd->GetSafeHwnd())
            pMainWnd->PostMessageW(Messages::WM_ActivateLicense, 0, 0);
    }
}

static inline std::string getStr(const CEdit & pEdit)
{
    TCHAR buffer[255];
    auto n = pEdit.GetLine(0, buffer, 255);
    return std::string(CStringA(buffer, n));
}

std::string licenseFilePath()
{
    char buffer[255];
    size_t sizes = 255;
    getenv_s(&sizes, buffer, 255, "HOMEDRIVE");

    std::string res(buffer, sizes - 1);

    getenv_s(&sizes, buffer, 255, "HOMEPATH");
    res = res + std::string(buffer, sizes - 1);

    return res + std::string("/.c3dkey");
}

bool LicenceWnd::loadLicense(std::string & signature, std::string & key)
{
    std::ifstream licenseFile;
    licenseFile.open(licenseFilePath(), std::ios::in);

    if (licenseFile.is_open())
    {
        char buffer[255];
        licenseFile.getline(buffer, 255);
        signature = std::string(buffer, licenseFile.gcount());
        licenseFile.getline(buffer, 255);
        key = std::string(buffer, licenseFile.gcount());
        licenseFile.close();

        return true;
    }

    return false;
}

void LicenceWnd::saveLicense(const std::string & signature, const  std::string & key)
{
    std::ofstream licenseFile;
    licenseFile.open(licenseFilePath(), std::ios::out);

    if (licenseFile.is_open())
    {
        licenseFile << signature << std::endl;
        licenseFile << key;
        licenseFile.close();
    }
}

bool LicenceWnd::activateLicense()
{
    bool isActivated = ::IsMathVisionEnable();

    if (!isActivated)
    {
        bool saveKey = m_save.GetCheck() == TRUE;

        std::string signature = getStr(m_signature);
        std::string key = getStr(m_key);

        ::EnableMathModules(signature.c_str(), static_cast<int>(signature.length()), key.c_str(), static_cast<int>(key.length()));
        isActivated = ::IsMathVisionEnable();
        if (isActivated && saveKey)
            saveLicense(signature, key);
    }

    return isActivated;
}

void LicenceWnd::updateLayout()
{
    CRect client;
    GetClientRect(client);

    const int lableWidth = 100;
    const int editHeight = 20;
    const int editWidth  = 420;
    const int buttonWidth = 120;
    const int checkboxWidth = 120;

    int h_center = client.Height() / 2;

    int left = (client.Width()-editWidth-lableWidth) / 2;
    int top = h_center - editHeight;
    
    m_message.SetWindowPos(NULL, 0, top, client.Width(), 20, SWP_NOZORDER);
    top += 25;

    m_labelSig.SetWindowPos(NULL, left, top, lableWidth, editHeight, SWP_NOZORDER);
    m_signature.SetWindowPos(NULL, left + lableWidth, top, editWidth, editHeight, SWP_NOZORDER);
    top += 25;

    m_labelKey.SetWindowPos(NULL, left, top, lableWidth, editHeight, SWP_NOZORDER);
    m_key.SetWindowPos(NULL, left + lableWidth, top, editWidth, editHeight, SWP_NOZORDER);
    top += 25;

    left = (client.Width() - buttonWidth - checkboxWidth - 5) / 2;

    m_save.SetWindowPos(NULL, left, top, checkboxWidth, editHeight, SWP_NOZORDER);
    left += checkboxWidth + 5;
    m_activate.SetWindowPos(NULL, left, top, checkboxWidth, editHeight, SWP_NOZORDER);
}

} // namespace MfcVision

VSN_END_NAMESPACE