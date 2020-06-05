//
// Created by redcat1 on 04.06.2020.
//

#ifndef PARAM_GEOM_NODE_H
#define PARAM_GEOM_NODE_H

#include <gce_types.h>
#include <mb_cart_point.h>
#include <cur_line_segment.h>
#include <cur_arc.h>

class MbPlaneInstance;

//----------------------------------------------------------------------------------------
// This node represents some geometric object in constraint system
//---
class AppGeomNode
{
protected:
  AppGeomNode() = default;
  virtual ~AppGeomNode() = default;

public:
          bool      AddToInstance(SPtr<MbPlaneInstance>);
          bool      DeleteFromInstance(SPtr<MbPlaneInstance>);
  virtual geom_item Formulate(GCE_system) = 0;      // This function formulates node's individual behavior in the solver
  virtual void      ApplySolution(GCE_system) = 0;  // This function take a computed coordinates from the solver
          bool      Remove(GCE_system);
  // Descriptor of geometrical object registered in the solver.
  virtual geom_item GceItem() const = 0;

protected:
  // Geometric representation of geometrical object registered in the solver.
  virtual SPtr<MbPlaneItem> PlaneItem() = 0;
  virtual void              ResetGeomItem() = 0;
};

//----------------------------------------------------------------------------------------
/*
  This subclass of GeomNode represents a control point of some geometric object.
  For example, an instance of 'ControlPoint' can represent center of circle,
  end of arc, end of lineseg and so on.
*/
//---
class AppPointNode final : public AppGeomNode
{
  MbCartPoint mdlrPnt;
  geom_item   slvrPnt; // Descriptor of a control point

public:
  explicit AppPointNode(geom_item g);
  ~AppPointNode() override = default;

public:
  geom_item GceItem() const override;
  geom_item Formulate(GCE_system solver) override;
  // Apply a state of evaluated geometry from the solver to the model object
  void      ApplySolution(GCE_system solver) override;

  AppPointNode(const AppPointNode &) = delete;
  AppPointNode & operator = (const AppPointNode &) = delete;

protected:
  SPtr<MbPlaneItem> PlaneItem() override { return SPtr<MbPlaneItem>(nullptr); }
  void ResetGeomItem() override { slvrPnt = GCE_NULL_G; }
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
class AppLineSegNode final : public AppGeomNode
{
  SPtr<MbLineSegment> lSeg;       // Controlled object, line segment
  geom_item           lSegItem;   // Descriptor of the line segment

public:
  explicit AppLineSegNode(MbLineSegment & _lSeg);
  ~AppLineSegNode() override = default;

public:
  geom_item GceItem() const override;
  geom_item Formulate(GCE_system solver) override;
  // Apply a state of evaluated geometry from the solver to the driven line segment
  void      ApplySolution(GCE_system solver) override;

  AppLineSegNode(const AppLineSegNode & ) = delete;
  AppLineSegNode & operator = (const AppLineSegNode & ) = delete;

protected:
  SPtr<MbPlaneItem> PlaneItem() override { return lSeg; }
  void ResetGeomItem() override { lSegItem = GCE_NULL_G; }
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
class AppCircleNode : public AppGeomNode
{
  SPtr<MbArc> arc;        // Controlled object, circle or arc
  geom_item   circleItem;   // Descriptor of the circle

public:
  explicit AppCircleNode(MbArc & _arc);
  ~AppCircleNode() override = default;

public:
  geom_item GceItem() const override;
  geom_item Formulate(GCE_system solver) override;
  // Apply a state of evaluated geometry from the solver to the driven arc
  void      ApplySolution(GCE_system solver) override;

  AppCircleNode(const AppCircleNode & ) = delete;
  AppCircleNode & operator = (const AppCircleNode & ) = delete;

protected:
  SPtr<MbPlaneItem> PlaneItem() override { return arc; }
  void ResetGeomItem() override { circleItem = GCE_NULL_G; }
};

#endif  // PARAM_GEOM_NODE_H
