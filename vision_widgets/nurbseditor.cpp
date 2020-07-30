#include "vsn_pen.h"
#include "nurbseditor.h"
#include "utils.h"

#include "vsn_widgets.h"
#include "vsn_scenegenerator.h"
#include "vsn_scenecontent.h"

#include "mesh.h"
#include "space_instance.h"
#include "cur_line_segment3d.h"
#include "cur_nurbs3d.h"
#include "cur_polyline3d.h"

#include <last.h>

VSN_USE_NAMESPACE

//-----------------------------------------------------------------------------
//
// ---
NurbsEditor::NurbsEditor( GraphicsScene * pScene )
    : m_pScene(pScene)
{  
    /// base point of nurbs
    m_points.Add({ 80, -43, 35 });
    m_points.Add({ 42, -48, 86 });
    m_points.Add({ 36, -27, 36 });
    m_points.Add({ 18, -49, 25 });

    /// root scenesegment of nurbs
    m_root = new SceneSegment(pScene->GetSceneContent()->GetRootSegment());

    /// build geometry
    Build();
    
    /// add point widgets
    for(uint32_t i = 0; i < m_points.size(); ++ i)
        AddPointWidget(i, m_points[i]);
    /// add trimming widget
    UpdateTrimmingWidget();
}

//-----------------------------------------------------------------------------
//
// ---
NurbsEditor::~NurbsEditor()
{

}

//-----------------------------------------------------------------------------
//  build geometry
// ---
void NurbsEditor::Build()
{
    /// create source curve
    if (!m_sourceCurve)
    {
        m_sourceCurve = MbNurbs3D::Create(3, m_points, false, nullptr);
        m_trimValue = (m_sourceCurve->GetTMax() + m_sourceCurve->GetTMin())*0.5; // center of curve
    }

    /// update curve by points
    if( m_sourceCurve->Init(3, m_points, false) )
    {
        auto buildCurve = [](MathRepresentation * rep, const SPtr<MbCurve3D> & curve) {
            SPtr<MbSpaceInstance> inst(new MbSpaceInstance(*curve));
            SPtr<MbMesh> pMesh(new MbMesh());
            inst->CalculateMesh(MbStepData(ist_SpaceStep, 0.02), MbFormNote(), *pMesh);

            rep->SetMathItem(pMesh);
        };

        /// curve with solid style
        if (!m_nurbs_1)
        {
            m_nurbs_1 = new MathRepresentation();
            m_nurbs_1->GetGeomAt(0)->SetPen(Pen(Color(50,200,60), 2.0f));
            m_nurbs_1->SetBuildType(MathGeometry::Synchronous);
            new SceneSegment(m_nurbs_1, m_root);
        }

        /// curve with dashed style
        if (!m_nurbs_2)
        {
            m_nurbs_2 = new MathRepresentation();
            m_nurbs_2->GetGeomAt(0)->SetPen(Pen(1.0f, PenStyle::dashed, Color(10,140,200)));
            m_nurbs_2->SetBuildType(MathGeometry::Synchronous);
            new SceneSegment(m_nurbs_2, m_root);
        }

        /// update geometry
        buildCurve(m_nurbs_1, SPtr<MbCurve3D>(m_sourceCurve->Trimmed(m_sourceCurve->GetTMin(), m_trimValue, 1)));
        buildCurve(m_nurbs_2, SPtr<MbCurve3D>(m_sourceCurve->Trimmed(m_trimValue, m_sourceCurve->GetTMax(), 1)));
        
        /// update polyline
        SPtr<MbPolyline3D> polyLine(new MbPolyline3D(m_points, false));
        {
            SPtr<MbSpaceInstance> inst(new MbSpaceInstance(*polyLine));
            SPtr<MbMesh> pMesh(new MbMesh());

            inst->CalculateMesh(MbStepData(ist_SpaceStep, 0.02), MbFormNote(), *pMesh);

            if (!m_polyline)
            {
                m_polyline = new MathRepresentation();
                m_polyline->GetGeomAt(0)->SetPen(Pen(1.0f, PenStyle::dashed));
                m_polyline->SetBuildType(MathGeometry::Synchronous);
                (new SceneSegment(m_polyline, m_root))->SetRenderLayer(2);
            }
            m_polyline->SetMathItem(pMesh);
        }
    }
}

//-----------------------------------------------------------------------------
// add point widget to move points of burbs
// ---
void NurbsEditor::AddPointWidget(uint32_t index, MbCartPoint3D position)
{
   static auto process = createTouchProcess(DefaultProcesses::spaceMove);

   auto widget = new SceneWidget(m_pScene, DefaultModles::pointModel, position);
   widget->SetCustomKey(NodeKey(index));
   // set moving process to element with id equal 0
   widget->AssignProcess(0, process.get());
   m_widgets.push_back(widget);
   /// connect modify signal with editor
   Object::Connect(widget, &SceneWidget::OnModified, this, &NurbsEditor::slotModify);
}

//-----------------------------------------------------------------------------
//  update position of the trimming widget
// ---
void NurbsEditor::UpdateTrimmingWidget()
{
    MbCartPoint3D position;
    m_sourceCurve->PointOn(m_trimValue, position);

    if( !m_trimmingWidget )
    {
        // create trimming widget
        m_trimProcess = createCurveMoveProcess(m_sourceCurve, false);
        m_trimmingWidget = new SceneWidget(m_pScene, DefaultModles::positionModel, MbCartPoint3D());
        m_trimmingWidget->AssignProcess(0, m_trimProcess.get());

        Object::Connect(m_trimmingWidget, &SceneWidget::OnModified, this, &NurbsEditor::slotTrimming);
    }

    m_trimmingWidget->Init(position);
}

//-----------------------------------------------------------------------------
//  widget change event
// ---
void NurbsEditor::slotModify(SceneWidget * item)
{
    auto key = item->GetCustomKey();
    m_points[key.GetKey()] = item->GetOrigin();

    Build();
    UpdateTrimmingWidget();
}

//-----------------------------------------------------------------------------
//  widget change event
// ---
void NurbsEditor::slotTrimming(SceneWidget * item)
{
    MbCartPoint3D point = item->GetOrigin();
    
    if (m_sourceCurve->NearPointProjection(point, m_trimValue, true))
        Build();
}


void NurbsEditor::Hide()
{
    for (auto w : m_widgets)
        w->SetVisible(false);

    m_root->SetVisible(false);
    m_trimmingWidget->SetVisible(false);
}

void NurbsEditor::Show()
{
    for (auto w : m_widgets)
        w->SetVisible(true);

    m_root->SetVisible(true);
    m_trimmingWidget->SetVisible(true);
}