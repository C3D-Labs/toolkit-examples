#ifndef __SCENERENDERERPRIVATE_H
#define __SCENERENDERERPRIVATE_H

#include <afxwin.h>

#include <vsn_object.h>
#include <vsn_vision.h>
#include <vsn_graphicsview.h>
#include "mfc_scenerenderer.h"
#include "mfc_visiondef.h"

#include <vsn_global.h>

VSN_BEGIN_NAMESPACE

/** \brief \ru ВНИМАНИЕ! Этот файл не является частью API Vision. Он необходим для иллюстрации использования
               ядра Vision с библиотекой MFC и ее классами. Этот заголовочный файл может изменяться от версии
               к версии без предупреждения или полностью удаляться.
            \en NO TRANSLATION. \~
*/

namespace MfcVision {


//------------------------------------------------------------------------------
/** \brief \ru Класс CConverterEventListener служит для интеграции с событийной моделью MFC и Vision.
           \en CConverterEventListener class gives integration with event MFC model and Vision. \~
    \details \ru В первую очередь, CConverterEventListener необходим для обеспечения работы Vision
                 с манипуляторами, такими как мышь, клавиатура и др. Кроме того, ConverterEvent служит
                 для конвертации определенных событий MFC в понятные события для Vision.
             \en CConverterEventListener is primarily needed to provide functioning of Vision with
                 such manipulators as mouse, keyboard, etc. Besides, ConverterEvent provides converting
                 certain MFC events to familiar events for Vision. \n \~
    \ingroup Vision_OpenGL
*/
// ---
class CConverterEventListener : public Object
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit CConverterEventListener(Object* pParent, HWND hWnd);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~CConverterEventListener();
public:
    /// \ru Установить слушателя событий. \en Sets event listener.
    void setListenerEvent(Object* pListenerEvent);
    /// \ru Перегрузка для внутренних работ. \en Overload for internal workings.
    virtual bool OnWinEvent(MSG* pMsg, long* result);
protected:
    bool OnKeyPressEvent(UINT nChar, UINT nRepCnt, UINT nFlags);
    bool OnKeyReleaseEvent(UINT nChar, UINT nRepCnt, UINT nFlags);
    bool OnMouseHoverEvent(UINT nFlags, CPoint point);
    bool OnMousePressEvent(UINT nFlags, CPoint point, ProcessEvent::EventType evType);
    bool OnMouseMoveEvent(UINT nFlags, CPoint point);
    bool OnMouseReleaseEvent(UINT nFlags, CPoint point, ProcessEvent::EventType evType);
    bool OnMouseDoubleClickEvent(UINT nFlags, CPoint point, ProcessEvent::EventType evType);
    bool OnMouseWheelEvent(UINT nFlags, short zDelta, CPoint pt);
protected:
    HWND m_hWnd;
    Object* m_pListenerEvent;
    int m_idleTimerId;
};


/* CSceneRendererPrivate */
class CSceneRendererPrivate
{
public:
    VSN_DECLARE_PUBLIC(CSceneRenderer)
public:
    explicit CSceneRendererPrivate(GraphicsSceneEnginePtr ptrEngine, OpenGLContextContainer* pSharedContainer);
    virtual ~CSceneRendererPrivate();
public:
    void Initialize(HWND hWnd);
    void Reset();
    void InvokeUserPaint();
    void Render();
    void ProcessActivation();
    void ProcessDeactivation();
public:
    HWND m_hWnd;
    GraphicsViewPtr m_ptrGraphicsView;
    RenderingAreaFormat m_requestedFormat;
    OpenGLContextInterface* m_pContext;
    Window* m_pWindow;
    bool m_bInitialized;
    bool m_bFlushPending;
    int m_requestedSamples;
    bool m_bInPaintGL;

    bool m_invalidFrame;
    OpenGLFramebufferObject * m_pFrameCache;
    CConverterEventListener* m_pEventFilter;
};


} // namespace MfcVision

VSN_END_NAMESPACE

#endif /* __SCENERENDERERPRIVATE_H */
