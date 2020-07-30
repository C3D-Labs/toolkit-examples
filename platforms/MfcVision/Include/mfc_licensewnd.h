#ifndef __LICENSEWND_H
#define __LICENSEWND_H

#include <afxwin.h>
#include "mfc_visiondef.h"
#include "vsn_global.h"
#include <last.h>

VSN_BEGIN_NAMESPACE

namespace MfcVision {

enum Commands
{
    CM_ActivateLicense = 1,
};

enum Messages
{
    WM_ActivateLicense = WM_USER + 1
};

/* CubeView */
class MFC_CLASS LicenceWnd : public CWnd
{
public:
    LicenceWnd();
    virtual ~LicenceWnd();
protected:
    afx_msg BOOL OnCreate(LPCREATESTRUCT);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);

    afx_msg void OnActivateLicense();
public:
    bool activateLicense();
private:
    void updateLayout();
    bool loadLicense(std::string & signature, std::string & key);
    void saveLicense(const std::string & signature, const  std::string & key);
private:
    CEdit m_key;
    CEdit m_signature;
    CStatic m_message;
    CStatic m_labelKey;
    CStatic m_labelSig;
    CButton m_activate;
    CButton m_save;
protected:
    DECLARE_MESSAGE_MAP()
};

} // namespace MfcVision

VSN_END_NAMESPACE

#endif __LICENSEWND_H