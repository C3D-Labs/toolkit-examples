#include <QApplication>
#include <QSurfaceFormat>

#include <vsn_application.h>
#include <qt_openglwidget.h>
#include <qt_exampletools.h>

#include "nurbseditor.h"

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

  std::unique_ptr<NurbsEditor> nurbsEditor;

  // build scene
  QObject::connect(pView, &QtExampleView::loadExample, [&nurbsEditor](GraphicsScene * pScene)
  {
      nurbsEditor.reset(new NurbsEditor(pScene));
  });

  ExampleWidget example("The parametric cube", pView);
  example.show();

  return app.exec();
}
