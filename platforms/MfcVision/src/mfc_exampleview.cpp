#include "mfc_exampleview.h"
#include "vsn_scenegenerator.h"
#include <mfc_scenerenderer.h>
#include <last.h>

VSN_BEGIN_NAMESPACE
namespace MfcVision {

BEGIN_MESSAGE_MAP(ExampleView, COpenGLWnd)
END_MESSAGE_MAP()

ExampleView::ExampleView()
    : COpenGLWnd()
{
    MfcVision::CreateProcessesCameraControls(GetViewport(), GetSceneContent()->GetRootSegment());
}

//-----------------------------------------------------------------------------
//
// ---
ExampleView::~ExampleView()
{
}

//-----------------------------------------------------------------------------
//
// ---
void ExampleView::InitializeOpenGL()
{
    GetViewport()->GetCamera()->SetViewOrientation(IsoXYZ);
    GetViewport()->SetBackgroundColour(VSN::Color(0xFF, 0xFF, 0xFF));

    GetViewport()->ZoomToFit(GetSceneContent()->GetBoundingBox());
}


} // namespace MfcVision
VSN_END_NAMESPACE