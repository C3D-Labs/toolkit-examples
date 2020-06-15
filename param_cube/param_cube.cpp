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
AppParametricCubePlan::AppParametricCubePlan(const MbPlacement3D & place,
                                             const ParamCubeProps & rect, const ParamHoleProps & hole)
  : sketch(nullptr)
  , sideX(nullptr)
  , sideY(nullptr)
  , holes()
  , controls()
{
  // Rectangle sides.
  sketch = std::make_shared<AppParametricSketch>(place);
  const MbCartPoint vertA(0., 0.), vertB(rect.length, 0.), vertC(rect.length, rect.width), vertD(0., rect.width);
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
  const double centerIndent = hole.radius + hole.centerIndent;
  SPtr<MbArc> circle(new MbArc(MbCartPoint(centerIndent, centerIndent), hole.radius));
  auto holeA = _AddHoleInCorner(*circle, *sideX, *sideY, centerIndent);
  controls["holeR"] = sketch->Fix(*holeA, GCE_RADIUS_DIM);

  circle = new MbArc(MbCartPoint(rect.length - centerIndent, centerIndent), hole.radius);
  auto holeB = _AddHoleInCorner(*circle, *sideX, *lsegBC, centerIndent);
  sketch->Equality(*holeA, *holeB, GCE_EQUAL_RADIUS);

  circle = new MbArc(MbCartPoint(rect.length - centerIndent, rect.width - centerIndent), hole.radius);
  auto holeC = _AddHoleInCorner(*circle, *lsegBC, *lsegCD, centerIndent);
  sketch->Equality(*holeA, *holeC, GCE_EQUAL_RADIUS);

  circle = new MbArc(MbCartPoint(centerIndent, rect.width - centerIndent), hole.radius);
  auto holeD = _AddHoleInCorner(*circle, *lsegCD, *sideY, centerIndent);
  sketch->Equality(*holeA, *holeD, GCE_EQUAL_RADIUS);
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
  return GCE_RESULT_Ok == sketch->ChangeDimension(*controls["lengthX"], lenX);
}

//----------------------------------------------------------------------------------------
//
// ---
bool AppParametricCubePlan::ChangeLengthY(double lenY)
{
  return GCE_RESULT_Ok == sketch->ChangeDimension(*controls["lengthY"], lenY);
}

//----------------------------------------------------------------------------------------
//
// ---
bool AppParametricCubePlan::ChangeHoleRadius(double rad)
{
  return GCE_RESULT_Ok == sketch->ChangeDimension(*controls["holeR"], rad);
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
                                     const ParamCubeProps & cube, const ParamHoleProps & hole)
  : paramCube(nullptr)
  , paramPlan(nullptr)
  , cubeProps(cube)
  , holeProps(hole)
{
  paramPlan = std::make_shared<AppParametricCubePlan>(MbPlacement3D::global, cubeProps, holeProps);
  SPtr<MbSolid> solid = BuildSolid();
  if (solid != nullptr)
  {
    paramCube = new MbInstance(*solid, place);
    paramCube->SetColor(120, 0, 0);
  }
}

//----------------------------------------------------------------------------------------
//
// ---
bool AppParametricCube::ChangeLengthX(double lenX)
{
  if (paramPlan->ChangeLengthX(lenX))
  {
    cubeProps.length = lenX;
    return true;
  }
  return false;
}

//----------------------------------------------------------------------------------------
//
// ---
bool AppParametricCube::ChangeLengthY(double lenY)
{
  if(paramPlan->ChangeLengthY(lenY))
  {
    cubeProps.width = lenY;
    return true;
  }
  return false;
}

//----------------------------------------------------------------------------------------
//
// ---
bool AppParametricCube::ChangeLengthZ(double lenZ)
{
  cubeProps.height = lenZ;
  return true;
}

//----------------------------------------------------------------------------------------
//
// ---
bool AppParametricCube::ChangeHoleRadius(double rad)
{
  if(paramPlan->ChangeHoleRadius(rad))
  {
    holeProps.radius = rad;
    return true;
  }
  return false;
}

//----------------------------------------------------------------------------------------
//
// ---
bool AppParametricCube::ChangeHoleDepth(double depth)
{
  holeProps.depth = depth;
  return true;
}

//----------------------------------------------------------------------------------------
//
// ---
bool AppParametricCube::RebuildSolid()
{
  auto solid = BuildSolid();
  if (solid != nullptr)
  {
      paramCube->ReplaceItem(*paramCube->GetItem(), *solid, true);
      return true;
  }
  return false;
}

//----------------------------------------------------------------------------------------
// Код примерный, требует уточнения.
// ---
SPtr<MbSolid> AppParametricCube::BuildSolid() const
{
  // First we must calculate plan to apply all changes from invoking AppParametricCube::ChangeXXX functions
  paramPlan->Calculate();
  // Creating solid cube
  auto sideX = paramPlan->GetSideX();
  auto sideY = paramPlan->GetSideY();
  SPtr<MbSolid> solid = AppParametricCube::CreateCube(*sideX, *sideY, cubeProps.height);
  if (solid != nullptr)
  {
    // Creating holes in cube
    for (auto && hole : paramPlan->GetHoles())
    {
      SPtr<MbSolid> cylinder = AppParametricCube::CreateCylinder(*hole, holeProps.depth);
      if (cylinder != nullptr)
      {
        MbSolid * tmpSolid = nullptr;
        SPtr<MbSolid> cube = solid;
        MbSNameMaker names(ct_BooleanSolid, MbSNameMaker::i_SideNone, 0);
        if(rt_Success == ::BooleanSolid(*cube, cm_Copy, *cylinder, cm_Copy, bo_Difference, names, tmpSolid))
        {
          solid = tmpSolid;
        }
      }
    }
  }

  return solid;
}

//----------------------------------------------------------------------------------------
//
// ---
SPtr<MbSolid> AppParametricCube::CreateCube(const MbLineSegment & sideX, const MbLineSegment & sideY, double height)
{
  SArray<MbCartPoint3D> cubePnts(4, 1);
  MbCartPoint3D p;
  p.Init(sideX.GetPoint1()); cubePnts.push_back(p);
  p.Init(sideX.GetPoint2()); cubePnts.push_back(p);
  p.Init(sideY.GetPoint1()); cubePnts.push_back(p);
  p.Init(0., 0., height);    cubePnts.push_back(p);
  MbSolid * cube = nullptr;
  MbSNameMaker names(-1, MbSNameMaker::i_SideNone, 0);
  ::ElementarySolid(cubePnts, et_Block, names, cube);
  return SPtr<MbSolid>(cube);
}

//----------------------------------------------------------------------------------------
//
// ---
SPtr<MbSolid> AppParametricCube::CreateCylinder(const MbArc & xyPlane, double height)
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
