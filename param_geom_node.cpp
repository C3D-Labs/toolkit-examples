//
// Created by redcat1
//

#include "param_geom_node.h"
#include <plane_instance.h>
#include <gce_api.h>

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
//
// ---
bool AppGeomNode::AddToInstance(SPtr<MbPlaneInstance> instance)
{
  if (instance != nullptr)
  {
    return instance->AddPlaneItem(PlaneItem()) != SYS_MAX_T;
  }
  return false;
}

//----------------------------------------------------------------------------------------
//
// ---
bool AppGeomNode::DeleteFromInstance(SPtr<MbPlaneInstance> instance)
{
  const size_t ind = instance->GetIndex(PlaneItem());
  return instance->DeleteItem(ind);
}

//----------------------------------------------------------------------------------------
//
// ---
bool AppGeomNode::Remove(GCE_system system)
{
  const bool res = GCE_RemoveGeom(system, GceItem());
  if (res)
  {
    ResetGeomItem();
  }
  return res;
}

//----------------------------------------------------------------------------------------
//
// ---
AppCPointNode AppGeomNode::GetControlPoint(GCE_system solver, point_type pType) const
{
  const auto pntItem = GCE_PointOf(solver, GceItem(), pType);
  return AppCPointNode(pntItem);
}

//----------------------------------------------------------------------------------------
//
// ---
AppCPointNode::AppCPointNode(geom_item g)
  : AppGeomNode(), mdlrPnt()
  , slvrPnt(g)
{}

//----------------------------------------------------------------------------------------
//
// ---
geom_item AppCPointNode::GceItem() const
{
  return slvrPnt;
}

//----------------------------------------------------------------------------------------
//
// ---
geom_item AppCPointNode::Formulate(GCE_system solver)
{
  return slvrPnt;
}

//----------------------------------------------------------------------------------------
//
// ---
void AppCPointNode::ApplySolution(GCE_system solver)
{
  mdlrPnt = _CPnt(GCE_GetPointXY(solver, slvrPnt));
}

//----------------------------------------------------------------------------------------
//
// ---
AppLineSegNode::AppLineSegNode(MbLineSegment & _lSeg)
  : AppGeomNode()
  , lSeg(&_lSeg)
  , lSegItem(GCE_NULL_G)
{}

//----------------------------------------------------------------------------------------
//
// ---
geom_item AppLineSegNode::GceItem() const
{
  return lSegItem;
}

//----------------------------------------------------------------------------------------
//
// ---
geom_item AppLineSegNode::Formulate(GCE_system solver)
{
  MbCartPoint p1 = lSeg->GetLimitPoint(1);
  MbCartPoint p2 = lSeg->GetLimitPoint(2);
  geom_item endPnts [] = { GCE_AddPoint(solver, _GPnt(p1)), GCE_AddPoint(solver, _GPnt(p2)) };
  lSegItem = GCE_AddLineSeg(solver, endPnts);
  return lSegItem;
}

//----------------------------------------------------------------------------------------
// Apply a state of evaluated geometry from the solver to the driven line segment
// ---
void AppLineSegNode::ApplySolution(GCE_system solver)
{
  GCE_point p1 = GCE_GetPointXY(solver, lSegItem, GCE_FIRST_END );
  GCE_point p2 = GCE_GetPointXY(solver, lSegItem, GCE_SECOND_END );
  lSeg->Init(_CPnt(p1), _CPnt(p2));
}

//----------------------------------------------------------------------------------------
//
// ---
AppCircleNode::AppCircleNode(MbArc & _arc)
  : AppGeomNode()
  , arc(&_arc)
  , circleItem(GCE_NULL_G)
{}

//----------------------------------------------------------------------------------------
//
// ---
geom_item AppCircleNode::GceItem() const
{
  return circleItem;
}

//----------------------------------------------------------------------------------------
//
// ---
geom_item AppCircleNode::Formulate(GCE_system solver)
{
  GCE_circle circPars;
  circPars.centre = _GPnt(arc->GetCentre());
  circPars.radius = arc->GetRadius();
  circleItem = GCE_AddCircle(solver, circPars);
  return circleItem;
}

//----------------------------------------------------------------------------------------
// Apply a state of evaluated geometry from the solver to the driven arc
// ---
void AppCircleNode::ApplySolution(GCE_system solver)
{
  GCE_point center = GCE_GetPointXY(solver, GCE_PointOf(solver, circleItem, GCE_CENTRE) );
  double    radius = GCE_GetCoordValue(solver, circleItem, GCE_RADIUS);
  arc->Init(_CPnt(center), radius);
}
