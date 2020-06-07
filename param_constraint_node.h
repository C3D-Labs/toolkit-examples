//
// Created by redcat1
//

#ifndef PARAM_CONSTRAINT_NODE_H
#define PARAM_CONSTRAINT_NODE_H

#include <gce_types.h>

class AppGeomNode;

//----------------------------------------------------------------------------------------
// Constraint node
//---
class AppConstraintNode
{
protected:
  using AppGeomNodeCRef = const AppGeomNode &;

protected:
  constraint_item conItem;

protected:
  AppConstraintNode();
  virtual ~AppConstraintNode() = default;

public:
  virtual constraint_item Formulate(GCE_system) = 0;
          bool            Remove(GCE_system);
  virtual GCE_result      ChangeDimension(GCE_system, double) { return GCE_RESULT_NullSystem; }
          constraint_item ConItem() const { return conItem; }

public:
  AppConstraintNode(const AppConstraintNode &) = delete;
  AppConstraintNode & operator = (const AppConstraintNode &) = delete;
};

//----------------------------------------------------------------------------------------
// Fix geom length constraint node.
//---
class AppFixLengthNode final : public AppConstraintNode
{
  geom_item geomItem;

public:
  explicit AppFixLengthNode(AppGeomNodeCRef);
  ~AppFixLengthNode() override = default;

public:
  constraint_item Formulate(GCE_system) override;

public:
  AppFixLengthNode(const AppFixLengthNode &) = delete;
  AppFixLengthNode & operator = (const AppFixLengthNode &) = delete;
};

//----------------------------------------------------------------------------------------
// Fix circle radius constraint node.
//---
class AppFixRadiusNode final : public AppConstraintNode
{
  geom_item circleItem;

public:
  explicit AppFixRadiusNode(AppGeomNodeCRef);
  ~AppFixRadiusNode() override = default;

public:
  constraint_item Formulate(GCE_system) override;

public:
  AppFixRadiusNode(const AppFixRadiusNode &) = delete;
  AppFixRadiusNode & operator = (const AppFixRadiusNode &) = delete;
};

//----------------------------------------------------------------------------------------
// Distance between geometric objects.
//---
class AppDistanceNode final : public AppConstraintNode
{
  geom_item     gItem1;
  geom_item     gItem2;
  GCE_ldim_pars dimPars;

public:
  AppDistanceNode(AppGeomNodeCRef, AppGeomNodeCRef, double);
  ~AppDistanceNode() override = default;

public:
  constraint_item Formulate(GCE_system) override;
  GCE_result      ChangeDimension(GCE_system, double) override;

public:
  AppDistanceNode(const AppDistanceNode &) = delete;
  AppDistanceNode & operator = (const AppDistanceNode &) = delete;
};

//----------------------------------------------------------------------------------------
// Connect second end of first curve with first end of second curve.
//---
class AppConnectSegmentsNode final : public AppConstraintNode
{
  geom_item     crvItem1;
  geom_item     crvItem2;

public:
  AppConnectSegmentsNode(AppGeomNodeCRef, AppGeomNodeCRef);
  ~AppConnectSegmentsNode() override = default;

public:
  constraint_item Formulate(GCE_system) override;

public:
  AppConnectSegmentsNode(const AppConnectSegmentsNode &) = delete;
  AppConnectSegmentsNode & operator = (const AppConnectSegmentsNode &) = delete;
};

//----------------------------------------------------------------------------------------
// Perpendicularity of two linear objects.
//---
class AppPerpendicularNode final : public AppConstraintNode
{
  geom_item lineItem1;
  geom_item lineItem2;

public:
  AppPerpendicularNode(AppGeomNodeCRef, AppGeomNodeCRef);
  ~AppPerpendicularNode() override = default;

public:
  constraint_item Formulate(GCE_system) override;

public:
  AppPerpendicularNode(const AppPerpendicularNode &) = delete;
  AppPerpendicularNode & operator = (const AppPerpendicularNode &) = delete;
};

//----------------------------------------------------------------------------------------
// Parallelism of two linear objects.
//---
class AppParallelNode final : public AppConstraintNode
{
  geom_item lineItem1;
  geom_item lineItem2;

public:
  AppParallelNode(AppGeomNodeCRef, AppGeomNodeCRef);
  ~AppParallelNode() override = default;

public:
  constraint_item Formulate(GCE_system) override;

public:
  AppParallelNode(const AppParallelNode &) = delete;
  AppParallelNode & operator = (const AppParallelNode &) = delete;
};

#endif  // PARAM_CONSTRAINT_NODE_H
