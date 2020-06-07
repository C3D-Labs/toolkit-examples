//
// Created by redcat1
//

#ifndef PARAM_CUBE_H
#define PARAM_CUBE_H

#include <memory>
#include <unordered_map>
#include <templ_sptr.h>
#include <gce_types.h>

class MbPlacement3D;
class MbCartPoint;
class MbArc;
class MbSolid;
class AppGeomNode;
class AppConstraintNode;
class AppParametricSketch;

//----------------------------------------------------------------------------------------
//
// ---
class AppParametricCubePlan
{
  using PlanControls = std::unordered_map<std::string, std::shared_ptr<AppConstraintNode>>;
  using GeomNodePtr  = std::shared_ptr<AppGeomNode>;
  using GeomNodeCRef = const AppGeomNode &;

  std::shared_ptr<AppParametricSketch> sketch;
  PlanControls                         controls;

public:
  AppParametricCubePlan(const MbPlacement3D & place, double length, double width,
                        double holeRadius, double holeIndent);

public:
  bool        ChangeLengthX(double lenX);
  bool        ChangeLengthY(double lenY);
  bool        ChangeHoleRadius(double rad);

  GCE_result  Calculate();

private:
  GeomNodePtr _AddRectangleSide(const MbCartPoint &, const MbCartPoint &);
  GeomNodePtr _AddHoleInCorner(MbArc & circle, GeomNodeCRef side1, GeomNodeCRef side2, double indent);

public:
  AppParametricCubePlan(const AppParametricCubePlan &) = delete;
  AppParametricCubePlan & operator = (const AppParametricCubePlan &) = delete;
};

//----------------------------------------------------------------------------------------
//
// ---
class AppParametricCube
{
  SPtr<MbSolid>                          cube;
  std::shared_ptr<AppParametricCubePlan> paramPlan;

public:
  AppParametricCube(const MbPlacement3D & place, double length, double width, double height);

public:
  // void AddHole();
  // void AddPocket();
  void ChangeLengthX(double lenX);
  void ChangeLengthY(double lenY);
  void ChangeLengthZ(double lenZ);
};

#endif  // PARAM_CUBE_H
