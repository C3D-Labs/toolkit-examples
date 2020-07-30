////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Примеры процессов и моделей виджетов.
         \en examples of widget models and processes. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __UTILS_H
#define __UTILS_H


#include "vsn_prchangewidget.h"
#include "vsn_widgetmodels.h"

VSN_BEGIN_NAMESPACE

class DefaultModles
{
public:
    static const std::shared_ptr<Widget3DModel> baseModel;
    static const std::shared_ptr<Widget3DModel> rotateModel;
    static const std::shared_ptr<Widget3DModel> directModel;
    static const std::shared_ptr<Widget3DModel> pointModel;
    static const std::shared_ptr<WidgetCanvasModel> rectModel;
    static const std::shared_ptr<WidgetCanvasModel> positionModel;

    static const std::shared_ptr<Widget3DModel> boxModel;
};

class DefaultProcesses
{
public:
    static const std::shared_ptr<WidgetProcess> spaceMove;
    static const std::shared_ptr<WidgetProcess> xlocalMove;
    static const std::shared_ptr<WidgetProcess> ylocalMove;
    static const std::shared_ptr<WidgetProcess> zlocalMove;

    static const std::shared_ptr<WidgetProcess> xylocalMove;

    static const std::shared_ptr<WidgetProcess> xRotate;
    static const std::shared_ptr<WidgetProcess> yRotate;
    static const std::shared_ptr<WidgetProcess> zRotate;
};

std::shared_ptr<WidgetProcess> createCurveMoveProcess(SPtr<const MbCurve3D> curve, bool local = true);
std::shared_ptr<WidgetProcess> createSurfaceMoveProcess(SPtr<const MbSurface> surface, bool local = true);
std::shared_ptr<WidgetProcess> createTouchProcess(std::shared_ptr<WidgetProcess> otherProcess);


VSN_END_NAMESPACE

#endif