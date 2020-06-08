//
// Created by redcat1
//

#include "param_cube.h"
#include <param_geom_node.h>
#include <param_constraint_node.h>
#include <param_sketch.h>

#include <cur_arc.h>
#include <action_solid.h>

//----------------------------------------------------------------------------------------
//
// ---
AppParametricCubePlan::AppParametricCubePlan(const MbPlacement3D & place, double length, double width,
                                             double holeRadius, double holeIndent)
  : sketch(nullptr)
  , controls()
{
  // Rectangle sides.
  sketch = std::make_shared<AppParametricSketch>(place);
  const MbCartPoint vertA(0., 0.), vertB(length, 0.), vertC(length, width), vertD(0., width);
  auto lsegAB = _AddRectangleSide(vertA, vertB);
  auto lsegBC = _AddRectangleSide(vertB, vertC);
  auto lsegCD = _AddRectangleSide(vertC, vertD);
  auto lsegDA = _AddRectangleSide(vertD, vertA);

  // Setting constraints on rectangle elements.
  const auto originPnt = sketch->GetControlPoint(*lsegAB, GCE_FIRST_END);
  sketch->Fix(originPnt, GCE_FIX_GEOM);
  controls["lengthX"] = sketch->Fix(*lsegAB, GCE_LENGTH);
  controls["lengthY"] = sketch->Fix(*lsegDA, GCE_LENGTH);

  sketch->ConnectSegments(*lsegAB, *lsegBC);
  sketch->ConnectSegments(*lsegBC, *lsegCD);
  sketch->ConnectSegments(*lsegCD, *lsegDA);
  sketch->ConnectSegments(*lsegDA, *lsegAB);

  sketch->Align(*lsegAB, GCE_HORIZONTAL);
  sketch->Align(*lsegDA, GCE_VERTICAL);
  sketch->Perpendicular(*lsegAB, *lsegBC);
  sketch->Parallel(*lsegAB, *lsegCD);

  // Create holes in each corner.
  const double centerIndent = holeRadius + holeIndent;
  SPtr<MbArc> circle(new MbArc(MbCartPoint(centerIndent, centerIndent), holeRadius));
  auto holeA = _AddHoleInCorner(*circle, *lsegAB, *lsegDA, centerIndent);
  controls["holeR"] = sketch->Fix(*holeA, GCE_RADIUS_DIM);

  circle = new MbArc(MbCartPoint(length - centerIndent, centerIndent), holeRadius);
  auto holeB = _AddHoleInCorner(*circle, *lsegAB, *lsegBC, centerIndent);
  sketch->Equality(*holeA, *holeB, GCE_EQUAL_RADIUS);

  circle = new MbArc(MbCartPoint(length - centerIndent, width - centerIndent), holeRadius);
  auto holeC = _AddHoleInCorner(*circle, *lsegBC, *lsegCD, centerIndent);
  sketch->Equality(*holeA, *holeC, GCE_EQUAL_RADIUS);

  circle = new MbArc(MbCartPoint(centerIndent, width - centerIndent), holeRadius);
  auto holeD = _AddHoleInCorner(*circle, *lsegCD, *lsegDA, centerIndent);
  sketch->Equality(*holeA, *holeD, GCE_EQUAL_RADIUS);

  Calculate();
}

//----------------------------------------------------------------------------------------
//
// ---
AppParametricCubePlan::GeomNodePtr
AppParametricCubePlan::_AddRectangleSide(const MbCartPoint & p1, const MbCartPoint & p2)
{
  SPtr<MbLineSegment> lseg(new MbLineSegment(p1, p2));
  return sketch->AddLineSegment(*lseg);
}

//----------------------------------------------------------------------------------------
//
// ---
AppParametricCubePlan::GeomNodePtr
AppParametricCubePlan::_AddHoleInCorner(MbArc & circle, GeomNodeCRef side1, GeomNodeCRef side2, double indent)
{
  auto hole = sketch->AddCircle(circle);
  auto center = sketch->GetControlPoint(*hole, GCE_CENTRE);
  sketch->Distance(center, side1, indent);
  sketch->Distance(center, side2, indent);
  return hole;
}

//----------------------------------------------------------------------------------------
//
// ---
bool AppParametricCubePlan::ChangeLengthX(double lenX)
{
  const GCE_result result = sketch->ChangeDimension(*controls["lenX"], lenX);
  return OK(result) ? GCE_RESULT_Ok == Calculate() : false;
}

//----------------------------------------------------------------------------------------
//
// ---
bool AppParametricCubePlan::ChangeLengthY(double lenY)
{
  const GCE_result result = sketch->ChangeDimension(*controls["lenY"], lenY);
  return OK(result) ? GCE_RESULT_Ok == Calculate() : false;
}

//----------------------------------------------------------------------------------------
//
// ---
bool AppParametricCubePlan::ChangeHoleRadius(double rad)
{
  const GCE_result result = sketch->ChangeDimension(*controls["holeR"], rad);
  return OK(result) ? GCE_RESULT_Ok == Calculate() : false;
}

//----------------------------------------------------------------------------------------
//
// ---
GCE_result AppParametricCubePlan::Calculate()
{
  return sketch->Evaluate();
}

//----------------------------------------------------------------------------------------
//
// ---
AppParametricCube::AppParametricCube(const MbPlacement3D & place,
                                     double length, double width, double height,
                                     double holeRadius, double holeIndent, double)
  : cube(nullptr)
  , paramPlan(nullptr)
{
  paramPlan = std::make_shared<AppParametricCubePlan>(place, length, width, holeRadius, holeIndent);

  MbSolid * solid = nullptr;
  MbSNameMaker names1(-1, MbSNameMaker::i_SideNone, 0);
  SArray<MbCartPoint3D> points(4, 1);
  points.push_back(place.GetOrigin());
  points.push_back(place.GetOrigin() + place.GetAxisX()*length);
  points.push_back(place.GetOrigin() + place.GetAxisY()*width);
  points.push_back(place.GetOrigin() + place.GetAxisZ()*height);
  ::ElementarySolid(points, et_Block, names1, solid);
  cube = solid;
  // mdlrWall = new MbInstance(*solid, place);
}

//----------------------------------------------------------------------------------------
//
// ---
bool AppParametricCube::ChangeLengthX(double lenX)
{
  bool res = paramPlan->ChangeLengthX(lenX);
  // тут перестраиваем кубик по обновлённому эскизу

  return res;
}

//----------------------------------------------------------------------------------------
//
// ---
bool AppParametricCube::ChangeLengthY(double lenY)
{
  bool res = paramPlan->ChangeLengthY(lenY);
  // тут перестраиваем кубик по обновлённому эскизу

  return res;
}

//----------------------------------------------------------------------------------------
//
// ---
bool AppParametricCube::ChangeLengthZ(double lenZ)
{
  // тут перестраиваем кубик. обновлять 2D эскиз не нужно
  return false;
}

//----------------------------------------------------------------------------------------
//
// ---
bool AppParametricCube::ChangeHoleRadius(double rad)
{
  bool res = paramPlan->ChangeHoleRadius(rad);
  // тут перестраиваем кубик по обновлённому эскизу

  return res;
}
