#include "mfc_stdafx.h"
#include "mfc_scenerendererprivate.h"

#include <vsn_graphicssceneengine.h>
#include <vsn_window.h>
#include <vsn_processevent.h>
#include <vsn_openglfbo.h>
#include <last.h>

VSN_BEGIN_NAMESPACE

namespace MfcVision {


/* CConverterEventListener */
CConverterEventListener::CConverterEventListener(Object* pParent, HWND hWnd)
    : Object(pParent)
    , m_hWnd(hWnd)
    , m_pListenerEvent(nullptr)
    , m_idleTimerId(-1)
{
}

//-----------------------------------------------------------------------------
//
// ---
CConverterEventListener::~CConverterEventListener()
{
}

//-----------------------------------------------------------------------------
// Установить слушателя событий
// ---
void CConverterEventListener::setListenerEvent(Object* pListenerEvent)
{
    m_pListenerEvent = pListenerEvent;
}

#define vsn_GET_X_LPARAM(lp)    ((int)(short)LOWORD(lp))
#define vsn_GET_Y_LPARAM(lp)    ((int)(short)HIWORD(lp))
#define vsn_GET_WHEEL_DELTA(wParam)  ((short)HIWORD(wParam))

//MAKELPARAM(nRepCnt, nFlags)
//-----------------------------------------------------------------------------
// Перегрузка для внутренних работ.
// ---
bool CConverterEventListener::OnWinEvent(MSG* pMsg, long* result)
{
    switch (pMsg->message)
    {
        case WM_KEYDOWN:
            return OnKeyPressEvent((UINT)pMsg->wParam, (UINT)LOWORD(pMsg->lParam), (UINT)HIWORD(pMsg->lParam));
        case WM_KEYUP:
            return OnKeyReleaseEvent((UINT)pMsg->wParam, (UINT)LOWORD(pMsg->lParam), (UINT)HIWORD(pMsg->lParam));
        case WM_MOUSELEAVE:
            return false;
        case WM_MOUSEHOVER:
            return OnMouseHoverEvent((UINT)pMsg->wParam, CPoint(vsn_GET_X_LPARAM((DWORD)pMsg->lParam), vsn_GET_Y_LPARAM((DWORD)pMsg->lParam)));
        case WM_MOUSEMOVE:
        {
/*
            TRACKMOUSEEVENT tme = { 0 };
            tme.cbSize = sizeof(tme);
            tme.hwndTrack = m_hWnd;
            tme.dwFlags = TME_HOVER | TME_LEAVE;
            tme.dwHoverTime = HOVER_DEFAULT;

            _TrackMouseEvent(&tme);
*/
            return OnMouseMoveEvent((UINT)pMsg->wParam, CPoint(vsn_GET_X_LPARAM((DWORD)pMsg->lParam), vsn_GET_Y_LPARAM((DWORD)pMsg->lParam)));
        }
        case WM_LBUTTONDBLCLK:
            return OnMouseDoubleClickEvent((UINT)pMsg->wParam, CPoint(vsn_GET_X_LPARAM((DWORD)pMsg->lParam), vsn_GET_Y_LPARAM((DWORD)pMsg->lParam)), ProcessEvent::LButtonDblClk);
        case WM_MBUTTONDBLCLK:
            return OnMouseDoubleClickEvent((UINT)pMsg->wParam, CPoint(vsn_GET_X_LPARAM((DWORD)pMsg->lParam), vsn_GET_Y_LPARAM((DWORD)pMsg->lParam)), ProcessEvent::MButtonDblClk);
        case WM_RBUTTONDBLCLK:
            return OnMouseDoubleClickEvent((UINT)pMsg->wParam, CPoint(vsn_GET_X_LPARAM((DWORD)pMsg->lParam), vsn_GET_Y_LPARAM((DWORD)pMsg->lParam)), ProcessEvent::RButtonDblClk);
        case WM_LBUTTONDOWN:
            return OnMousePressEvent((UINT)pMsg->wParam, CPoint(vsn_GET_X_LPARAM((DWORD)pMsg->lParam), vsn_GET_Y_LPARAM((DWORD)pMsg->lParam)), ProcessEvent::LButtonDown);
        case WM_MBUTTONDOWN:
            return OnMousePressEvent((UINT)pMsg->wParam, CPoint(vsn_GET_X_LPARAM((DWORD)pMsg->lParam), vsn_GET_Y_LPARAM((DWORD)pMsg->lParam)), ProcessEvent::MButtonDown);
        case WM_RBUTTONDOWN:
            return OnMousePressEvent((UINT)pMsg->wParam, CPoint(vsn_GET_X_LPARAM((DWORD)pMsg->lParam), vsn_GET_Y_LPARAM((DWORD)pMsg->lParam)), ProcessEvent::RButtonDown);
        case WM_LBUTTONUP:
            return OnMouseReleaseEvent((UINT)pMsg->wParam, CPoint(vsn_GET_X_LPARAM((DWORD)pMsg->lParam), vsn_GET_Y_LPARAM((DWORD)pMsg->lParam)), ProcessEvent::LButtonUp);
        case WM_MBUTTONUP:
            return OnMouseReleaseEvent((UINT)pMsg->wParam, CPoint(vsn_GET_X_LPARAM((DWORD)pMsg->lParam), vsn_GET_Y_LPARAM((DWORD)pMsg->lParam)), ProcessEvent::MButtonUp);
        case WM_RBUTTONUP:
            return OnMouseReleaseEvent((UINT)pMsg->wParam, CPoint(vsn_GET_X_LPARAM((DWORD)pMsg->lParam), vsn_GET_Y_LPARAM((DWORD)pMsg->lParam)), ProcessEvent::RButtonUp);
        case WM_MOUSEWHEEL:
            return OnMouseWheelEvent((UINT)pMsg->wParam, vsn_GET_WHEEL_DELTA(pMsg->wParam), CPoint(vsn_GET_X_LPARAM((DWORD)pMsg->lParam), vsn_GET_Y_LPARAM((DWORD)pMsg->lParam)));
        default:
            break;
    }
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
bool CConverterEventListener::OnKeyPressEvent(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    KeyEvent processEvent(ProcessEvent::KeyDown, nChar, 0, 0, 0/*event->nativeScanCode(), event->nativeVirtualKey(), event->nativeModifiers()*/);
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
bool CConverterEventListener::OnKeyReleaseEvent(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    KeyEvent processEvent(ProcessEvent::KeyUp, nChar, 0, 0, 0/*event->nativeScanCode(), event->nativeVirtualKey(), event->nativeModifiers()*/);
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
static int mapModifiers(UINT nFlags)
{
    VSN_UNUSED(nFlags);
    int flag = 0;
    if ((::GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0)
        flag |= mb_Shift;
    if ((::GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0)
        flag |= mb_Control;
    if ((::GetAsyncKeyState(VK_MENU) & 0x8000) != 0)
        flag |= mb_Alt;
    return flag;
}

//-----------------------------------------------------------------------------
//
// ---
bool CConverterEventListener::OnMouseHoverEvent(UINT nFlags, CPoint point)
{
    _ASSERT(m_pListenerEvent != nullptr);
    int flags = mapModifiers(nFlags);
    HoverEvent processEvent(ProcessEvent::HoverMove, IntPoint(point.x, point.y), IntPoint());
    processEvent.SetFlags(flags);
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
bool CConverterEventListener::OnMousePressEvent(UINT nFlags, CPoint point, ProcessEvent::EventType evType)
{
    _ASSERT(m_pListenerEvent != nullptr);

    ProcessEvent::EventType type = evType;
    int flags = mapModifiers(nFlags);

    if (evType == ProcessEvent::LButtonDown)
        flags |= mb_LButton;
    else if (evType == ProcessEvent::MButtonDown)
        flags |= mb_MButton;
    else if (evType == ProcessEvent::RButtonDown)
        flags |= mb_RButton;

    CPoint ptScreenCursor;
    ::GetCursorPos(&ptScreenCursor);
    ::ScreenToClient(m_hWnd, &ptScreenCursor);

    MouseEvent processEvent(type);
    processEvent.SetFlags(flags);
    processEvent.SetScreenPos(IntPoint(ptScreenCursor.x, ptScreenCursor.y));
//    processEvent.SetWindowPos(IntPoint(event->windowPos().x(), event->windowPos().y()));
    processEvent.SetClientPos(IntPoint(point.x, point.y));

    // set current viewport
    if (auto pScene = vobject_cast<GraphicsScene*>(m_pListenerEvent))
        processEvent.SetViewport(pScene->GetViewport()->GetId());

    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);

    return false;
}

//-----------------------------------------------------------------------------
//
// ---
bool CConverterEventListener::OnMouseMoveEvent(UINT nFlags, CPoint point)
{
    _ASSERT(m_pListenerEvent != nullptr);

    int flags = mapModifiers(nFlags);
    if (nFlags & MK_LBUTTON)
        flags |= mb_LButton;
    if (nFlags & MK_MBUTTON)
        flags |= mb_MButton;
    if (nFlags & MK_RBUTTON)
        flags |= mb_RButton;

    CPoint ptScreenCursor;
    ::GetCursorPos(&ptScreenCursor);
    ::ScreenToClient(m_hWnd, &ptScreenCursor);

    MouseEvent processEvent(ProcessEvent::MouseMove);
    processEvent.SetFlags(flags);
    processEvent.SetScreenPos(IntPoint(ptScreenCursor.x, ptScreenCursor.y));
//    processEvent.SetWindowPos(IntPoint(event->windowPos().x(), event->windowPos().y()));
    processEvent.SetClientPos(IntPoint(point.x, point.y));

    // set current viewport
    if (auto pScene = vobject_cast<GraphicsScene*>(m_pListenerEvent))
        processEvent.SetViewport(pScene->GetViewport()->GetId());

    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
bool CConverterEventListener::OnMouseReleaseEvent(UINT nFlags, CPoint point, ProcessEvent::EventType evType)
{
    _ASSERT(m_pListenerEvent != nullptr);

    ProcessEvent::EventType type = evType;
    int flags = mapModifiers(nFlags);

    if (evType == ProcessEvent::LButtonDown || evType == ProcessEvent::LButtonUp)
        flags |= mb_LButton;
    else if (evType == ProcessEvent::MButtonDown || evType == ProcessEvent::MButtonUp)
        flags |= mb_MButton;
    else if (evType == ProcessEvent::RButtonDown || evType == ProcessEvent::RButtonUp)
        flags |= mb_RButton;

    CPoint ptScreenCursor;
    ::GetCursorPos(&ptScreenCursor);
    ::ScreenToClient(m_hWnd, &ptScreenCursor);

    MouseEvent processEvent(type);
    processEvent.SetFlags(flags);
    processEvent.SetScreenPos(IntPoint(ptScreenCursor.x, ptScreenCursor.y));
//    processEvent.SetWindowPos(IntPoint(event->windowPos().x(), event->windowPos().y()));
    processEvent.SetClientPos(IntPoint(point.x, point.y));

    // set current viewport
    if (auto pScene = vobject_cast<GraphicsScene*>(m_pListenerEvent))
        processEvent.SetViewport(pScene->GetViewport()->GetId());

    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);

    return false;
}

//-----------------------------------------------------------------------------
//
// ---
bool CConverterEventListener::OnMouseDoubleClickEvent(UINT nFlags, CPoint point, ProcessEvent::EventType evType)
{
    _ASSERT(m_pListenerEvent != nullptr);

    int flags = mapModifiers(nFlags);

    if (evType == ProcessEvent::LButtonDblClk)
        flags |= mb_LButton;
    else if (evType == ProcessEvent::MButtonDblClk)
        flags |= mb_MButton;
    else if (evType == ProcessEvent::RButtonDblClk)
        flags |= mb_RButton;

    CPoint ptScreenCursor;
    ::GetCursorPos(&ptScreenCursor);
    ::ScreenToClient(m_hWnd, &ptScreenCursor);

    MouseEvent processEvent(evType);
    processEvent.SetFlags(flags);
    processEvent.SetScreenPos(IntPoint(ptScreenCursor.x, ptScreenCursor.y));
//    processEvent.SetWindowPos(IntPoint(event->windowPos().x(), event->windowPos().y()));
    processEvent.SetClientPos(IntPoint(point.x, point.y));

    // set current viewport
    if (auto pScene = vobject_cast<GraphicsScene*>(m_pListenerEvent))
        processEvent.SetViewport(pScene->GetViewport()->GetId());

    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
bool CConverterEventListener::OnMouseWheelEvent(UINT nFlags, short zDelta, CPoint point)
{
    ::ScreenToClient(m_hWnd, &point);
    WheelEvent processEvent;
    ProcessEvent::EventType type = ProcessEvent::None;
    int flags = mapModifiers(nFlags);
    processEvent.SetFlags(flags);
    processEvent.SetWheelDelta(static_cast<int>(zDelta));
    processEvent.SetWindowPos(IntPoint(point.x, point.y));
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}



/* CSceneRendererPrivate */
CSceneRendererPrivate::CSceneRendererPrivate(GraphicsSceneEnginePtr ptrEngine, OpenGLContextContainer* pSharedContainer)
    : m_ptrGraphicsView(std::make_shared<GraphicsView>(ptrEngine))
    , m_pContext(nullptr)
    , m_pWindow(nullptr)
    , m_bInitialized(false)
    , m_bFlushPending(false)
    , m_requestedSamples(0)
    , m_bInPaintGL(false)
    , m_invalidFrame(true)
    , m_pFrameCache(nullptr)
    , m_pEventFilter(nullptr)
{
    m_requestedFormat = RenderingAreaFormat::GetDefaultFormat();
}

//-----------------------------------------------------------------------------
//
// ---
CSceneRendererPrivate::~CSceneRendererPrivate()
{
}

//-----------------------------------------------------------------------------
// Initializing opengl and Vision resources
// ---
void CSceneRendererPrivate::Initialize(HWND hWnd)
{
    VSN_P(CSceneRenderer);
    if (m_bInitialized)
        return;
    m_hWnd = hWnd;
    m_requestedSamples = m_requestedFormat.GetSamples();
    OpenGLContextInterface* pContext = OpenGLContextInterface::CreateOpenGLContext(m_requestedFormat);
    if (pContext == nullptr)
        _ASSERT(FALSE);

    m_pWindow = new Window;
    m_pWindow->SetFormat(pContext->GetFormat());
    m_pWindow->Create(hWnd, pContext);
    if (!pContext->MakeCurrent(m_pWindow))
    {
        _RPTW0(_CRT_ERROR, "COpenGLViewPrivate::Initialize(): Failed to make context current");
        return;
    }
    m_pContext = pContext;

    CRect rect;
    ::GetWindowRect(hWnd, &rect);
    int w = rect.Width();
    int h = rect.Height();
    if (w == 0 || h == 0)
    {
        w = 100;
        h = 100;
    }
    m_pFrameCache = new OpenGLFramebufferObject(w, h, m_requestedSamples, true/*depth*/, true/*stencil*/);
    m_ptrGraphicsView->Initialize();
    m_pEventFilter = new CConverterEventListener(&p, hWnd);
    m_pEventFilter->setListenerEvent(m_ptrGraphicsView->GetGraphicsScene());

    m_bInitialized = true;
    p.InitializeOpenGL();
}

//-----------------------------------------------------------------------------
//
// ---
void CSceneRendererPrivate::Reset()
{
    VSN_P(CSceneRenderer);

    if (m_bInitialized)
        p.MakeCurrent();

    delete m_pFrameCache;
    m_pFrameCache = nullptr;

    if (m_bInitialized)
        p.DoneCurrent();

    VSN_DELETE_AND_NULL(m_pWindow);
    VSN_DELETE_AND_NULL(m_pContext);
    m_bInitialized = false;
}

//-----------------------------------------------------------------------------
//
// ---
void CSceneRendererPrivate::InvokeUserPaint()
{
    VSN_P(CSceneRenderer);
    m_bInPaintGL = true;
    p.PaintOpenGL();
    m_bInPaintGL = false;

    m_bFlushPending = true;
}


//-----------------------------------------------------------------------------
//
// ---
void CSceneRendererPrivate::Render()
{
    VSN_P(CSceneRenderer);
    if (!m_bInitialized)
        return;
    p.MakeCurrent();

    if (m_pFrameCache)
    {
        if (m_invalidFrame)
        {
            m_pFrameCache->Bind();
            InvokeUserPaint();
            m_pFrameCache->Release();
            m_invalidFrame = true;
        }

        p.MakeCurrent();
        // настроим умолчательные параметры, для вывода изображения
        glViewport(0, 0, m_pFrameCache->GetWidth(), m_pFrameCache->GetHeight());
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        m_pFrameCache->RenderImage(-1, -1, 2, 2);
    }
    else
        InvokeUserPaint();

    if (!GlobalFlags::IsSelectionMode())
        m_pContext->SwapBuffers(m_pWindow);
}

//-----------------------------------------------------------------------------
//
// ---
void CSceneRendererPrivate::ProcessActivation()
{
    VSN_P(CSceneRenderer);
    if (Essence* pEssence = m_ptrGraphicsView->GetSceneEngine()->GetTopEssence())
    {
        std::vector<PrAbstractCamera*> vector = pEssence->FindChildren<PrAbstractCamera*>();
        for (auto it = vector.begin(); it != vector.end(); ++it)
        {
            PrAbstractCamera* pProcess = (*it);
            pProcess->SetViewport(m_ptrGraphicsView->GetViewport().get());
            bool bConnect = Object::Connect(pProcess, &PrAbstractCamera::OnCameraModified, &p, &CSceneRenderer::RepaintWindow);
            _ASSERT(bConnect != false);
        }
    }
}

//-----------------------------------------------------------------------------
//
// ---
void CSceneRendererPrivate::ProcessDeactivation()
{
    VSN_P(CSceneRenderer);
    if (Essence* pEssence = m_ptrGraphicsView->GetSceneEngine()->GetTopEssence())
    {
        std::vector<PrAbstractCamera*> vector = pEssence->FindChildren<PrAbstractCamera*>();
        for (auto it = vector.begin(); it != vector.end(); ++it)
        {
            PrAbstractCamera* pProcess = (*it);
            pProcess->SetViewport(m_ptrGraphicsView->GetViewport().get());
            bool bConnect = Object::Disconnect(pProcess, &PrAbstractCamera::OnCameraModified, &p, &CSceneRenderer::RepaintWindow);
            _ASSERT(bConnect != false);
        }
    }
}

/* CSceneRenderer */
//-----------------------------------------------------------------------------
//
// ---
CSceneRenderer::CSceneRenderer()
{
    vsn_d_ptr = new CSceneRendererPrivate(std::make_shared<GraphicsSceneEngine>(), nullptr);
    vsn_d_ptr->setPublic(this);
}

//-----------------------------------------------------------------------------
//
// ---
CSceneRenderer::~CSceneRenderer()
{
    MakeCurrent();
    VSN_FINI_PRIVATE()
}

//-----------------------------------------------------------------------------
//
// ---
void CSceneRenderer::MakeCurrent()
{
    VSN_D(CSceneRenderer)
    if (!d.m_bInitialized)
        return;
    _ASSERT(d.m_pContext != nullptr);
    if (d.m_pContext->MakeCurrent(d.m_pWindow))
        OpenGLContextInterface::m_pContextInterface = static_cast<OpenGLContextInterface*>(d.m_pContext);
}

//-----------------------------------------------------------------------------
//
// ---
void CSceneRenderer::DoneCurrent()
{
    VSN_D(CSceneRenderer)
    if (!d.m_bInitialized)
        return;
    _ASSERT(d.m_pContext != nullptr);
    d.m_pContext->DoneCurrent();
    OpenGLContextInterface::m_pContextInterface = nullptr;
}

//-----------------------------------------------------------------------------
//
// ---
void CSceneRenderer::InitializeOpenGL()
{
}

//-----------------------------------------------------------------------------
//
// ---
void CSceneRenderer::PaintOpenGL()
{
    VSN_D(CSceneRenderer)
    if (d.m_pContext == nullptr)
        return;
    d.m_ptrGraphicsView->DoRender();
}

//-----------------------------------------------------------------------------
// Вернуть указатель на источник освешения сцены
// ---
Light* CSceneRenderer::GetMainLight() const
{
    VSN_D(const CSceneRenderer);
    return d.m_ptrGraphicsView->GetMainLight();
}

//-----------------------------------------------------------------------------
//
// ---
Viewport* CSceneRenderer::GetViewport() const
{
    VSN_D(const CSceneRenderer);
    return d.m_ptrGraphicsView->GetViewport().get();
}

//-----------------------------------------------------------------------------
//
// ---
GraphicsScene* CSceneRenderer::GetGraphicsScene() const
{
    VSN_D(const CSceneRenderer);
    return d.m_ptrGraphicsView->GetGraphicsScene();
}

//-----------------------------------------------------------------------------
//
// ---
SceneContentPtr CSceneRenderer::GetSceneContent() const
{
    VSN_D(const CSceneRenderer);
    return d.m_ptrGraphicsView->GetGraphicsScene()->GetSceneContent();
}

//-----------------------------------------------------------------------------
// Вернуть указатель на GraphicsView.
// ---
GraphicsViewPtr CSceneRenderer::GetGraphicsView() const
{
    VSN_D(const CSceneRenderer);
    return d.m_ptrGraphicsView;
}

//-----------------------------------------------------------------------------
// Создать CSceneRenderer и захватить все необходимые рисурсы.
// ---
void CSceneRenderer::DoCreate(HWND hWnd)
{
    VSN_D(CSceneRenderer);
    d.Initialize(hWnd);
    GetGraphicsView()->GetSceneEngine()->GetObjectPickSelection()->SetOpenGLContext(d.m_pContext);
    GetGraphicsView()->GetSceneEngine()->GetObjectPickSelection()->SetViewport(d.m_ptrGraphicsView->GetViewport());
}

//-----------------------------------------------------------------------------
// Разрушить и освободить ресурсы Vision.
// ---
void CSceneRenderer::DoDestroy()
{
    VSN_D(CSceneRenderer);
    GetGraphicsView()->GetSceneEngine()->GetObjectPickSelection()->ResetOpenGLContext(d.m_pContext);
    d.Reset();
}

//-----------------------------------------------------------------------------
// Подготовка Vision для отрисовки сцены.
// ---
void CSceneRenderer::DoPreparingToDisplay()
{
    VSN_D(CSceneRenderer);
    d.m_ptrGraphicsView->PreparingToDisplay();
}

//-----------------------------------------------------------------------------
// Отрисовать сцену.
// ---
void CSceneRenderer::DoDraw()
{
    VSN_D(CSceneRenderer);
    d.Render();
}

//-----------------------------------------------------------------------------
//
// ---
void CSceneRenderer::RepaintWindow()
{
    VSN_D(CSceneRenderer);
    d.Render();
}

//-----------------------------------------------------------------------------
//
// ---
void CSceneRenderer::DoResize(int w, int h)
{
    VSN_D(CSceneRenderer);
    if (d.m_pContext == nullptr)
        return;
    MakeCurrent();
    if (OpenGLContextInterface::GetCurrentContext() && d.m_pContext == OpenGLContextInterface::GetCurrentContext())
    {
        d.m_ptrGraphicsView->DoResize(w, h);
        if (d.m_pFrameCache)
        {
            d.m_pFrameCache->Update(w, h);
            d.m_invalidFrame = true;
        }
    }
}

//-----------------------------------------------------------------------------
//
// ---
void CSceneRenderer::DoSetFocus(CWnd* pOldWnd)
{
    VSN_D(CSceneRenderer);
    VSN_UNUSED(pOldWnd);
    d.ProcessActivation();
}

//-----------------------------------------------------------------------------
//
// ---
void CSceneRenderer::DoKillFocus(CWnd* pNewWnd)
{
    VSN_D(CSceneRenderer);
    VSN_UNUSED(pNewWnd);
    d.ProcessDeactivation();
}

//-----------------------------------------------------------------------------
// Перегрузка для внутренних работ.
// ---
bool CSceneRenderer::OnWinEvent(MSG* pMsg, long* result)
{
    VSN_D(CSceneRenderer);
    if (d.m_pEventFilter != nullptr)
        return d.m_pEventFilter->OnWinEvent(pMsg, result);
    return false;
}


//-----------------------------------------------------------------------------
// Creating processes to control the camera.
// ---
MFC_FUNC(void) CreateProcessesCameraControls(Viewport* pViewport, Node* pParent, ProcessTypes prType)
{
    // Create and add process Orbit
    if (prType.checkFlag(pt_Orbit))
    {
        PrAbstractCamera* pProcess = new PrCameraOrbit(pParent);
        pProcess->SetMouseButtonsActivate({ VSN::mb_RButton });
        pProcess->SetViewport(pViewport);
    }
    // Create and add process Pan
    if (prType.checkFlag(pt_Pan))
    {
        PrAbstractCamera* pProcess = new PrCameraPan(pParent);
        pProcess->SetMouseButtonsActivate({ VSN::mb_MButton });
        pProcess->SetViewport(pViewport);
    }
    // Create and add process Zoom
    if (prType.checkFlag(pt_Zoom))
    {
        PrAbstractCamera* pProcess = new PrCameraZoom(pParent);
        pProcess->SetViewport(pViewport);
        VSN_UNUSED(pProcess);
    }
}


} // namespace MfcVision

VSN_END_NAMESPACE
