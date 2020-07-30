#include "utils.h"

#include "vsn_coordlocator.h"
#include "vsn_prchangewidget.h"
#include "vsn_widgetmodels.h"
#include "surf_plane.h"
#include "vsn_painter.h"
#include "vsn_brush.h"
#include "vsn_image.h"
#include "vsn_planemarker.h"
#include "mb_axis3d.h"

#include <last.h>


VSN_BEGIN_NAMESPACE

std::shared_ptr<Widget3DModel> createBaseModel()
{
    std::shared_ptr<Widget3DModel> model(new Widget3DModel());

    double l = 40.0;
    double ln = l*1.4;

    model->AddCylinder(1, {}, { l,0,0 }, 2.5, Color(200, 0, 0));
    model->AddCone(1, { l,0,0 }, { ln,0,0 }, 5, Color(200, 0, 0));
    model->AddCylinder(2, {}, { 0,l,0 }, 2.5, Color(0, 200, 0));
    model->AddCone(2, { 0,l,0 }, { 0, ln, 0 }, 5, Color(0, 200, 0));
    model->AddCylinder(3, {}, { 0,0,l }, 2.5, Color(0, 0, 200));
    model->AddCone(3, { 0,0,l }, { 0,0,ln }, 5, Color(0, 0, 200));

    //model->AddSphere(-1, { ln,ln ,ln }, 5, Color(200, 0, 0));

    model->AddMarker(-1, { ln+5, 0, 0 }, MarkerID::labelX);
    model->AddMarker(-1, { 0, ln+5, 0 }, MarkerID::labelY);
    model->AddMarker(-1, { 0, 0, ln+5 }, MarkerID::labelZ);

    return model;
}

std::shared_ptr<Widget3DModel> createRotateModel()
{
    std::shared_ptr<Widget3DModel> model(new Widget3DModel());
    double l = 40.0;
    double ln = l*1.4;

    model->AddTorus(1, {}, { l,0,0 }, 1.5, Color(200, 0, 0), 0, M_PI);
    model->AddTorus(2, {}, { 0,-l,0 }, 1.5, Color(0, 200, 0), 0, M_PI);
    model->AddTorus(3, {}, { 0,0,l }, 1.5, Color(0, 0, 200));

    return model;
}

std::shared_ptr<Widget3DModel> createDirectModel()
{
    std::shared_ptr<Widget3DModel> model(new Widget3DModel());

    double l = 40.0;
    double ln = l*1.4;

    model->AddCylinder(0, {}, { 0,0,l }, 2.8, Color(20, 140, 200));
    model->AddCone(0, { 0,0,l }, { 0,0,ln }, 6, Color(20, 140, 200));
    model->AddCube(0, {-5, -5 ,-5 }, { 5, 5, 5 }, Color(220, 220, 220));

    return model;
}

std::shared_ptr<Widget3DModel> createSphereModel()
{
    std::shared_ptr<Widget3DModel> model(new Widget3DModel());

    model->AddSphere(0, {}, 5, Color(255, 0, 0));

    return model;
}

std::shared_ptr<WidgetCanvasModel> createRectModel()
{
    std::shared_ptr<WidgetCanvasModel> model(new WidgetCanvasModel());

    Painter p(model->GetCanvas());

    p.Begin();
    p.SetFillBrush(SolidBrush(Color(10,141,211)));
    p.DrawFillRect({ -4,-4 }, { 4,4 });
    p.End();

    return model;
}


std::shared_ptr<WidgetCanvasModel> createPositionModel()
{
    std::shared_ptr<WidgetCanvasModel> model(new WidgetCanvasModel());

    Painter p(model->GetCanvas());

    double r = 6.0;
    p.Begin();
    p.SetFillBrush(SolidBrush(Color(10, 141, 211)));
    p.DrawFillCircle({ 0.0,r*2.0 }, r);
    p.DrawTrianglesPath({ { 0.0,0.0 },{ r*0.7,r*1.2 },{ -r*0.7,r*1.2 } });
    p.End();

    return model;
}


std::shared_ptr<WidgetProcess> createSpaceMoveProcess()
{
    std::shared_ptr<MoveWidgetProcess> process(new MoveWidgetProcess(nullptr));
    process->SetLocator(new ModelCoordLocator(process.get()));

    return process;
}

std::shared_ptr<WidgetProcess> createTouchProcess(std::shared_ptr<WidgetProcess> otherProcess )
{
    std::shared_ptr<TouchWidgetProcess> process(new TouchWidgetProcess(nullptr));
    process->SetWorkProcess(otherProcess.get());

    return process;
}

std::shared_ptr<WidgetProcess> createCurveMoveProcess(SPtr<const MbCurve3D> curve, bool local)
{
    std::shared_ptr<MoveWidgetProcess> process(new MoveWidgetProcess(nullptr));
    process->SetLocator(new CurveScreenCoordLocator(curve, process.get()));
    process->SetConvertPlacement(local ? WidgetConvertPlacements::Widget : WidgetConvertPlacements::Scene);
    return process;
}

std::shared_ptr<WidgetProcess> createRotateProcess(const MbAxis3D & axis)
{
    std::shared_ptr<RotateWidgetProcess> process(new RotateWidgetProcess(axis));
    process->SetStep(Math::PI2/72.0);

    return process;
}

std::shared_ptr<WidgetProcess> createSurfaceMoveProcess(SPtr<const MbSurface> surface, bool local)
{
    std::shared_ptr<MoveWidgetProcess> process(new MoveWidgetProcess(nullptr));

    process->SetLocator(new SurfaceScreenCoordLocator(surface, process.get()));
    process->SetConvertPlacement(local ? WidgetConvertPlacements::Widget : WidgetConvertPlacements::Scene);

    return process;
}

VSN_END_NAMESPACE
VSN_USE_NAMESPACE

const std::shared_ptr<Widget3DModel>     DefaultModles::baseModel     = createBaseModel();
const std::shared_ptr<Widget3DModel>     DefaultModles::rotateModel   = createRotateModel();
const std::shared_ptr<Widget3DModel>     DefaultModles::directModel   = createDirectModel();
const std::shared_ptr<Widget3DModel>     DefaultModles::pointModel    = createSphereModel();
const std::shared_ptr<WidgetCanvasModel> DefaultModles::rectModel     = createRectModel();
const std::shared_ptr<WidgetCanvasModel> DefaultModles::positionModel = createPositionModel();

const std::shared_ptr<WidgetProcess> DefaultProcesses::spaceMove  = createSpaceMoveProcess();
const std::shared_ptr<WidgetProcess> DefaultProcesses::xlocalMove = createCurveMoveProcess(SPtr<MbCurve3D>(new MbLine3D({}, MbCartPoint3D{ 1,0,0 })));
const std::shared_ptr<WidgetProcess> DefaultProcesses::ylocalMove = createCurveMoveProcess(SPtr<MbCurve3D>(new MbLine3D({}, MbCartPoint3D{ 0,1,0 })));
const std::shared_ptr<WidgetProcess> DefaultProcesses::zlocalMove = createCurveMoveProcess(SPtr<MbCurve3D>(new MbLine3D({}, MbCartPoint3D{ 0,0,1 })));

const std::shared_ptr<WidgetProcess> DefaultProcesses::xylocalMove = createSurfaceMoveProcess(SPtr<MbSurface>(new MbPlane()));

const std::shared_ptr<WidgetProcess> DefaultProcesses::xRotate = createRotateProcess(MbAxis3D::xAxis);
const std::shared_ptr<WidgetProcess> DefaultProcesses::yRotate = createRotateProcess(MbAxis3D::yAxis);
const std::shared_ptr<WidgetProcess> DefaultProcesses::zRotate = createRotateProcess(MbAxis3D::zAxis);
