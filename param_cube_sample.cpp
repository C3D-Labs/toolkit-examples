//
// Created by redcat1
//

#include "param_cube_sample.h"
#include <param_cube.h>

#include <mb_placement3d.h>
#include <system_dependency_utils.h>
#include <test_variables.h>
#include <test_manager.h>

//----------------------------------------------------------------------------------------
//
// ---
void ShowCube()
{
  const MbPlacement3D xyPlane;
  auto paramCube = std::make_shared<AppParametricCube>(xyPlane, 100., 80., 150., 15., 5., 30.);
  TestVariables::viewManager->AddObject(Style(1, RGB( 0, 0, 200)), paramCube->SolidItem());
  // Show cube
  paramCube->ChangeLengthX(110.);
  TestVariables::viewManager->RedrawObject(paramCube->SolidItem());
  // Show cube
  paramCube->ChangeLengthY(90.);
  TestVariables::viewManager->RedrawObject(paramCube->SolidItem());
  // Show cube
  paramCube->ChangeLengthZ(125.);
  TestVariables::viewManager->RedrawObject(paramCube->SolidItem());
  // Show cube
  paramCube->ChangeHoleRadius(10.);
  TestVariables::viewManager->RedrawObject(paramCube->SolidItem());
  TestVariables::viewManager->RefreshModel();
  // Show cube
}
