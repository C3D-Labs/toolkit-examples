//
// Created by redcat1
//

#ifndef PARAM_SKETCH_H
#define PARAM_SKETCH_H

#include <templ_sptr.h>
#include <gce_types.h>

class AppGeomNode;
class AppCPointNode;
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
  using AppGeomNodeCRef   = const AppGeomNode &;
  using AppConstrNodeCRef = const AppConstraintNode &;
  using AppGeomNodePtr    = std::shared_ptr<AppGeomNode>;
  using AppConstrNodePtr  = std::shared_ptr<AppConstraintNode>;
  using AppGeomsVector    = std::vector<AppGeomNodePtr>;
  using AppConsVector     = std::vector<AppConstrNodePtr>;

private:
  SPtr<MbPlaneInstance> sketch;
  GCE_system            solver;
  AppGeomsVector        gNodes;  // Set of geometric nodes which are under control of the solver
  AppConsVector         cNodes;  // Set of constraint nodes which are under control of the solver

public:
  explicit AppParametricSketch(const MbPlacement3D & place);
  ~AppParametricSketch();

public:
  SPtr<MbItem>     SketchItem() const;

  AppGeomNodePtr   AddLineSegment(MbLineSegment &);
  AppGeomNodePtr   AddCircle(MbArc &);
  AppCPointNode    GetControlPoint(AppGeomNodeCRef, point_type) const;
  bool             Remove(AppGeomNodePtr);

public: /* Functions formulating constraints */
  /* Allow to fix a radius (GCE_RADIUS_DIM) or a length (GCE_LENTH) of geometic
   * object or to fix whole geometric object (GCE_FIX_GEOM).*/
  AppConstrNodePtr FixGeom(AppGeomNodeCRef, constraint_type);
  AppConstrNodePtr Distance(AppGeomNodeCRef, AppGeomNodeCRef, double dimVal);  // Distance dimension for a pair of geometric objects
  AppConstrNodePtr ConnectSegments(AppGeomNodeCRef, AppGeomNodeCRef);
  AppConstrNodePtr Perpendicular(AppGeomNodeCRef, AppGeomNodeCRef);
  AppConstrNodePtr Parallel(AppGeomNodeCRef, AppGeomNodeCRef);
  bool             Remove(AppConstrNodePtr) = delete;

public:
  GCE_result       Evaluate(); // Solve the sketch
  GCE_result       ChangeDimension(AppConstraintNode &, double dVal);  // Set a new value of dimension

private:
  geom_item        _Register(AppGeomNodePtr); // Registers a node in C3D Solver with its formulation
  constraint_item  _Register(AppConstrNodePtr);

public:
  AppParametricSketch(const AppParametricSketch & ) = delete;
  AppParametricSketch & operator = (const AppParametricSketch & ) = delete;
};

#endif  // UNITTESTS_PARAM_SKETCH_H
