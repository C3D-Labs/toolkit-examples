#include <StdAfx.h>

#include <vsn_application.h>
#include <tool_enabler.h>
#include <mfc_openglview.h>
#include "mfc_exampletools.h"
#include "nurbseditor.h"
#include <functional>


#include <last.h>

VSN_USE_NAMESPACE

/* Cube: implements the MFC application */
class MfcExampleApp : public CWinApp
{
public:
    MfcExampleApp() {}
public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
    /*virtual int Run();*/
    virtual BOOL OnIdle(LONG lCount);
protected:
    MfcVision::ExampleView* m_pView;
    Application* m_pAppl;

    std::unique_ptr<NurbsEditor> m_nurbsEditrp;
protected:
    DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(MfcExampleApp, CWinApp)
END_MESSAGE_MAP()

/* instance of the MFC application */
MfcExampleApp cube_app;

/* updates the GL window */
BOOL MfcExampleApp::OnIdle(LONG lCount)
{
    Sleep(1);
    return TRUE;
}

/* called when the application exits */
int MfcExampleApp::ExitInstance()
{
    CWinApp::ExitInstance();
    /* destroy the window and the OpenGL rendering context */
    VSN_DELETE_AND_NULL(m_pView);
    VSN_DELETE_AND_NULL(m_pAppl);
    return 0;
}


/* called when the application starts */
BOOL MfcExampleApp::InitInstance()
{
    CWinApp::InitInstance();
    m_pAppl = new Application;

    //if (!MfcVision::isExistLicense())
    //    return 0;

    RenderingAreaFormat format;
    format.SetDepthBufferSize(24);
    format.SetStencilBufferSize(8);
    format.SetSamples(4);
    format.SetSwapInterval(0);
    RenderingAreaFormat::SetDefaultFormat(format);

    CRect actualDesktop;
    GetWindowRect(GetDesktopWindow(), &actualDesktop);

    CPoint pos(200, 200);
    CSize sz(2 * actualDesktop.Width() / 3, 2 * actualDesktop.Height() / 3);
    // instance the MFC window/OpenGLContext 
    m_pView = new MfcVision::ExampleView;

    MfcVision::ExampleWindow * pFrame = new MfcVision::ExampleWindow(m_pView);

    std::unique_ptr<NurbsEditor> nurbsEditor;

    // loading scene after activate license
    pFrame->SetSceneLoader([this](GraphicsScene * pScene)
    {
        m_nurbsEditrp.reset(new NurbsEditor(pScene));
    });

    m_pMainWnd = pFrame;
    m_pMainWnd->ShowWindow(m_nCmdShow);

    return TRUE;
}