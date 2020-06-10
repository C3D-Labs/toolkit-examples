////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru .
         \en . \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __OPENGLWIDGETPRIVATE_H
#define __OPENGLWIDGETPRIVATE_H

#include "qt_openglwidget.h"
#include "qt_visiondef.h"

VSN_BEGIN_NAMESPACE

/** \brief \ru ВНИМАНИЕ! Этот файл не является частью API Vision. Он необходим для иллюстрации использования 
               ядра Vision с библиотекой Qt и ее классами. Этот заголовочный файл может изменяться от версии 
               к версии без предупреждения или полностью удаляться.
           \en WARNING! The file is not a part of API Vision. It is needed to illustrate using of the Vision kernel
               with Qt library and its classes. This header file can be changed from version to version with
               no warning or completely deleted.\~
*/

namespace QtVision {
//------------------------------------------------------------------------------
/** \brief \ru Класс QtConverterEventListener служит для интеграции с событийной моделью Qt и Vision.
           \en QtConverterEventListener class gives integration with event Qt model and Vision. \~
    \details \ru В первую очередь, QtConverterEventListener необходим для обеспечения работы Vision
                 с манипуляторами, такими как мышь, клавиатура и др. Кроме того, ConverterEvent служит
                 для конвертации определенных событий Qt в понятные события для Vision.
              \en QtConverterEventListener is primarily needed to provide functioning of Vision with
                  such manipulators as mouse, keyboard, etc. Besides, ConverterEvent provides converting
                  certain Qt events to familiar events for Vision. \n \~
    \ingroup Vision_OpenGL
*/
// ---
class QT_CLASS QtConverterEventListener : public QObject
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit QtConverterEventListener(QObject* pParent);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~QtConverterEventListener();
public:
    /// \ru Установить слушателя событий. \en Sets event listener.
    void setListenerEvent(Object* pListenerEvent);
protected:
    bool keyPressEvent(QKeyEvent* event, QObject* watched);
    bool keyReleaseEvent(QKeyEvent* event, QObject* watched);
    bool mouseHoverEvent(QHoverEvent* event, QObject* watched);
    bool mousePressEvent(QMouseEvent* event, QObject* watched);
    bool mouseMoveEvent(QMouseEvent* event, QObject* watched);
    bool mouseReleaseEvent(QMouseEvent* event, QObject* watched);
    bool mouseDoubleClickEvent(QMouseEvent* event, QObject* watched);
    bool mouseWheelEvent(QWheelEvent* event, QObject* watched);
protected:
    /// \ru Перегрузка для внутренних работ. \en Overload for internal workings.
    virtual bool eventFilter(QObject* watched, QEvent* event);
    virtual void timerEvent(QTimerEvent* event);
protected:
    Object* m_pListenerEvent;
    int m_idleTimerId;
};

class QtOpenGLContextShell;
/* QtOpenGLWidgetPrivate */
class QtOpenGLWidgetPrivate
{
protected:
    VSN_DECLARE_PUBLIC(QtOpenGLWidget);
public:
    explicit QtOpenGLWidgetPrivate(OpenGLContextContainer* pSharedContainer = nullptr)
        : m_bInitialized(false)
        , m_bUpdatePending(false)
        , m_pSharedContainer(pSharedContainer)
        , m_pQContext(nullptr)
    {
    }
    virtual ~QtOpenGLWidgetPrivate()
    {
        reset();
    }
    virtual void initialize();
    void reset();
    void renderNow();
    void renderLater();
public:
    bool m_bInitialized;    ///< признак инициализация контекста
    bool m_bUpdatePending;
    OpenGLContextContainer* m_pSharedContainer;
    QtOpenGLContextShell* m_pQContext;
};

} // namespace QtVision

VSN_END_NAMESPACE

#endif // __OPENGLWIDGETPRIVATE_H
