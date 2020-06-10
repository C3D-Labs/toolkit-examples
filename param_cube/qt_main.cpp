#include <QApplication>
#include <QDesktopWidget>
#include <QSurfaceFormat>

#include <vsn_application.h>
#include <qt_openglwidget.h>
#include <qt_exampletools.h>

// ---
int main(int argc, char** argv)
{
    Application vapp;
    QApplication app(argc, argv);
    app.setApplicationName("Parametric cube");
    app.setOrganizationName("C3DLabs");

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setSamples(4);
    QSurfaceFormat::setDefaultFormat(format);

    // prepare view
    auto view = new QtVision::QtOpenGLSceneWidget();
    view->viewport()->SetBackgroundColour(Color(74, 74, 74));
    QtVision::CreateProcessesCameraControls(view->graphicsEngine()->GetTopEssence(), QtVision::pt_AllProcess);

    ExampleWidget example("The parametric cube", view);

    example.spinbox("Length", 10.0);
    example.spinbox("Height", 10.0);
    example.spinbox("Width", 10.0);
    example.button("Recalculate");



    example.move(QPoint(200, 200));
    QRect geom = QApplication::desktop()->availableGeometry();
    example.resize(2 * geom.width() / 3, 2 * geom.height() / 3);
    example.show();

    return app.exec();
}
