#ifndef __NURBSEDITOR_H
#define __NURBSEDITOR_H

#include "vsn_viewport.h"
#include "vsn_graphicsscene.h"



VSN_BEGIN_NAMESPACE

class SceneWidget;
class WidgetProcess;
class SceneSegment;
class MathRepresentation;
class NurbsEditor : public VSN::Object
{
    VSN_OBJECT(NurbsEditor);
public:
    NurbsEditor( GraphicsScene * scene );
    virtual ~NurbsEditor();

public:
    /// build geometry
    void Build();
public:
    void Hide();
    void Show();

protected:
    /// add point widget into scene
    void AddPointWidget(uint32_t index, MbCartPoint3D position);
    /// update position of the trimming widget
    void UpdateTrimmingWidget();
public:
    VSN_SLOT(Public, slotModify, void slotModify(SceneWidget*));
    VSN_SLOT(Public, slotTrimming, void slotTrimming(SceneWidget*));

private:
    SArray<MbCartPoint3D> m_points;
    GraphicsScene *       m_pScene    = nullptr;
    SceneSegment*         m_root      = nullptr;
    SPtr<MbNurbs3D>       m_sourceCurve; // source nurbs
    MathRepresentation *  m_nurbs_1   = nullptr;
    MathRepresentation *  m_nurbs_2   = nullptr;
    MathRepresentation *  m_polyline  = nullptr;
    double                m_trimValue = 0.0;

    std::vector<SceneWidget*>      m_widgets;
    SceneWidget*                   m_trimmingWidget = nullptr;
    std::shared_ptr<WidgetProcess> m_trimProcess; //  process of moving trimming widget by curve
};

VSN_END_NAMESPACE

#endif