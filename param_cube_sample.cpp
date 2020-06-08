//
// Created by redcat1
//

#include "param_cube_sample.h"
#include <param_cube.h>

#include <mb_placement3d.h>
#include <system_dependency_utils.h>

//----------------------------------------------------------------------------------------
//
// ---
void ShowCube()
{
  const MbPlacement3D xyPlane;
  auto paramCube = std::make_shared<AppParametricCube>(xyPlane, 100., 100., 100., 15., 5., 30.);
  // Show cube
  SleepCP(2000);
  paramCube->ChangeLengthX(110.);
  // Show cube
  SleepCP(2000);
  paramCube->ChangeLengthY(90.);
  // Show cube
  SleepCP(2000);
  paramCube->ChangeLengthY(125.);
  // Show cube
  SleepCP(2000);
  paramCube->ChangeHoleRadius(10.);
  // Show cube
  //TestVariables::viewManager->RedrawObject(sketch->SketchItem());
}
