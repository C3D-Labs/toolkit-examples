//
// Created by redcat1
//

#include "param_sketch.h"
#include <param_geom_node.h>
#include <param_constraint_node.h>
#include <plane_instance.h>
#include <gce_api.h>

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
