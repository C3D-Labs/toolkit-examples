#pragma once
#include <QApplication>
#include <qt_openglwidget.h>

#include <tool_enabler.h>

void InitQApplication(QApplication & app)
{
    app.setApplicationName("Parametric cube");
    app.setOrganizationName("C3DLabs");

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setSamples(4);
    QSurfaceFormat::setDefaultFormat(format);
}

class QT_CLASS QtExampleView : public QtVision::QtOpenGLSceneWidget
{
    Q_OBJECT
public:
    QtExampleView(VSN::Color & background)
    {
        viewport()->SetBackgroundColour(background);
        QtVision::CreateProcessesCameraControls(graphicsEngine()->GetTopEssence(), QtVision::pt_AllProcess);

        Object::Connect(viewport(), &Viewport::RefreshScreen, this, &QtOpenGLWidget::repaintWidget);
    }

public:
    virtual void initializeGL() override
    {
        QtVision::QtOpenGLSceneWidget::initializeGL();

        m_loadedGl = true;
        if (m_activateKey && m_loadedGl)
        {
            emit loadExample(graphicsScene());
            ZoomToFit();
        }
    }

    void activateKey()
    {
        m_activateKey = IsMathVisionEnable();
        if (m_activateKey && m_loadedGl)
        {
            emit loadExample(graphicsScene());
            ZoomToFit();
        }
    }
signals:
   void loadExample(GraphicsScene * scene);

private:
    bool m_loadedGl = false;
    bool m_activateKey = false;
};