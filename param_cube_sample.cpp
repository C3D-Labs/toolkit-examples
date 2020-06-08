//
// Created by redcat1
//

#include "param_cube_sample.h"
#include <param_cube.h>

#include <mb_placement3d.h>

//----------------------------------------------------------------------------------------
//
// ---
void ShowCube()
{
  const MbPlacement3D xyPlane;
  auto paramCube = std::make_shared<AppParametricCube>(xyPlane, 100., 100., 100., 15., 5., 30.);
  // Show cube
  paramCube->ChangeLengthX(110.);
  // Show cube
  paramCube->ChangeLengthY(90.);
  // Show cube
  paramCube->ChangeLengthY(125.);
  // Show cube
  paramCube->ChangeHoleRadius(10.);
  // Show cube
  //TestVariables::viewManager->RedrawObject(sketch->SketchItem());
}
