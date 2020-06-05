//
// Created by redcat1
//

#include "param_cube_sample.h"
#include <param_sketch.h>


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
