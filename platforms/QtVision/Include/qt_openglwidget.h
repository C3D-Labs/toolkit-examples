////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Класс QtOpenGLWidget реализует интеграцию Vision c Qt. Представленные классы 
             необходимы для рендеринга графики Vision с помощью OpenGL.
         \en QtOpenGLWidget class implements integration of Vision with Qt.
             The presented classes are necessary to render graphics with OpenGL. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __OPENGLWIDGET_H
#define __OPENGLWIDGET_H

#include <QWidget>
#include <QGLWidget>
#include <QOpenGLWidget>
#include <QApplication>
#include <QSurfaceFormat>
#include <QDesktopWidget>

#include <vsn_vision.h>
#include <vsn_application.h>
#include <vsn_meshgeometry.h>
#include <vsn_graphicsview.h>
#include <vsn_graphicssceneengine.h>
#include <vsn_objectpickselection.h>
#include <vsn_openglcontextinterface.h>
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

class QtOpenGLWidgetPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс QtOpenGLWidget реализует интеграцию Vision c Qt.
           \en QtOpenGLWidget class implements integration of Vision with Qt. \~
    \details \ru QtOpenGLWidget необходим для работы Vision с другими классами библиотеки Qt. Например,
                 как самостоятельный виджет или может быть применен в качестве viewport для QGraphicsView
                 и QGraphicsScene. Vision внутри работает с собственным представлением контекста OpenGl 
                 (OpenGLContextInterface) и класс QtOpenGLWidget содержит некоторые оболочки, обеспечивающие 
                 совместную работу QOpenGLContext и OpenGLContextInterface.
             \en QtOpenGLWidget is needed for Vision to work with other classes of Qt library,
                 for example, as an independent widget or can be applied as viewport for QGraphicsView
                 and QGraphicsScene. Vision inside works with own representation of OpenGL context
                 (OpenGLContextInterface) and QtOpenGLWidget class contains certain shells providing
                 QtOpenGLWidget and OpenGLContextInterface with working jointly. \n \~
    \ingroup Vision_OpenGL
*/
// ---
class QT_CLASS QtOpenGLWidget : public QOpenGLWidget, public Object
{
    Q_OBJECT
    VSN_OBJECT(QtOpenGLWidget)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit QtOpenGLWidget(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    /// \ru Деструктор OpenGLWidget освобождает созданные ресурсы. \en OpenGLWidget destructor releases created resources. \~
    virtual ~QtOpenGLWidget();
public:
    /**
    \brief \ru Подготовка OpenGL для рендеринга в этом виджете(установить текущий OpenGL контекст).
           \en Preparing of OpenGL for rendering in this widget. Sets the current OpenGL context.
        \detaild \ru Нет необходимости вызывать эту функцию в большинстве случаев, потому что она 
                     вызывается автоматически перед вызовом paintGL().
                 \en No need to call this function in most cases, as it is called automatically
                     before calling paintGL().
    */
    using QOpenGLWidget::makeCurrent;
    void makeCurrent();
    /**
    \brief \ru Освободить OpenGL контекст.
           \en Releases OpenGL context.
        \detailed \ru Нет необходимости вызывать эту функцию в большинстве случаев, поскольку
                      в функции paintGL() контекст будет назначен и освобожден.
                  \en No need to call this function in most cases, as there will be context set and
                      released in paintGL() function.
    */
    using QOpenGLWidget::doneCurrent;
    void doneCurrent();

    /// \ru Вернуть указатель на OpenGLContextInterface. \en NO TRANSLATION. \~
    OpenGLContextInterface* contextInterface();
public:
    /// \ru Просто вызывает функцию QWidget::update(). Служит для совместимости слотов.
    /// \en Just calls QWidget::update() function. Serves for compatibility of slots. \~
    VSN_SLOT(Public, updateWidget, void updateWidget())
    /// \ru Просто вызывает функцию QWidget::repaint(). Служит для совместимости слотов.
    /// \en Just calls QWidget::repaint() function. Serves for compatibility of slots. \~
    VSN_SLOT(Public, repaintWidget, void repaintWidget())
protected:
    /// \ru Инициализация OpenGL ресурсов. \en Initialises OpenGL resources. \~
    virtual void initializeGL() override;
protected:
    virtual bool event(QEvent* event) override;
protected:
    QtOpenGLWidget(QtOpenGLWidgetPrivate& dd, QWidget* parent, Qt::WindowFlags f);
    VSN_DECLARE_PRIVATE(QtOpenGLWidget);
private:
    Q_DISABLE_COPY(QtOpenGLWidget);
};

class QtOpenGLSceneWidgetPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс QtOpenGLSceneWidget - это виджет для рендеринга графики Vision с помощью OpenGL.
           \en QtOpenGLSceneWidget is a widget for rendering Vision graphics with OpenGL. \~
    \details \ru Класс QtOpenGLSceneWidget полностью самостоятельный, создает и инициализирует 
                 в полной мере компоненты Vision. Этот класс представляет необходимые функции для работы с Vision. 
                 Класс QtOpenGLSceneWidget самостоятельно устанавливает текущий контест OpenGL, когда это необходимо. 
             \en QtOpenGLSceneWidget class is fully autonomous, so it completely creates and initialises
                 Vision components. This class provides required functions to work with Vision.
                 QtOpenGLSceneWidget class independently sets the current OpenGL context when necessary. \n \~
    \ingroup Vision_OpenGL
*/
// ---
class QT_CLASS QtOpenGLSceneWidget : public QtOpenGLWidget
{
    Q_OBJECT
    VSN_OBJECT(QtOpenGLSceneWidget)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit QtOpenGLSceneWidget(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    /// \ru Специальный конструктор. \en Special constructor. \~
    explicit QtOpenGLSceneWidget(GraphicsSceneEnginePtr engine, OpenGLContextContainer* sharedContainer, QWidget* parent = Q_NULLPTR,  Qt::WindowFlags f = Qt::WindowFlags());
    /// \ru Деструктор OpenGLWidget освобождает созданные ресурсы. \en OpenGLWidget destructor releases created resources. \~
    virtual ~QtOpenGLSceneWidget();
public:
    /// \ru Вернуть указатель на источник освешения сцены. \en Returns a pointer to scene lighting source. \~
    Light* mainLight() const;
    /// \ru Вернуть указатель на камеру. \en Returns a pointer to camera. \~
    Camera* camera() const;
    /// \ru Вернуть указатель на Viewport для отображения сцены. \en Returns a pointer to Viewport to display a scene. \~
    Viewport* viewport() const;
    /// \ru Вернуть указатель на содержимое сцены. \en Returns a pointer to scene content. \~
    SceneContentPtr sceneContent();
    /// \ru Вернуть указатель на графическую сцену. \en Returns a pointer to graphic scene. \~
    GraphicsScene* graphicsScene() const;
    /// \ru Вернуть указатель на компонент выбора объектов. \en Returns a pointer to object selecting component. \~
    ObjectPickSelection* objectPickSelection() const;
    /// \ru Вернуть указатель на GraphicsSceneEngine. \en Returns pointer to GraphicsSceneEngine. \~
    GraphicsSceneEnginePtr graphicsEngine() const;
    /// \ru Вернуть указатель на GraphicsView. \en Returns pointer to GraphicsView. \~
    GraphicsViewPtr graphicsView() const;
public:
    /// \ru Увеличить модель до размера viewport по габариту модели. \en Zooms the model to viewport size by bounding box of the model. \~
    VSN_SLOT(Public, ZoomToFit, void ZoomToFit())
protected:
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;
    virtual bool event(QEvent *event) override;
    virtual void enterEvent(QEvent* event) override;
    virtual void leaveEvent(QEvent* event) override;
    virtual void focusInEvent(QFocusEvent* event) override;
    virtual void focusOutEvent(QFocusEvent* event) override;
    virtual bool OnEvent(ProcessEvent* event);
protected:
    virtual void showEvent(QShowEvent* event) override;
    virtual void closeEvent(QCloseEvent* event) override;
private:
    Q_DISABLE_COPY(QtOpenGLSceneWidget);
    VSN_DECLARE_EX_PRIVATE(QtOpenGLSceneWidget);
    friend class QtRenderSelection;
};


enum ProcessType
{
    pt_Pan      = 0x01,
    pt_Orbit    = 0x02,
    pt_Zoom     = 0x04,
    pt_AllProcess = pt_Orbit | pt_Zoom | pt_Pan,
};
VSN_DECLARE_FLAGS(ProcessTypes, ProcessType)


/// \ru Создание процессов для управления камерой. \en Creating processes to control the camera. \~
QT_FUNC(void) CreateProcessesCameraControls(Node* pParent, ProcessTypes prType = pt_AllProcess);
/// \ru This is method is deprecated, use ActivateLicense
QT_FUNC(bool) isExistLicense();
QT_FUNC(bool) ActivateLicense(const std::string & signature = "", const std::string & key = "");

} // namespace QtVision

VSN_END_NAMESPACE

#endif // __OPENGLWIDGET_H
