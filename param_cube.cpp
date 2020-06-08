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
  , sideX(nullptr)
  , sideY(nullptr)
  , holes()
  , controls()
{
  // Rectangle sides.
  sketch = std::make_shared<AppParametricSketch>(place);
  const MbCartPoint vertA(0., 0.), vertB(length, 0.), vertC(length, width), vertD(0., width);
  sideX = _AddRectangleSide(vertA, vertB);  // lsegAB
  auto lsegBC = _AddRectangleSide(vertB, vertC);
  auto lsegCD = _AddRectangleSide(vertC, vertD);
  sideY = _AddRectangleSide(vertD, vertA);  // sideY

  // Setting constraints on rectangle elements.
  const auto originPnt = sketch->GetControlPoint(*sideX, GCE_FIRST_END);
  sketch->Fix(originPnt, GCE_FIX_GEOM);
  controls["lengthX"] = sketch->Fix(*sideX, GCE_LENGTH);
  controls["lengthY"] = sketch->Fix(*sideY, GCE_LENGTH);

  sketch->ConnectSegments(*sideX, *lsegBC);
  sketch->ConnectSegments(*lsegBC, *lsegCD);
  sketch->ConnectSegments(*lsegCD, *sideY);
  sketch->ConnectSegments(*sideY, *sideX);

  sketch->Align(*sideX, GCE_HORIZONTAL);
  sketch->Align(*sideY, GCE_VERTICAL);
  sketch->Perpendicular(*sideX, *lsegBC);
  sketch->Parallel(*sideX, *lsegCD);

  // Create holes in each corner.
  const double centerIndent = holeRadius + holeIndent;
  SPtr<MbArc> circle(new MbArc(MbCartPoint(centerIndent, centerIndent), holeRadius));
  auto holeA = _AddHoleInCorner(*circle, *sideX, *sideY, centerIndent);
  controls["holeR"] = sketch->Fix(*holeA, GCE_RADIUS_DIM);

  circle = new MbArc(MbCartPoint(length - centerIndent, centerIndent), holeRadius);
  auto holeB = _AddHoleInCorner(*circle, *sideX, *lsegBC, centerIndent);
  sketch->Equality(*holeA, *holeB, GCE_EQUAL_RADIUS);

  circle = new MbArc(MbCartPoint(length - centerIndent, width - centerIndent), holeRadius);
  auto holeC = _AddHoleInCorner(*circle, *lsegBC, *lsegCD, centerIndent);
  sketch->Equality(*holeA, *holeC, GCE_EQUAL_RADIUS);

  circle = new MbArc(MbCartPoint(centerIndent, width - centerIndent), holeRadius);
  auto holeD = _AddHoleInCorner(*circle, *lsegCD, *sideY, centerIndent);
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
  holes.push_back(hole);
  return holes.back();
}

//----------------------------------------------------------------------------------------
//
// ---
bool AppParametricCubePlan::ChangeLengthX(double lenX)
{
  const GCE_result result = sketch->ChangeDimension(*controls["lengthX"], lenX);
  return OK(result) ? GCE_RESULT_Ok == Calculate() : false;
}

//----------------------------------------------------------------------------------------
//
// ---
bool AppParametricCubePlan::ChangeLengthY(double lenY)
{
  const GCE_result result = sketch->ChangeDimension(*controls["lengthY"], lenY);
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
SPtr<MbLineSegment> AppParametricCubePlan::GetSideX() const
{
  const MbCartPoint p1 = sketch->GetPointValue(*sideX, GCE_FIRST_END);
  const MbCartPoint p2 = sketch->GetPointValue(*sideX, GCE_SECOND_END);
  return SPtr<MbLineSegment>(new MbLineSegment(p1, p2));
}

//----------------------------------------------------------------------------------------
//
// ---
SPtr<MbLineSegment> AppParametricCubePlan::GetSideY() const
{
  const MbCartPoint p1 = sketch->GetPointValue(*sideY, GCE_FIRST_END);
  const MbCartPoint p2 = sketch->GetPointValue(*sideY, GCE_SECOND_END);
  return SPtr<MbLineSegment>(new MbLineSegment(p1, p2));
}

//----------------------------------------------------------------------------------------
//
// ---
std::vector<SPtr<MbArc>> AppParametricCubePlan::GetHoles() const
{
  std::vector<SPtr<MbArc>> mdlrHoles;
  for (auto && hole : holes)
  {
    const MbCartPoint center = sketch->GetPointValue(*hole, GCE_CENTRE);
    const double radius = sketch->GetCoordValue(*hole, GCE_RADIUS);
    mdlrHoles.emplace_back(new MbArc(center, radius));
  }
  return mdlrHoles;
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
                                     double holeRadius, double holeIndent, double holeDepth)
  : paramCube(nullptr)
  , paramPlan(nullptr)
{
  paramPlan = std::make_shared<AppParametricCubePlan>(MbPlacement3D::global, length, width, holeRadius, holeIndent);
  SPtr<MbSolid> solid = _CreateSolidWithHoles(height, holeDepth);
  paramCube = new MbInstance(*solid, place);
}

//----------------------------------------------------------------------------------------
//
// ---
bool AppParametricCube::ChangeLengthX(double lenX)
{
  bool res = paramPlan->ChangeLengthX(lenX);
  // тут перестраиваем кубик по обновлённому эскизу
  // должен быть вызван аналог функции _CreateSolidWithHoles

  return res;
}

//----------------------------------------------------------------------------------------
//
// ---
bool AppParametricCube::ChangeLengthY(double lenY)
{
  bool res = paramPlan->ChangeLengthY(lenY);
  // тут перестраиваем кубик по обновлённому эскизу
  // должен быть вызван аналог функции _CreateSolidWithHoles

  return res;
}

//----------------------------------------------------------------------------------------
//
// ---
bool AppParametricCube::ChangeLengthZ(double lenZ)
{
  // тут перестраиваем кубик без задействования параметризации.
  // хотя обновлять 2D эскиз не нужно, можно использовать для перестроения ту же функцию,
  // что и в ChangeLengthX, ChangeLengthY, ChangeHoleRadius
  return false;
}

//----------------------------------------------------------------------------------------
//
// ---
bool AppParametricCube::ChangeHoleRadius(double rad)
{
  bool res = paramPlan->ChangeHoleRadius(rad);

  // тут перестраиваем кубик по обновлённому эскизу
  // должен быть вызван аналог функции _CreateSolidWithHoles

  return res;
}

//----------------------------------------------------------------------------------------
// Код примерный, требует уточнения.
// ---
SPtr<MbSolid> AppParametricCube::_CreateSolidWithHoles(double height, double holeDepth) const
{
  // Get a rectangle actual state from 2D sketch
  auto lsegX = paramPlan->GetSideX();
  auto lsegY = paramPlan->GetSideY();
  auto holes = paramPlan->GetHoles();
  // Creating solid
  SPtr<MbSolid> solid = _CreateCube(*lsegX, *lsegY, height);
  // Creating holes
  for (auto && hole : holes)
  {
    SPtr<MbSolid> cylinder = _CreateCylinder(*hole, holeDepth);
    if (cylinder != nullptr)
    {
      MbSolid * tmpSolid = nullptr;
      SPtr<MbSolid> cube = solid;
      MbSNameMaker names(ct_BooleanSolid, MbSNameMaker::i_SideNone, 0);
      ::BooleanSolid(*cube, cm_Copy, *cylinder, cm_Copy, bo_Difference, names, tmpSolid);
      solid = tmpSolid;
    }
  }

  return solid;
}

//----------------------------------------------------------------------------------------
//
// ---
SPtr<MbSolid>
    AppParametricCube::_CreateCube(const MbLineSegment & axisX, const MbLineSegment & axisY, double height) const
{
  SArray<MbCartPoint3D> cubePnts(4, 1);
  MbCartPoint3D p;
  p.Init(axisX.GetPoint1()); cubePnts.push_back(p);
  p.Init(axisX.GetPoint2()); cubePnts.push_back(p);
  p.Init(axisY.GetPoint1()); cubePnts.push_back(p);
  p.Init(0., 0., height);   cubePnts.push_back(p);
  MbSolid * cube = nullptr;
  MbSNameMaker names(-1, MbSNameMaker::i_SideNone, 0);
  ::ElementarySolid(cubePnts, et_Block, names, cube);
  return SPtr<MbSolid>(cube);
}

//----------------------------------------------------------------------------------------
//
// ---
SPtr<MbSolid> AppParametricCube::_CreateCylinder(const MbArc & xyPlane, double height) const
{
  SArray<MbCartPoint3D> cylinderPnts(3, 1);
  auto center = xyPlane.GetCentre();
  cylinderPnts.push_back(MbCartPoint3D(center.x, center.y, 0.));
  cylinderPnts.push_back(MbCartPoint3D(center.x, center.y, height));
  cylinderPnts.push_back(MbCartPoint3D(center.x + xyPlane.GetRadius(), center.y, 0.));
  MbSolid * cylinder = nullptr;
  MbSNameMaker names(-1, MbSNameMaker::i_SideNone, 0);
  ::ElementarySolid(cylinderPnts, et_Cylinder, names, cylinder);
  return SPtr<MbSolid>(cylinder);
}
