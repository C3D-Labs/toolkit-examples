//
// Created by redcat1
//

#ifndef PARAM_SKETCH_H
#define PARAM_SKETCH_H

#include <templ_sptr.h>
#include <gce_types.h>

class AppGeomNode;
class AppConstraintNode;
class MbPlaneInstance;
class MbItem;
class MbPlacement3D;
class MbLineSegment;
class MbArc;

//----------------------------------------------------------------------------------------
// Constraint system of the sketch
//---
class AppParametricSketch
{
public:
  using AppGeomNodePtr   = std::shared_ptr<AppGeomNode>;
  using AppConstrNodePtr = std::shared_ptr<AppConstraintNode>;
  using AppGeomsVector   = std::vector<AppGeomNodePtr>;
  using AppConsVector    = std::vector<AppConstrNodePtr>;

private:
  SPtr<MbPlaneInstance> sketch;
  GCE_system            solver;
  AppGeomsVector        gNodes;  // Set of geometric nodes which are under control of the solver
  AppConsVector         cNodes;  // Set of constraint nodes which are under control of the solver

public:
  explicit AppParametricSketch(const MbPlacement3D & place);
  ~AppParametricSketch();

public:
  SPtr<MbItem>     SketchItem() const { return sketch; }

  AppGeomNodePtr   AddLineSegment(MbLineSegment &);
  AppGeomNodePtr   AddCircle(MbArc &);
  bool             Remove(AppGeomNodePtr);

public: /* Functions formulating constraints */
  AppConstrNodePtr FixLength(std::string name, AppGeomNodePtr);  // Distance between the ends of line segment
  AppConstrNodePtr FixRadius(std::string name, AppGeomNodePtr circle);  // Radial dimension for arc or circle
  AppConstrNodePtr Distance(AppGeomNodePtr, AppGeomNodePtr, double dimVal );  // Distance dimension for a pair of geometric objects
  AppConstrNodePtr ConnectSegments(AppGeomNodePtr, AppGeomNodePtr);
  AppConstrNodePtr Perpendicular(AppGeomNodePtr, AppGeomNodePtr);
  AppConstrNodePtr Parallel(AppGeomNodePtr, AppGeomNodePtr);
  bool             Remove(AppConstrNodePtr) = delete;

public:
  GCE_result       Evaluate(); // Solve the sketch
  GCE_result       ChangeDimension(AppConstrNodePtr, double dVal);  // Set a new value of dimension

private:
  geom_item        _Register(AppGeomNodePtr); // Registers a node in C3D Solver with its formulation
  constraint_item  _Register(AppConstrNodePtr);

public:
  AppParametricSketch(const AppParametricSketch & ) = delete;
  AppParametricSketch & operator = (const AppParametricSketch & ) = delete;
};

#endif  // UNITTESTS_PARAM_SKETCH_H
