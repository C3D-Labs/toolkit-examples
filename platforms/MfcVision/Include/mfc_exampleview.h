#ifndef __EXAMPLEVIEW_H
#define __EXAMPLEVIEW_H

#include <afxwin.h>
#include "mfc_visiondef.h"
#include <vsn_vision.h>
#include <mfc_openglwnd.h>

VSN_BEGIN_NAMESPACE
namespace MfcVision {

class MFC_CLASS ExampleView : public COpenGLWnd
{
public:
    ExampleView();
    virtual ~ExampleView();
protected:
    virtual void InitializeOpenGL();
public:
    //{{AFX_MSG(MFCContext
    afx_msg void OnDestroy();
protected:
    DECLARE_MESSAGE_MAP()
};

} // namespace MfcVision
VSN_END_NAMESPACE
#endif /* __EXAMPLEVIEW_H */