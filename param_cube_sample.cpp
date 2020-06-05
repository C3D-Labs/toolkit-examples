//
// Created by redcat1 on 04.06.2020.
//

#include "param_cube_sample.h"

//////////////////////////////////////////////////////////////////////////////////////////
//  The file contains a source code demonstrating a sample how to implement a wrapper
// for 2D solver. Such wrapper aimed to subordinate a 2D sketch to geometric constraints
// i.e. to make the sketch driven by constraints and dimensions.
//  CAD system that uses the solver have to have such wrapper as a bridge connecting
// CAD-specific geometry to Solver data through its API (header gce_api.h).
//////////////////////////////////////////////////////////////////////////////////////////

#include <test_samples.h>
#include <test_variables.h>
#include <test_manager.h>
#include <test_service.h>
//
#include <param_geom_node.h>
#include <param_constraint_node.h>
//
#include <cur_arc.h>
#include <cur_line_segment.h>
#include <plane_instance.h>
//
#include <gce_api.h>
#include <mt_ref_item.h>
//
#include <math_namespace.h>
#include <last.h>

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

using AppGeomNodePtr = AppParametricSketch::AppGeomNodePtr;
using AppConstrNodePtr = AppParametricSketch::AppConstrNodePtr;

//----------------------------------------------------------------------------------------
//
// ---
AppParametricSketch::AppParametricSketch(const MbPlacement3D & place)
  : sketch(new MbPlaneInstance(place))
  , solver(GCE_CreateSystem())
  , gNodes()
  , cNodes()
{
  GCE_SetJournal(solver, "gce_sample.jrn");
}

//----------------------------------------------------------------------------------------
//
// ---
AppParametricSketch::~AppParametricSketch()
{
  GCE_RemoveSystem(solver);
}

//----------------------------------------------------------------------------------------
//
//---
AppGeomNodePtr AppParametricSketch::AddCircle(MbArc & circle)
{
  auto circleNode = std::make_shared<AppCircleNode>(circle);
  _Register(circleNode);
  return circleNode;
}

//----------------------------------------------------------------------------------------
//
//---
AppGeomNodePtr AppParametricSketch::AddLineSegment(MbLineSegment & lSeg)
{
  auto lSegNode = std::make_shared<AppLineSegNode>(lSeg);
  _Register(lSegNode);
  return lSegNode;
}

//----------------------------------------------------------------------------------------
//
// ---
bool AppParametricSketch::Remove(AppGeomNodePtr gNode)
{
  if (gNode != nullptr)
  {
    auto eraseIt = std::find(std::cbegin(gNodes), std::cend(gNodes), gNode);
    if (eraseIt != std::cend(gNodes))
    {
      if (gNode->Remove(solver))
      {
        gNode->DeleteFromInstance(sketch);
        gNodes.erase(eraseIt);
        return true;
      }
    }
  }
  return false;
}

//----------------------------------------------------------------------------------------
// Fixes distance between the ends of line segment
//---
AppConstrNodePtr AppParametricSketch::FixLength(std::string name, AppGeomNodePtr lSeg)
{
  auto conNode = std::make_shared<AppFixLengthNode>(lSeg);
  _Register(conNode);
  return conNode;
}

//----------------------------------------------------------------------------------------
// Sets a radial dimension for arc or circle
//---
AppConstrNodePtr AppParametricSketch::FixRadius(std::string name, AppGeomNodePtr circle)
{
  auto conNode = std::make_shared<AppFixRadiusNode>(circle);
  _Register(conNode);
  return conNode;
}

//----------------------------------------------------------------------------------------
// Distance between two geometric objects
//---
AppConstrNodePtr AppParametricSketch::Distance(AppGeomNodePtr gNode1, AppGeomNodePtr gNode2, double dimVal)
{
  auto conNode = std::make_shared<AppDistanceNode>(gNode1, gNode2, dimVal);
  _Register(conNode);
  return conNode;
}

//----------------------------------------------------------------------------------------
// Connects two bounded curves at the its ends
/*
  The function connects end of the first curve to begin of the second curve.
*/
//---
AppConstrNodePtr AppParametricSketch::ConnectSegments(AppGeomNodePtr bndCrv1, AppGeomNodePtr bndCrv2)
{
  auto conNode = std::make_shared<AppConnectSegmentsNode>(bndCrv1, bndCrv2);
  _Register(conNode);
  return conNode;
}

//----------------------------------------------------------------------------------------
//
//---
AppConstrNodePtr AppParametricSketch::Perpendicular(AppGeomNodePtr line1, AppGeomNodePtr line2)
{
  auto conNode = std::make_shared<AppPerpendicularNode>(line1, line2);
  _Register(conNode);
  return conNode;
}

//----------------------------------------------------------------------------------------
//
// ---
AppConstrNodePtr AppParametricSketch::Parallel(AppGeomNodePtr line1, AppGeomNodePtr line2)
{
  auto conNode = std::make_shared<AppParallelNode>(line1, line2);
  _Register(conNode);
  return conNode;
}

//----------------------------------------------------------------------------------------
// Solve the sketch
//---
GCE_result AppParametricSketch::Evaluate()
{
  GCE_result resCode = GCE_Evaluate( solver );
  if ( resCode == GCE_RESULT_Ok )
  {
    // Apply evaluation results to the sketch geometry
    for (auto && gNode : gNodes)
    {
      gNode->ApplySolution(solver);
    }
  }
  return resCode;
}

//----------------------------------------------------------------------------------------
// Set a new value of dimension
/*
  NOTE: This function only sets the parameter without solving the constraint system.
        Call the function Evaluate() to apply the changes.
*/
//---
GCE_result AppParametricSketch::ChangeDimension(AppConstrNodePtr dim, double newDimVal)
{
  if (dim != nullptr)
  {
    return dim->ChangeDimension(solver, newDimVal);
  }
  return GCE_RESULT_NullSystem;
}

//----------------------------------------------------------------------------------------
//
//---
geom_item AppParametricSketch::_Register(AppGeomNodePtr gNode)
{
  gNode->AddToInstance(sketch);
  const geom_item geomId = gNode->Formulate(solver);  // Formulate parametric behavior of the object
  if (geomId != GCE_NULL_G)
  {
    gNodes.push_back(gNode);
  }
  return geomId;
}

//----------------------------------------------------------------------------------------
//
// ---
constraint_item AppParametricSketch::_Register(AppConstrNodePtr conNode)
{
  const constraint_item conId = conNode->Formulate(solver);
  if (conId != GCE_NULL_C)
  {
    cNodes.emplace_back(conNode);
  }
  return conId;
}

//----------------------------------------------------------------------------------------
// The sample of parametric sketch
/*
  This sample demonstrates how to change parametric sketch using C3D Solver.
  The sketch is driven by three parameters:
    A - hight of the sketch (tangential linear dimension );
    B - width of the sketch;
    C - another parameter, hight of the right part of the sketch.

  The first call of this function creates a sketch represented by a class-instance of
 'MbPlaneInstance', and other calls allow to change the parameters observing
  behavior of the parametric sketch.
*/
// ---
void ConstructParametricSketch(AppParametricSketch & sketch)
{
  /*
    The sample demonstrating how to change parametric sketch using C3D Solver
  */
  // The values of dimensions of the sketch, A, B, C;
    const MbCartPoint center( -150.0, 100.0 );  // A center of the circles
  SPtr<MbArc> circ( new MbArc(center,20.0) ); // The internal circle;
  /*
    Create a geometry of the sketch
  */
  const MbCartPoint origin; // the origin of the sketch coordinate system
  MbCartPoint arcBegin(-133.0, 147.0), arcMid(-176.0, 142.0), arcEnd(-200.0, 100.0);
  SPtr<MbArc> arc( new MbArc(arcBegin,arcMid,arcEnd) );
  MbCartPoint vertexAB(-200, 0), vertexC(0, 100);

  SPtr<MbLineSegment> segA( new MbLineSegment(arcEnd,vertexAB) ); // Use smart pointer to avoid memory leaks
  SPtr<MbLineSegment> segB( new MbLineSegment(vertexAB,origin) );
  SPtr<MbLineSegment> segC( new MbLineSegment(origin,vertexC) );
  SPtr<MbLineSegment> segD( new MbLineSegment(vertexC,arcBegin) );
  /*
    Add the geoms to the constraint system
  */
  auto circNode = sketch.AddCircle(*circ);
  auto arcNode  = sketch.AddCircle(*arc);
  auto aSeg     = sketch.AddLineSegment(*segA);
  auto bSeg     = sketch.AddLineSegment(*segB);
  auto cSeg     = sketch.AddLineSegment(*segC);
  auto dSeg     = sketch.AddLineSegment(*segD);

  /*
    Add geometric constraints to the sketch
  */
  sketch.ConnectSegments(arcNode, aSeg );
  sketch.ConnectSegments(aSeg, bSeg );
  sketch.ConnectSegments(bSeg, cSeg );
  sketch.ConnectSegments(cSeg, dSeg );
  sketch.ConnectSegments(dSeg, arcNode );
  sketch.Perpendicular(bSeg, cSeg );
  sketch.Evaluate();

  /*
    Add driving dimensions A, B, C, R
  */
  sketch.Distance(bSeg, arcNode, 100.);
  sketch.FixLength(std::string("fix1"), bSeg);
  sketch.FixLength(std::string("fix2"), cSeg);
  sketch.FixRadius(std::string("fixR1"), arcNode);

  GCE_result resCode = sketch.Evaluate();  // Satisfy all of constraints of the sketch
  TestVariables::viewManager->AddItem(*sketch.SketchItem(), Style());
}

//----------------------------------------------------------------------------------------
//
// ---
void ShowCube()
{
  const MbPlacement3D xyPlane;  // a local coordinate system of the sketch
  auto sketch = std::make_unique<AppParametricSketch>(xyPlane);
  ConstructParametricSketch(*sketch);

  /*
      Recalculate the sketch with new parameters A, B, C
    */
  double aVal = 150.0, bVal = 200.0, cVal = 100.0;
  /*sketch->ChangeDimension(aDim, aVal );
  sketch->ChangeDimension(bDim, bVal );
  sketch->ChangeDimension(cDim, cVal );*/
  GCE_result resCode = sketch->Evaluate();
  TestVariables::viewManager->RedrawObject(sketch->SketchItem());
}
