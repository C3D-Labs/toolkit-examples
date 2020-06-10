#include "qt_openglwidgetprivate.h"
#include <QApplication>
#include <QScreen>
#include <QWindow>
#include <QMessageBox>
#include <QProcessEnvironment>
#include <QtGui/qevent.h>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOffscreenSurface>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QOpenGLFramebufferObject>

#include <vsn_window.h>
#include <vsn_openglfbo.h>
#include <vsn_graphicsview.h>
#include <vsn_graphicssceneengine.h>
#include <vsn_graphicsscene.h>
#include <vsn_texture2d.h>
#include <tool_enabler.h>

#include "qt_openglcontext.h"
#include "lisencekey.h"

#include <last.h>

VSN_BEGIN_NAMESPACE

namespace QtVision {

/* QtConverterEventListener */
QtConverterEventListener::QtConverterEventListener(QObject* pParent)
    : QObject(pParent)
    , m_pListenerEvent(nullptr)
    , m_idleTimerId(-1)
{
    parent()->installEventFilter(this);
#ifndef VSN_OS_WIN
    m_idleTimerId = startTimer(QGuiApplication::primaryScreen()->refreshRate());
#endif
}

//-----------------------------------------------------------------------------
//
// ---
QtConverterEventListener::~QtConverterEventListener()
{
    parent()->removeEventFilter(this);
}

//-----------------------------------------------------------------------------
// Установить слушателя событий
// ---
void QtConverterEventListener::setListenerEvent(Object* pListenerEvent)
{
    m_pListenerEvent = pListenerEvent;
}

//-----------------------------------------------------------------------------
//
// ---
bool QtConverterEventListener::keyPressEvent(QKeyEvent* event, QObject* watched)
{
    KeyEvent processEvent(ProcessEvent::KeyDown, event->key(), event->nativeScanCode(), event->nativeVirtualKey(), event->nativeModifiers());
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
bool QtConverterEventListener::keyReleaseEvent(QKeyEvent* event, QObject* watched)
{
    KeyEvent processEvent(ProcessEvent::KeyUp, event->key(), event->nativeScanCode(), event->nativeVirtualKey(), event->nativeModifiers());
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
bool QtConverterEventListener::mouseHoverEvent(QHoverEvent* event, QObject* watched)
{
    Q_ASSERT(m_pListenerEvent != nullptr);
    int flags = 0;
    HoverEvent processEvent(ProcessEvent::HoverMove, IntPoint(event->posF().x(), event->posF().y()), IntPoint());
    processEvent.SetFlags(flags);
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
static int mapModifiers(Qt::KeyboardModifiers state)
{
    int flag = 0;
    if (state & Qt::ShiftModifier)
        flag |= mb_Shift;
    if (state & Qt::ControlModifier)
        flag |= mb_Control;
    if (state & Qt::AltModifier)
        flag |= mb_Alt;
    return flag;
}

//-----------------------------------------------------------------------------
//
// ---
bool QtConverterEventListener::mousePressEvent(QMouseEvent* event, QObject* watched)
{
    Q_ASSERT(m_pListenerEvent != nullptr);
    ProcessEvent::EventType type = ProcessEvent::None;
    int flags = mapModifiers(event->modifiers());
    if (event->button() == (Qt::LeftButton))
    {
        flags |= mb_LButton;
        type = ProcessEvent::LButtonDown;
    }
    else if (event->button() == (Qt::MiddleButton))
    {
        flags |= mb_MButton;
        type = ProcessEvent::MButtonDown;
    }
    else if (event->button() == (Qt::RightButton))
    {
        flags |= mb_RButton;
        type = ProcessEvent::RButtonDown;
    }
    MouseEvent processEvent(type);
    auto view = qobject_cast<QtOpenGLSceneWidget*>(watched);
    if (view && view->viewport())
        processEvent.SetViewport(view->viewport()->GetId());

    processEvent.SetFlags(flags);
    processEvent.SetScreenPos(IntPoint(event->screenPos().x(), event->screenPos().y()));
    processEvent.SetWindowPos(IntPoint(event->windowPos().x(), event->windowPos().y()));
    processEvent.SetClientPos(IntPoint(event->localPos().x(), event->localPos().y()));
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
bool QtConverterEventListener::mouseMoveEvent(QMouseEvent* event, QObject* watched)
{
    Q_ASSERT(m_pListenerEvent != nullptr);

    int flags = mapModifiers(event->modifiers());
    if (event->buttons() & Qt::LeftButton)
        flags |= mb_LButton;
    if (event->buttons() & Qt::MiddleButton)
        flags |= mb_MButton;
    if (event->buttons() & Qt::RightButton)
        flags |= mb_RButton;

    MouseEvent processEvent(ProcessEvent::MouseMove);

    auto view = qobject_cast<QtOpenGLSceneWidget*>(watched);
    if (view && view->viewport())
        processEvent.SetViewport(view->viewport()->GetId());

    processEvent.SetFlags(flags);
    processEvent.SetScreenPos(IntPoint(event->screenPos().x(), event->screenPos().y()));
    processEvent.SetWindowPos(IntPoint(event->windowPos().x(), event->windowPos().y()));
    processEvent.SetClientPos(IntPoint(event->localPos().x(), event->localPos().y()));
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;//m_pListenerEvent->OnEvent(&processEvent);
}

//-----------------------------------------------------------------------------
//
// ---
bool QtConverterEventListener::mouseReleaseEvent(QMouseEvent* event, QObject* watched)
{
    Q_ASSERT(m_pListenerEvent != nullptr);
    ProcessEvent::EventType type = ProcessEvent::None;
    int flags = mapModifiers(event->modifiers());
    if (event->button() == (Qt::LeftButton))
    {
        flags |= mb_LButton;
        type = ProcessEvent::LButtonUp;
    }
    else if (event->button() == (Qt::MiddleButton))
    {
        flags |= mb_MButton;
        type = ProcessEvent::MButtonUp;
    }
    else if (event->button() == (Qt::RightButton))
    {
        flags |= mb_RButton;
        type = ProcessEvent::RButtonUp;
    }
    MouseEvent processEvent(type);
    auto view = qobject_cast<QtOpenGLSceneWidget*>(watched);
    if (view && view->viewport())
        processEvent.SetViewport(view->viewport()->GetId());

    processEvent.SetFlags(flags);
    processEvent.SetScreenPos(IntPoint(event->screenPos().x(), event->screenPos().y()));
    processEvent.SetWindowPos(IntPoint(event->windowPos().x(), event->windowPos().y()));
    processEvent.SetClientPos(IntPoint(event->localPos().x(), event->localPos().y()));
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
bool QtConverterEventListener::mouseDoubleClickEvent(QMouseEvent* event, QObject* watched)
{
    Q_ASSERT(m_pListenerEvent != nullptr);

    ProcessEvent::EventType type = ProcessEvent::None;
    int flags = mapModifiers(event->modifiers());
    if (event->button() == (Qt::LeftButton))
    {
        flags |= mb_LButton;
        type = ProcessEvent::LButtonDblClk;
    }
    else if (event->button() == (Qt::MiddleButton))
    {
        flags |= mb_MButton;
        type = ProcessEvent::MButtonDblClk;
    }
    else if (event->button() == (Qt::RightButton))
    {
        flags |= mb_RButton;
        type = ProcessEvent::RButtonDblClk;
    }
    MouseEvent processEvent(type);
    auto view = qobject_cast<QtOpenGLSceneWidget*>(watched);
    if (view && view->viewport())
        processEvent.SetViewport(view->viewport()->GetId());

    processEvent.SetFlags(flags);
    processEvent.SetScreenPos(IntPoint(event->screenPos().x(), event->screenPos().y()));
    processEvent.SetWindowPos(IntPoint(event->windowPos().x(), event->windowPos().y()));
    processEvent.SetClientPos(IntPoint(event->localPos().x(), event->localPos().y()));
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
bool QtConverterEventListener::mouseWheelEvent(QWheelEvent* event, QObject* watched)
{
    WheelEvent processEvent;
    int flags = mapModifiers(event->modifiers());
    processEvent.SetFlags(flags);
    processEvent.SetWheelDelta(event->delta());
    processEvent.SetWindowPos(IntPoint(event->pos().x(), event->pos().y()));
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
// Перегрузка для внутренних работ.
// ---
bool QtConverterEventListener::eventFilter(QObject* watched, QEvent* event)
{
    if (watched != parent())
        return QObject::eventFilter(watched, event);

    switch (event->type())
    {
        case QEvent::KeyPress:
            return keyPressEvent(static_cast<QKeyEvent*>(event), watched);
        case QEvent::KeyRelease:
            return keyReleaseEvent(static_cast<QKeyEvent*>(event), watched);
        case QEvent::HoverMove:
            return mouseHoverEvent(static_cast<QHoverEvent*>(event), watched);
        case QEvent::MouseMove:
            return mouseMoveEvent(static_cast<QMouseEvent*>(event), watched);
        case QEvent::MouseButtonDblClick:
            return mouseDoubleClickEvent(static_cast<QMouseEvent*>(event), watched);
        case QEvent::MouseButtonPress:
            return mousePressEvent(static_cast<QMouseEvent*>(event), watched);
        case QEvent::MouseButtonRelease:
            return mouseReleaseEvent(static_cast<QMouseEvent*>(event), watched);
        case QEvent::Wheel:
            return mouseWheelEvent(static_cast<QWheelEvent*>(event), watched);
        default:
            break;
    }
    return QObject::eventFilter(watched, event);
}

//-----------------------------------------------------------------------------
//
// ---
void QtConverterEventListener::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == m_idleTimerId)
        BaseApplication::OnProcessSendPostedEvents();
    else
        QObject::timerEvent(event);
}

//-----------------------------------------------------------------------------
// 
// ---
void QtOpenGLWidgetPrivate::initialize()
{
    VSN_P(QtOpenGLWidget);
    if (m_bInitialized)
        return;
    p.makeCurrent();
    m_pQContext = new QtOpenGLContextShell(&p, m_pSharedContainer);
    m_pQContext->MakeCurrent();
    m_bInitialized = true;
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLWidgetPrivate::reset()
{
    VSN_P(QtOpenGLWidget);
    VSN_DELETE_AND_NULL(m_pQContext);
    m_bInitialized = false;
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLWidgetPrivate::renderNow()
{
    VSN_P(QtOpenGLWidget);
    QOpenGLContext* openGLContext = p.context();
    if (!openGLContext)
        return;
    p.makeCurrent();
    p.paintGL();
    openGLContext->swapBuffers(openGLContext->surface());
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLWidgetPrivate::renderLater()
{
    VSN_P(QtOpenGLWidget);
    if (!m_bUpdatePending)
    {
        m_bUpdatePending = true;
        QCoreApplication::postEvent(&p, new QEvent(QEvent::UpdateRequest));
    }
}

//-----------------------------------------------------------------------------
// Конструктор по умолчанию.
// ---
QtOpenGLWidget::QtOpenGLWidget(QWidget* parent, Qt::WindowFlags f)
    : QOpenGLWidget(parent, f)
{
    VSN_INIT_PRIVATE(QtOpenGLWidget);
}

//-----------------------------------------------------------------------------
// Конструктор по умолчанию.
// ---
QtOpenGLWidget::QtOpenGLWidget(QtOpenGLWidgetPrivate& dd, QWidget* parent, Qt::WindowFlags f)
    : QOpenGLWidget(parent, f)
{
    vsn_d_ptr = &dd;
    vsn_d_ptr->setPublic(this);
}

//-----------------------------------------------------------------------------
// Деструктор OpenGLWidget освобождает созданные ресурсы
// ---
QtOpenGLWidget::~QtOpenGLWidget()
{
    // Вылет при закрытии вкладки документа
    makeCurrent();
    VSN_FINI_PRIVATE();
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLWidget::makeCurrent()
{
    VSN_D(QtOpenGLWidget);
    if (d.m_pQContext)
        d.m_pQContext->MakeCurrent();
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLWidget::doneCurrent()
{
    VSN_D(QtOpenGLWidget);
    if (d.m_pQContext)
        d.m_pQContext->DoneCurrent();
}

//-----------------------------------------------------------------------------
// Вернуть указатель на OpenGLContextInterface.
// ---
OpenGLContextInterface* QtOpenGLWidget::contextInterface()
{
    VSN_D(QtOpenGLWidget);
    return d.m_pQContext;
}

//-----------------------------------------------------------------------------
// Просто вызывает функцию QWidget::update(). Служит для совместимости слотов.
// ---
void QtOpenGLWidget::updateWidget()
{
    update();
}

//-----------------------------------------------------------------------------
// Просто вызывает функцию QWidget::rapaint(). Служит для совместимости слотов.
// ---
void QtOpenGLWidget::repaintWidget()
{
    repaint();
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLWidget::initializeGL()
{
    VSN_D(QtOpenGLWidget);
    if (!d.m_bInitialized && window() && window()->windowHandle())
        d.initialize();
}

//-----------------------------------------------------------------------------
//
// ---
bool QtOpenGLWidget::event(QEvent* event)
{
    VSN_D(QtOpenGLWidget);
    if (event->type() == QEvent::WindowChangeInternal && d.m_bInitialized && !qGuiApp->testAttribute(Qt::AA_ShareOpenGLContexts))
        d.reset();

    bool ok = QOpenGLWidget::event(event);

    switch (event->type())
    {
        case QEvent::UpdateRequest:
            if (d.m_bUpdatePending)
            {
                update();
                d.m_bUpdatePending = false;
                return true;
            }
            break;
        case QEvent::WindowChangeInternal:
            if (qGuiApp->testAttribute(Qt::AA_ShareOpenGLContexts))
                break;
            if (d.m_bInitialized)
                d.reset();
            // FALLTHROUGH
        case QEvent::Show: // reparenting may not lead to a resize so reinitalize on Show too
            if (!d.m_bInitialized && !size().isEmpty() && window() && window()->windowHandle())
                d.initialize();
            break;
        default:
            break;
    }
    return ok;
}


/* OpenGLWidgetPrivate */
class QtOpenGLSceneWidgetPrivate : public QtOpenGLWidgetPrivate
{
    VSN_DECLARE_EX_PUBLIC(QtOpenGLSceneWidget)
public:
    explicit QtOpenGLSceneWidgetPrivate(GraphicsSceneEnginePtr ptrEngine, OpenGLContextContainer* pSharedContainer)
        : QtOpenGLWidgetPrivate(pSharedContainer)
        , m_ptrGraphicsView(std::make_shared<GraphicsView>(ptrEngine))
        , m_pEventFilter(nullptr)
        , m_bVsnInitialized(false)
    {
    }
    virtual ~QtOpenGLSceneWidgetPrivate()
    {
        m_ptrGraphicsView->GetSceneEngine()->GetObjectPickSelection()->ResetOpenGLContext(m_pQContext);
        VSN_DELETE_AND_NULL(m_pQContext);
        VSN_DELETE_AND_NULL(m_pEventFilter);
    }
    virtual void initialize() override;
public:
    void processActivation();
    void processDeactivation();
public:
    GraphicsViewPtr m_ptrGraphicsView;
    QtConverterEventListener* m_pEventFilter;
    bool m_bVsnInitialized;
};

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidgetPrivate::initialize()
{
    VSN_P(QtOpenGLSceneWidget);
    if (m_bInitialized)
        return;
    QtOpenGLWidgetPrivate::initialize();
    if (m_bVsnInitialized)
        return;

    p.setFocusPolicy(Qt::StrongFocus);
    p.setMouseTracking(true);
    p.setAttribute(Qt::WA_Hover, true);

    m_ptrGraphicsView->Initialize();
    m_pEventFilter = new QtConverterEventListener(&p);
    m_pEventFilter->setListenerEvent(m_ptrGraphicsView->GetGraphicsScene());
    Object::Connect(m_ptrGraphicsView.get(), &GraphicsView::OnViewModified, &p, &QtOpenGLWidget::repaintWidget);

    m_bVsnInitialized = true;
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidgetPrivate::processActivation()
{
    VSN_P(QtOpenGLSceneWidget);
    if (Essence* pEssence = m_ptrGraphicsView->GetSceneEngine()->GetTopEssence())
    {
        std::vector<Process*> vector = pEssence->FindChildren<Process*>();
        for (auto it = vector.begin(); it != vector.end(); ++it)
        {
			Process* pProcess = (*it);
            pProcess->SetViewport(m_ptrGraphicsView->GetViewport().get());
			bool bConnect = Object::Connect(pProcess, &Process::OnModified, &p, &QtOpenGLWidget::repaintWidget);
			Q_ASSERT(bConnect != false);

			if (PrAbstractCamera* pAbsProcess = vobject_cast<PrAbstractCamera*>(pProcess))
			{
				bConnect = Object::Connect(pAbsProcess, &PrAbstractCamera::OnCameraModified, &p, &QtOpenGLWidget::repaintWidget);
				Q_ASSERT(bConnect != false);
			}
        }
    }
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidgetPrivate::processDeactivation()
{
    VSN_P(QtOpenGLSceneWidget);
    if (Essence* pEssence = m_ptrGraphicsView->GetSceneEngine()->GetTopEssence())
    {
        std::vector<Process*> vector = pEssence->FindChildren<Process*>();
        for (auto it = vector.begin(); it != vector.end(); ++it)
        {
			Process* pProcess = (*it);
            pProcess->SetViewport(m_ptrGraphicsView->GetViewport().get());
			bool bConnect = Object::Disconnect(pProcess, &Process::OnModified, &p, &QtOpenGLWidget::repaintWidget);
//			Q_ASSERT(bConnect != false);

			if (PrAbstractCamera* pAbsProcess = vobject_cast<PrAbstractCamera*>(pProcess))
			{
				bConnect = Object::Disconnect(pAbsProcess, &PrAbstractCamera::OnCameraModified, &p, &QtOpenGLWidget::repaintWidget);
//				Q_ASSERT(bConnect != false);
			}
        }
    }
}


/* QtOpenGLSceneWidget */
QtOpenGLSceneWidget::QtOpenGLSceneWidget(QWidget* parent, Qt::WindowFlags f)
    : QtOpenGLWidget(*new QtOpenGLSceneWidgetPrivate(std::make_shared<GraphicsSceneEngine>(), nullptr), parent, f)
{
}

//-----------------------------------------------------------------------------
// Special constructor.
// ---
QtOpenGLSceneWidget::QtOpenGLSceneWidget(GraphicsSceneEnginePtr engine, OpenGLContextContainer* sharedContainer, QWidget* parent, Qt::WindowFlags f)
    : QtOpenGLWidget(*new QtOpenGLSceneWidgetPrivate(engine, sharedContainer), parent, f)
{
}

//-----------------------------------------------------------------------------
//
// ---
QtOpenGLSceneWidget::~QtOpenGLSceneWidget()
{
}

//-----------------------------------------------------------------------------
//
// ---
GraphicsScene* QtOpenGLSceneWidget::graphicsScene() const
{
    VSN_D(const QtOpenGLSceneWidget);
    return d.m_ptrGraphicsView->GetGraphicsScene();
}

//-----------------------------------------------------------------------------
// Вернуть указатель на компонент выбора объектов.
// ---
ObjectPickSelection* QtOpenGLSceneWidget::objectPickSelection() const
{
    VSN_D(const QtOpenGLSceneWidget);
    return d.m_ptrGraphicsView->GetSceneEngine()->GetObjectPickSelection();
}

//-----------------------------------------------------------------------------
// Вернуть указатель на GraphicsSceneEngine.
// ---
GraphicsSceneEnginePtr QtOpenGLSceneWidget::graphicsEngine() const
{
    VSN_D(const QtOpenGLSceneWidget);
    return d.m_ptrGraphicsView->GetSceneEngine();
}

//-----------------------------------------------------------------------------
// Вернуть указатель на GraphicsView.
// ---
GraphicsViewPtr QtOpenGLSceneWidget::graphicsView() const
{
    VSN_D(const QtOpenGLSceneWidget);
    return d.m_ptrGraphicsView;
}

//-----------------------------------------------------------------------------
// Вернуть указатель на основной источник света
// ---
Light* QtOpenGLSceneWidget::mainLight() const
{
    VSN_D(const QtOpenGLSceneWidget);
    return d.m_ptrGraphicsView->GetGraphicsScene()->GetMainLight();
}

//-----------------------------------------------------------------------------
//
// ---
Camera* QtOpenGLSceneWidget::camera() const
{
    return viewport()->GetCamera();
}

//-----------------------------------------------------------------------------
// Вернуть указатель на Viewport для отображения сцены.
// ---
Viewport* QtOpenGLSceneWidget::viewport() const
{
    VSN_D(const QtOpenGLSceneWidget);
    return d.m_ptrGraphicsView->GetViewport().get();
}

//-----------------------------------------------------------------------------
// Вернуть указатель на содержимое сцены.
// ---
SceneContentPtr QtOpenGLSceneWidget::sceneContent()
{
    VSN_D(const QtOpenGLSceneWidget);
    return d.m_ptrGraphicsView->GetGraphicsScene()->GetSceneContent();
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::resizeGL(int w, int h)
{
    VSN_D(QtOpenGLSceneWidget);
    QtOpenGLWidget::resizeGL(w, h);
    if (d.m_pQContext == nullptr)
        return;
    d.m_pQContext->MakeCurrent();
    if (OpenGLContextInterface::GetCurrentContext() && d.m_pQContext == OpenGLContextInterface::GetCurrentContext())
        d.m_ptrGraphicsView->DoResize(w, h);
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::paintGL()
{
    VSN_D(QtOpenGLSceneWidget);
    if (d.m_pQContext == nullptr)
        return;
    d.m_pQContext->MakeCurrent();
    d.m_ptrGraphicsView->DoRender();
    d.m_pQContext->DoneCurrent();
}


//-----------------------------------------------------------------------------
//
// ---
bool QtOpenGLSceneWidget::event(QEvent* event)
{
//#ifndef Q_OS_WIN
//    BaseApplication::OnProcessSendPostedEvents();
//#endif /*Q_OS_WIN*/
    return QtOpenGLWidget::event(event);
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::enterEvent(QEvent* event)
{
     VSN_D(QtOpenGLSceneWidget);
     QtOpenGLWidget::enterEvent(event);
     d.m_ptrGraphicsView->GetSceneEngine()->GetObjectPickSelection()->SetOpenGLContext(d.m_pQContext);
     d.m_ptrGraphicsView->GetSceneEngine()->GetObjectPickSelection()->SetViewport(d.m_ptrGraphicsView->GetViewport());
     d.processActivation();
}

//-----------------------------------------------------------------------------
//
// ---
 void QtOpenGLSceneWidget::leaveEvent(QEvent* event)
{
     VSN_D(QtOpenGLSceneWidget);
     QtOpenGLWidget::enterEvent(event);
     d.processDeactivation();
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::focusInEvent(QFocusEvent* event)
{
    VSN_D(QtOpenGLSceneWidget);
    QtOpenGLWidget::focusInEvent(event);
    d.processActivation();
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::focusOutEvent(QFocusEvent* event)
{
    VSN_D(QtOpenGLSceneWidget);
    QtOpenGLWidget::focusOutEvent(event);
    d.processDeactivation();
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::ZoomToFit()
{
    VSN_D(QtOpenGLSceneWidget);
    if ( viewport() && sceneContent() )
        viewport()->ZoomToFit(sceneContent()->GetBoundingBox());
}

//-----------------------------------------------------------------------------
//
// ---
bool QtOpenGLSceneWidget::OnEvent(ProcessEvent* event)
{
    if (event->GetType() == ProcessEvent::Draw)
        repaint();
    return Object::OnEvent(event);
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::showEvent(QShowEvent* event)
{
    VSN_D(QtOpenGLSceneWidget);
    if (!d.m_bVsnInitialized)
        return;
    d.m_ptrGraphicsView->PreparingToDisplay();
    d.renderLater();
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::closeEvent(QCloseEvent* event)
{
    QtOpenGLWidget::closeEvent(event);
}

//-----------------------------------------------------------------------------
// Creating processes to control the camera.
// ---
QT_FUNC(void) CreateProcessesCameraControls(Node* pParent, ProcessTypes prType)
{
    // Create and add process Orbit
    if (prType.checkFlag(pt_Orbit))
    {
        PrCameraOrbit* pProcess = new PrCameraOrbit(pParent);
        pProcess->SetMouseButtonsActivate({ VSN::mb_RButton });
    }
    // Create and add process Pan
    if (prType.checkFlag(pt_Pan))
    {
        PrCameraPan* pProcess = new PrCameraPan(pParent);
        pProcess->SetMouseButtonsActivate({ VSN::mb_MButton });
    }
    // Create and add process Zoom
    if (prType.checkFlag(pt_Zoom))
    {
        PrCameraZoom* pProcess = new PrCameraZoom(pParent);
        VSN_UNUSED(pProcess);
    }
}

//-----------------------------------------------------------------------------
// Лицензия получена
// ---
QT_FUNC(bool) isExistLicense()
{
    return IsMathVisionEnable();
}


QT_FUNC(bool) ActivateLicense( const std::string & signature, const std::string & key)
{
//    std::string key = strKey;
//    std::string signature = strSignature;

//     QProcessEnvironment procEnv = QProcessEnvironment::systemEnvironment();
//     QString envKey = procEnv.value("C3DKey");
//     QString envSignature = procEnv.value("C3Dsignature");
//     if (!envKey.isEmpty() && !envSignature.isEmpty())
//     {
//         key = envKey.toStdString();
//         signature = envSignature.toStdString();
//     }

    ::EnableMathModules(signature.c_str(), static_cast<int>(signature.length()), key.c_str(), static_cast<int>(key.length()));
    if (!IsMathVisionEnable())
    {
        //QMessageBox::warning(nullptr, QObject::tr("Warning"), QObject::tr("The evaluation period has expired. For a new license, please contact C3D Labs."));
        return false;
    }
    return true;
}

} // namespace QtVision
VSN_END_NAMESPACE