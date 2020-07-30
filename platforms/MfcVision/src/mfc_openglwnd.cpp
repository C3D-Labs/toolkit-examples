#include "mfc_stdafx.h"
#include "mfc_openglwnd.h"
#include "mfc_scenerenderer.h"
#include <last.h>

VSN_BEGIN_NAMESPACE

namespace MfcVision {

IMPLEMENT_DYNCREATE(COpenGLWnd, CWnd)
//-----------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(COpenGLWnd, CWnd)
    ON_WM_CREATE()
    ON_WM_DESTROY()
    ON_WM_SHOWWINDOW()
    ON_WM_PAINT()
    ON_WM_SIZE()
END_MESSAGE_MAP()

/* COpenGLWnd */
//-----------------------------------------------------------------------------
//
// ---
COpenGLWnd::COpenGLWnd()
    : m_pSceneRenderer(new CSceneRenderer)
{
}

//-----------------------------------------------------------------------------
//
// ---
COpenGLWnd::~COpenGLWnd()
{
    VSN_DELETE_AND_NULL(m_pSceneRenderer);
}

//-----------------------------------------------------------------------------
// Вернуть указатель на источник освешения сцены.
// ---
Light* COpenGLWnd::GetMainLight() const
{
    return m_pSceneRenderer->GetMainLight();
}

//-----------------------------------------------------------------------------
// Вернуть указатель на Viewport для отображения сцены.
// ---
Viewport* COpenGLWnd::GetViewport() const
{
    return m_pSceneRenderer->GetViewport();
}

//-----------------------------------------------------------------------------
// Вернуть указатель на содержимое сцены.
// ---
SceneContentPtr COpenGLWnd::GetSceneContent() const
{
    return m_pSceneRenderer->GetSceneContent();
}

//-----------------------------------------------------------------------------
// Вернуть указатель на GraphicsView.
// ---
GraphicsViewPtr COpenGLWnd::GetGraphicsView() const
{
    return m_pSceneRenderer->GetGraphicsView();
}

//-----------------------------------------------------------------------------
// Функция вызывается после инициализации Vision
// ---
void COpenGLWnd::InitializeOpenGL()
{
}

BOOL COpenGLWnd::PreTranslateMessage(MSG* pMsg)
{
    long* resul = nullptr;
    m_pSceneRenderer->OnWinEvent(pMsg, resul);
    return CWnd::PreTranslateMessage(pMsg);
}

//-----------------------------------------------------------------------------
// Создать окно и захватить ресурсы OpenGL, а также произвести инициализацию Vision
// ---
int COpenGLWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;
    m_pSceneRenderer->DoCreate(m_hWnd);
    InitializeOpenGL();
    return 0;
}

//-----------------------------------------------------------------------------
//
// ---
void COpenGLWnd::OnDestroy()
{
    m_pSceneRenderer->DoDestroy();
    CWnd::OnDestroy();
}

//-----------------------------------------------------------------------------
//
// ---
void COpenGLWnd::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CWnd::OnShowWindow(bShow, nStatus);
    if (bShow)
        m_pSceneRenderer->DoPreparingToDisplay();
}

//-----------------------------------------------------------------------------
//
// ---
void COpenGLWnd::OnPaint()
{
    m_pSceneRenderer->DoDraw();
}

//-----------------------------------------------------------------------------
//
// ---
void COpenGLWnd::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);
    if (0 >= cx || 0 >= cy || nType == SIZE_MINIMIZED)
        return;
    m_pSceneRenderer->DoResize(cx, cy);
}


} // namespace MfcVision

VSN_END_NAMESPACE
