#include <QApplication>
#include <QDesktopWidget>
#include <QSurfaceFormat>

#include <vsn_application.h>
#include <qt_openglwidget.h>
#include <qt_exampletools.h>

#include <param_cube.h>
#include <mb_placement3d.h>



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

    auto pLenghtEd = example.spinbox("Length", 80, 0.0, 500.0, 1.0);
    auto pHeightEd = example.spinbox("Height", 150.0, 0.0, 500.0, 1.0);
    auto pWidthEd  = example.spinbox("Width", 100.0, 0.0, 500.0, 1.0);

    auto pHoleRadiusEd = example.spinbox("holeRadius", 15.0);
    //auto pHoleIndentEd = example.spinbox("holeIndent", 5.0);
    auto pHoleDepthEd  = example.spinbox("holeDepth", 30.0, 0.0, 500.0, 1.0);

    const MbPlacement3D xyPlane;
    auto paramCube = std::make_shared<AppParametricCube>(xyPlane, 100., 80., 150., 15., 5., 30.);

    SceneSegment * root = view->sceneContent()->GetRootSegment();
    SceneSegment * pMathSegment = nullptr;
    
    auto recreater = [root, &pMathSegment](const MbItem * pItem) {
        delete pMathSegment;
        auto pRep = SceneGenerator::Instance()->CreateMathRep(pItem, MathGeometry::Synchronous);
        pMathSegment = new SceneSegment(pRep, root);
    };
    
    recreater(paramCube->SolidItem());
    view->ZoomToFit();

    /// rebuild geometry
    QObject::connect(example.button("Recalculate"), &QPushButton::clicked, [&]()
    {
        paramCube->ChangeLengthX(pLenghtEd->value());
        paramCube->ChangeLengthY(pWidthEd->value());
        paramCube->ChangeLengthZ(pHeightEd->value());
        paramCube->ChangeHoleRadius(pHoleRadiusEd->value());

        if (paramCube->RebuildSolid(pHeightEd->value(), pHoleDepthEd->value()))
        {
            recreater(paramCube->SolidItem());
            view->ZoomToFit();
            view->update();
        }
    });

    example.move(QPoint(200, 200));
    QRect geom = QApplication::desktop()->availableGeometry();
    example.resize(2 * geom.width() / 3, 2 * geom.height() / 3);
    example.show();

    return app.exec();
}
