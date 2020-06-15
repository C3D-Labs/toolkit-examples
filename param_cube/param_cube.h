//
// Created by redcat1
//

#ifndef PARAM_CUBE_H
#define PARAM_CUBE_H

#include <memory>
#include <unordered_map>
#include <templ_sptr.h>
#include <gce_types.h>
#include <instance.h>

class MbArc;
class AppGeomNode;
class AppConstraintNode;
class AppParametricSketch;

/**
 *  Parametric cube properties.
 */
struct ParamCubeProps
{
  double length;
  double width;
  double height;
};

/**
 *  Parametric hole properties.
 *  @param depth - hole depth in cube.
 *  @param centerIndent - indent of hole center from cube closest edges.
 */
struct ParamHoleProps
{
  double radius;
  double depth;
  double centerIndent;
};

//----------------------------------------------------------------------------------------
//
// ---
class AppParametricCubePlan
{
  using GeomNodePtr  = std::shared_ptr<AppGeomNode>;
  using GeomNodeCRef = const AppGeomNode &;
  using PlanHoles    = std::vector<GeomNodePtr>;
  using PlanControls = std::unordered_map<std::string, std::shared_ptr<AppConstraintNode>>;


  std::shared_ptr<AppParametricSketch> sketch;
  GeomNodePtr                          sideX;
  GeomNodePtr                          sideY;
  PlanHoles                            holes;
  PlanControls                         controls;

public:
  AppParametricCubePlan(const MbPlacement3D & place, const ParamCubeProps &, const ParamHoleProps &);
  ~AppParametricCubePlan() = default;

public:
  /**Solve system of equations and update state of sketch geometry.*/
  GCE_result               Calculate();
  // Functions for controlling the plan.
  bool                     ChangeLengthX(double lenX);
  bool                     ChangeLengthY(double lenY);
  bool                     ChangeHoleRadius(double rad);

  SPtr<MbLineSegment>      GetSideX() const;
  SPtr<MbLineSegment>      GetSideY() const;
  std::vector<SPtr<MbArc>> GetHoles() const;

private:
  GeomNodePtr              _AddRectangleSide(const MbCartPoint &, const MbCartPoint &);
  GeomNodePtr              _AddHoleInCorner(MbArc & circle, GeomNodeCRef side1, GeomNodeCRef side2, double indent);

public:
  AppParametricCubePlan(const AppParametricCubePlan &) = delete;
  AppParametricCubePlan & operator = (const AppParametricCubePlan &) = delete;
};

//----------------------------------------------------------------------------------------
//
// ---
class AppParametricCube
{
  SPtr<MbInstance>                       paramCube;
  std::shared_ptr<AppParametricCubePlan> paramPlan;  // It is defined in cube's XY plane
  ParamCubeProps                         cubeProps;
  ParamHoleProps                         holeProps;

public:
  AppParametricCube(const MbPlacement3D & place, const ParamCubeProps &, const ParamHoleProps &);
  ~AppParametricCube() = default;

public:
  SPtr<MbInstance> SolidItem() const { return paramCube; }
  bool             RebuildSolid();
  // Functions for controlling the parametric cube and it's holes.
  bool             ChangeLengthX(double lenX);
  bool             ChangeLengthY(double lenY);
  bool             ChangeLengthZ(double lenZ);
  bool             ChangeHoleRadius(double rad);
  bool             ChangeHoleDepth(double depth);

private:
  SPtr<MbSolid>    BuildSolid() const;

public:
  AppParametricCube(const AppParametricCube &) = delete;
  AppParametricCube & operator = (const AppParametricCube &) = delete;

private:
  static SPtr<MbSolid> CreateCube(const MbLineSegment & sideX, const MbLineSegment & sideY, double height);
  static SPtr<MbSolid> CreateCylinder(const MbArc & xyPlane, double height);
};

#endif  // PARAM_CUBE_H
