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
// Convert to MbCartPoint type
//---
template<class XYType>
inline MbCartPoint _CPnt ( const XYType & crd )
{
  return MbCartPoint(crd.x,crd.y);
}

//----------------------------------------------------------------------------------------
// Convert to GCE_point type
//---
template<class XYType>
inline GCE_point _GPnt ( const XYType & crd )
{
  GCE_point pnt;
  pnt.x = crd.x, pnt.y = crd.y;
  return pnt;
}

//----------------------------------------------------------------------------------------
// Parametric node
/*
  This class represents a geometric and dimensional entities which are under control of the solver.
*/
//---
class AppParametricNode
{
public:
  virtual void  Formulate( GCE_system ) = 0;      // This function formulates node's individual behavior in the solver
  virtual void  ApplySolution( GCE_system ) = 0;  // This function take a computed coordinates from the solver

protected:
  virtual ~AppParametricNode() = default;
};

//----------------------------------------------------------------------------------------
// Constraint node
//---
class AppConstraintNode: public AppParametricNode {};

//----------------------------------------------------------------------------------------
// This node represents some geometric object in constraint system
//---
class AppGeomNode: public AppParametricNode
{
protected:
  AppGeomNode() : AppParametricNode() {}
  ~AppGeomNode() override = default;

public:
  // Descriptor of geometrical object registered in the solver.
  virtual geom_item GceItem() const = 0;
};

//----------------------------------------------------------------------------------------
/*
  This subclass of GeomNode represents a control point of some geometric object.
  For example, an instance of 'ControlPoint' can represent center of circle,
  end of arc, end of lineseg and so on.
*/
//---
class AppPointNode: public AppGeomNode
{
  MbCartPoint mdlrPnt;
  geom_item   slvrPnt; // Descriptor of a control point

public:
  explicit AppPointNode(geom_item g)
      : AppGeomNode(), mdlrPnt(), slvrPnt(g)
  {}

public:
  geom_item GceItem() const override { return slvrPnt; }

  void      Formulate(GCE_system solver) override
  {
    slvrPnt = GCE_AddPoint(solver, _GPnt(mdlrPnt));
  }

  // Apply a state of evaluated geometry from the solver to the model object
  void      ApplySolution(GCE_system solver) override
  {
    mdlrPnt = _CPnt(GCE_GetPointXY(solver, slvrPnt));
  }

  AppPointNode(const AppPointNode &) = delete;
  AppPointNode & operator = (const AppPointNode &) = delete;
};

//----------------------------------------------------------------------------------------
// Parametric node controlling a line segment
/*
  This class takes control of object of type 'MbLineSegment'. 'LineSegNode' able to apply
  solver result to a line segment. An object, which under control, can be replaced by any
  other type. This may be not only C3D-object 'MbLineSegment' but any native geometric
  type (presenting line segment) of client application.
*/
//---
class AppLineSegNode: public AppGeomNode
{
  SPtr<MbLineSegment> lSeg;       // Controlled object, line segment
  geom_item           lSegItem;   // Descriptor of the line segment

public:
  explicit AppLineSegNode(MbLineSegment & _lSeg)
      : AppGeomNode(), lSeg(&_lSeg), lSegItem(GCE_NULL_G)
  {}

  ~AppLineSegNode() override = default;

public:
  geom_item GceItem() const override
  {
    return lSegItem;
  }

  void      Formulate(GCE_system solver) override
  {
    MbCartPoint p1 = lSeg->GetLimitPoint(1);
    MbCartPoint p2 = lSeg->GetLimitPoint(2);
    geom_item endPnts [] = { GCE_AddPoint(solver, _GPnt(p1)), GCE_AddPoint(solver, _GPnt(p2)) };
    lSegItem = GCE_AddLineSeg(solver, endPnts);
  }

  // Apply a state of evaluated geometry from the solver to the driven line segment
  void      ApplySolution(GCE_system solver) override
  {
    GCE_point p1 = GCE_GetPointXY(solver, lSegItem, GCE_FIRST_END );
    GCE_point p2 = GCE_GetPointXY(solver, lSegItem, GCE_SECOND_END );
    lSeg->Init(_CPnt(p1), _CPnt(p2));
  }

  AppLineSegNode(const AppLineSegNode & ) = delete;
  AppLineSegNode & operator = (const AppLineSegNode & ) = delete;
};

//----------------------------------------------------------------------------------------
// The node controlling an arc
/*
  This class takes control of object of type 'MbArc'. 'ArcNode' able to apply solver result
  to a circular arc. An object, which under control, can be replaced by any other type.
  This may be not only 'MbArc' but any native geometric type (presenting circular arc) of
  client application.
*/
//---
class AppCircleNode: public AppGeomNode
{
  SPtr<MbArc> arc;        // Controlled object, circle or arc
  geom_item   circItem;   // Descriptor of the circle

public:
  explicit AppCircleNode(MbArc & _arc )
    : AppGeomNode(), arc(&_arc ), circItem(GCE_NULL_G )
  {}

  ~AppCircleNode() override = default;

public:
  geom_item GceItem() const override
  {
    return circItem;
  }

  void      Formulate(GCE_system solver) override
  {
    GCE_circle circPars;
    circPars.centre = _GPnt(arc->GetCentre());
    circPars.radius = arc->GetRadius();
    circItem = GCE_AddCircle(solver, circPars);
  }

  // Apply a state of evaluated geometry from the solver to the driven arc
  void      ApplySolution(GCE_system solver) override
  {
    GCE_point center = GCE_GetPointXY(solver, GCE_PointOf(solver, circItem, GCE_CENTRE) );
    double    radius = GCE_GetCoordValue(solver, circItem, GCE_RADIUS);
    arc->Init(_CPnt(center), radius);
  }

  AppCircleNode(const AppCircleNode & ) = delete;
  AppCircleNode & operator = (const AppCircleNode & ) = delete;
};

class C3DArcNode : public AppCircleNode {};

//----------------------------------------------------------------------------------------
// Constraint system of the sketch
//---
class AppParametricSketch
{
  using GeomNodePtr = std::shared_ptr<AppGeomNode>;
  using GeomsVector = std::vector<GeomNodePtr>;

  SPtr<MbPlaneInstance> sketch;
  GCE_system            system;
  GeomsVector           gNodes;  // Set of geometric nodes which are under control of the solver

public:
  explicit AppParametricSketch(const MbPlacement3D & place)
      : sketch(new MbPlaneInstance(place)), system(GCE_CreateSystem()), gNodes()
  {
    GCE_SetJournal( system, "gce_sample.jrn" );
  }

  ~AppParametricSketch()
  {
    GCE_RemoveSystem( system );
  }

public:
  MbItem &        SketchItem() const { return *sketch; }
  bool            IsEmpty() const { return gNodes.empty(); }

  GeomNodePtr     AddCircle(MbArc &);
  GeomNodePtr     AddLineSegment(MbLineSegment &);
  void            Remove(std::shared_ptr<AppParametricNode>) = delete; // Not implemented

public: /* Functions formulating constraints */
  constraint_item Fix(GeomNodePtr);
  constraint_item Length(GeomNodePtr);  // Distance between the ends of line segment
  constraint_item Radius(GeomNodePtr circle);  // Radial dimension for arc or circle
  constraint_item UnaryConstraint(constraint_type, GeomNodePtr);  // Horizontal / vertical
  constraint_item ConnectSegments(GeomNodePtr, GeomNodePtr);
  constraint_item Perpendicular(GeomNodePtr, GeomNodePtr);
  constraint_item Distance(GeomNodePtr, GeomNodePtr, double dimVal );  // Distance dimension for a pair of geometric objects

public:
  GCE_result      Evaluate(); // Solve the sketch
  GCE_result      ChangeDimension( constraint_item, double dVal );  // Set a new value of dimension

private:
  geom_item  _GceItem(GeomNodePtr);
  geom_item  _Register(GeomNodePtr); // Registers a node in C3D Solver with its formulation
  void       _Unregister(GeomNodePtr);   // Removes a node from C3D Solver and its constraint system (not implemented)

public:
  AppParametricSketch(const AppParametricSketch & ) = delete;
  AppParametricSketch & operator = (const AppParametricSketch & ) = delete;
};

//----------------------------------------------------------------------------------------
//
//---
std::shared_ptr<AppGeomNode> AppParametricSketch::AddCircle(MbArc & circle)
{
  sketch->AddPlaneItem(&circle);
  auto circleNode = std::make_shared<AppCircleNode>(circle);
  _Register(circleNode);
  return circleNode;
}

//----------------------------------------------------------------------------------------
//
//---
std::shared_ptr<AppGeomNode> AppParametricSketch::AddLineSegment(MbLineSegment & lSeg)
{
  sketch->AddPlaneItem(&lSeg);
  auto lSegNode = std::make_shared<AppLineSegNode>(lSeg);
  _Register(lSegNode);
  return lSegNode;
}

//----------------------------------------------------------------------------------------
// Fixing constraint
//---
constraint_item AppParametricSketch::Fix(AppParametricSketch::GeomNodePtr gNode)
{
  return GCE_FixGeom(system, _GceItem(gNode));
}

//----------------------------------------------------------------------------------------
// Sets a radial dimension for arc or circle
//---
constraint_item AppParametricSketch::Radius(AppParametricSketch::GeomNodePtr circle)
{
  return GCE_FixRadius(system, _GceItem(circle));
}

//----------------------------------------------------------------------------------------
// Connects two bounded curves at the its ends
/*
  The function connects end of the first curve to begin of the second curve.
*/
//---
constraint_item AppParametricSketch::ConnectSegments(AppParametricSketch::GeomNodePtr bndCrv1,
                                                     AppParametricSketch::GeomNodePtr bndCrv2)
{
  geom_item ends[2] = { GCE_PointOf(system, _GceItem(bndCrv1), GCE_SECOND_END),
                        GCE_PointOf(system, _GceItem(bndCrv2), GCE_FIRST_END) };  // end points
  return GCE_AddCoincidence(system, ends);
}

//----------------------------------------------------------------------------------------
// Fixes distance between the ends of line segment
//---
constraint_item AppParametricSketch::Length(AppParametricSketch::GeomNodePtr lSeg)
{
  return GCE_FixLength( system, _GceItem(lSeg) );
}

//----------------------------------------------------------------------------------------
//
//---
constraint_item AppParametricSketch::Perpendicular(AppParametricSketch::GeomNodePtr line1,
                                                   AppParametricSketch::GeomNodePtr line2)
{
  geom_item lines[2] = { _GceItem(line1), _GceItem(line2) };
  return GCE_AddPerpendicular( system, lines );
}

//----------------------------------------------------------------------------------------
// Horizontal / vertical
//---
constraint_item AppParametricSketch::UnaryConstraint(constraint_type cType,
                                                     AppParametricSketch::GeomNodePtr gNode)
{
  return GCE_AddUnaryConstraint( system, cType, _GceItem(gNode) );
}

//----------------------------------------------------------------------------------------
// Distance between two geometric objects
//---
constraint_item AppParametricSketch::Distance(AppParametricSketch::GeomNodePtr gNode1,
                                              AppParametricSketch::GeomNodePtr gNode2,
                                              double dimVal)
{
  GCE_ldim_pars pars;
  pars.dPars.dimValue = dimVal;
  geom_item g[2] = { _GceItem(gNode1), _GceItem(gNode2) };
  return GCE_AddDistance( system, g, pars );
}

//----------------------------------------------------------------------------------------
// Solve the sketch
//---
GCE_result AppParametricSketch::Evaluate()
{
  GCE_result resCode = GCE_Evaluate( system );
  if ( resCode == GCE_RESULT_Ok )
  {
    // Apply evaluation results to the sketch geometry
    for (auto && gNode : gNodes)
    {
      gNode->ApplySolution(system);
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
GCE_result AppParametricSketch::ChangeDimension(constraint_item dim, double dVal)
{
  return GCE_ChangeDrivingDimension(system, dim, dVal);
}

//----------------------------------------------------------------------------------------
//
//---
geom_item AppParametricSketch::_GceItem(AppParametricSketch::GeomNodePtr gNode)
{
  return (nullptr != gNode) ? gNode->GceItem() : GCE_NULL_G;
}

//----------------------------------------------------------------------------------------
//
//---
geom_item AppParametricSketch::_Register(AppParametricSketch::GeomNodePtr gNode)
{
  gNode->Formulate(system);  // Formulate parametric behavior of the object
  if (gNode->GceItem() != GCE_NULL)
  {
    gNodes.push_back(gNode);
  }
  return gNode->GceItem();
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
  constraint_item  aDim, bDim, cDim, rDim;
  if ( sketch.IsEmpty() )
  {
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
    sketch.UnaryConstraint(GCE_VERTICAL, aSeg );
    sketch.UnaryConstraint(GCE_HORIZONTAL, bSeg );
    sketch.Perpendicular(bSeg, cSeg );
    sketch.Evaluate();

    /*
      Add driving dimensions A, B, C, R
    */
    aDim = sketch.Distance(bSeg, arcNode, aVal );
    bDim = sketch.Length(bSeg );
    cDim = sketch.Length(cSeg );
    rDim = sketch.Radius(arcNode );

    GCE_result resCode = sketch.Evaluate();  // Satisfy all of constraints of the sketch
    TestVariables::viewManager->AddItem(sketch.SketchItem(), Style());
  }
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
  sketch->ChangeDimension(aDim, aVal );
  sketch->ChangeDimension(bDim, bVal );
  sketch->ChangeDimension(cDim, cVal );
  GCE_result resCode = sketch->Evaluate();
  TestVariables::viewManager->RedrawObject( &sketch.SketchItem());
}
