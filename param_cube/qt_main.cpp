#include <QApplication>
#include <QSurfaceFormat>

#include <vsn_application.h>
#include <qt_openglwidget.h>
#include <qt_exampletools.h>

#include <param_cube.h>
#include <mb_placement3d.h>


std::shared_ptr<AppParametricCube> g_paramModel;
SceneSegment * g_pMathSegment = nullptr;

//----------------------------------------------------------------------------------------
//
// ---
void buildVisualSegment(const MbItem * pItem, SceneSegment * parent)
{
  if (g_paramModel)
  {
    delete g_pMathSegment;
    auto pRep = SceneGenerator::Instance()->CreateMathRep(pItem, MathGeometry::Synchronous);
    g_pMathSegment = new SceneSegment(pRep, parent);
  }
}

//----------------------------------------------------------------------------------------
//
// ---
void LoadExampleScene(GraphicsScene * pGraphScene)
{
  const MbPlacement3D xyPlane;
  ParamCubeProps cubeProps{100., 80., 150.};
  ParamHoleProps holeProps{15., 30., 5.};
  g_paramModel = std::make_shared<AppParametricCube>(xyPlane, cubeProps, holeProps);

  buildVisualSegment(g_paramModel->SolidItem(), pGraphScene->GetSceneContent()->GetRootSegment());

  pGraphScene->GetViewport()->GetCamera()->SetViewOrientation(VSN_NAMESPACE::Rear);
}


//----------------------------------------------------------------------------------------
//
// ---
int main(int argc, char** argv)
{
  Application vapp;
  QApplication app(argc, argv);
  InitQApplication(app);

  // prepare view
  Color color(74, 74, 74);
  QtExampleView * pView = new QtExampleView(color);

  // build scene
  QObject::connect(pView, &QtExampleView::loadExample, std::bind(&LoadExampleScene, std::placeholders::_1));

  ExampleWidget example("The parametric cube", pView);

  auto pLenghtEd = example.spinbox("Block length", 80, 0.0, 500.0, 1.0);
  auto pHeightEd = example.spinbox("Block height", 150.0, 0.0, 500.0, 1.0);
  auto pWidthEd  = example.spinbox("Block width", 100.0, 0.0, 500.0, 1.0);

  auto pHoleRadiusEd = example.spinbox("Holes radius", 15.0);
  auto pHoleDepthEd  = example.spinbox("Holes depth", 30.0, 0.0, 500.0, 1.0);
  //auto pHoleIndentEd = example.spinbox("holeIndent", 5.0);

  /// rebuild geometry button
  QObject::connect(example.button("Recalculate"), &QPushButton::clicked, [&]()
      {
        g_paramModel->ChangeLengthX(pWidthEd->value());
        g_paramModel->ChangeLengthY(pLenghtEd->value());
        g_paramModel->ChangeLengthZ(pHeightEd->value());
        g_paramModel->ChangeHoleRadius(pHoleRadiusEd->value());
        g_paramModel->ChangeHoleDepth(pHoleDepthEd->value());

        if (g_paramModel->RebuildSolid())
        {
            buildVisualSegment(g_paramModel->SolidItem(), pView->sceneContent()->GetRootSegment());
            pView->update();
        }
      });

  example.show();

  return app.exec();
}
