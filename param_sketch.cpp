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
// ---
AppCPointNode AppParametricSketch::GetControlPoint(AppGeomNodeCRef gNode, point_type pType) const
{
  return gNode.GetControlPoint(solver, pType);
}

//----------------------------------------------------------------------------------------
//
// ---
SPtr<MbItem> AppParametricSketch::SketchItem() const
{
  return sketch;
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
  return false;
}

//----------------------------------------------------------------------------------------
//
// ---
AppConstrNodePtr AppParametricSketch::FixGeom(AppGeomNodeCRef gNode, constraint_type cType)
{
  std::shared_ptr<AppConstraintNode> conNode = nullptr;
  if(GCE_LENGTH == cType)
  {
    conNode = std::make_shared<AppFixLengthNode>(gNode);
  }
  else if (GCE_RADIUS_DIM == cType)
  {
    conNode = std::make_shared<AppFixRadiusNode>(gNode);
  }
  else if (GCE_FIX_GEOM == cType)
  {
    conNode = std::make_shared<AppFixGeomNode>(gNode);
  }
  _Register(conNode);
  return conNode;
}

//----------------------------------------------------------------------------------------
// Distance between two geometric objects
//---
AppConstrNodePtr AppParametricSketch::Distance(AppGeomNodeCRef gNode1, AppGeomNodeCRef gNode2, double dimVal)
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
AppConstrNodePtr AppParametricSketch::ConnectSegments(AppGeomNodeCRef bndCrv1, AppGeomNodeCRef bndCrv2)
{
  auto conNode = std::make_shared<AppConnectSegmentsNode>(bndCrv1, bndCrv2);
  _Register(conNode);
  return conNode;
}

//----------------------------------------------------------------------------------------
//
//---
AppConstrNodePtr AppParametricSketch::Perpendicular(AppGeomNodeCRef line1, AppGeomNodeCRef line2)
{
  auto conNode = std::make_shared<AppPerpendicularNode>(line1, line2);
  _Register(conNode);
  return conNode;
}

//----------------------------------------------------------------------------------------
//
// ---
AppConstrNodePtr AppParametricSketch::Parallel(AppGeomNodeCRef line1, AppGeomNodeCRef line2)
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
GCE_result AppParametricSketch::ChangeDimension(AppConstraintNode & dim, double newDimVal)
{
  return dim.ChangeDimension(solver, newDimVal);
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
  constraint_item conId = GCE_NULL_C;
  if (conNode != nullptr)
  {
    const constraint_item conId = conNode->Formulate(solver);
    if (conId != GCE_NULL_C)
    {
      cNodes.emplace_back(conNode);
    }
  }
  return conId;
}
