#ifndef __SCENERENDERER_H
#define __SCENERENDERER_H

#include <afxwin.h>
#include <vsn_object.h>
#include <vsn_vision.h>
#include <vsn_global.h>
#include "mfc_visiondef.h"

VSN_BEGIN_NAMESPACE

/** \brief \ru ВНИМАНИЕ! Этот файл не является частью API Vision. Он необходим для иллюстрации использования
               ядра Vision с библиотекой MFC и ее классами. Этот заголовочный файл может изменяться от версии
               к версии без предупреждения или полностью удаляться.
            \en NO TRANSLATION. \~
*/

namespace MfcVision {


class COpenGLWndPrivate;
/* CSceneRenderer */
class MFC_CLASS CSceneRenderer : public Object
{
    VSN_OBJECT(CSceneRenderer)
public:
    /// \ru Конструктор по умолчанию. \en NO TRANSLATION.
    CSceneRenderer();
    /// \ru Деструктор OpenGLWnd освобождает созданные ресурсы. \en NO TRANSLATION.
    virtual ~CSceneRenderer();
public:
    /**
    \brief \ru Подготовка OpenGL для рендеринга в этом виджете(установить текущий OpenGL контекст.
           \en NO TRANSLATION.
        \detaild \ru Нет необходимости вызывать эту функцию в большинстве случаев, потому что она вызывается автоматически перед вызовом paintGL().
                 \en NO TRANSLATION.
    */
    void MakeCurrent();
    /**
    \brief \ru Освободить OpenGL контекст.
           \en NO TRANSLATION.
        \detaild \ru Нет необходимости вызывать эту функцию в большинстве случаев, поскольку
                     в функции paintGL() контекст будет назначен и освобожден.
                 \en NO TRANSLATION.
    */
    void DoneCurrent();
public:
    /// \ru Вернуть указатель на источник освешения сцены. \en Returns a pointer to scene lighting source. \~
    Light* GetMainLight() const;
    /// \ru Вернуть указатель на Viewport для отображения сцены. \en NO TRANSLATION. \~
    Viewport* GetViewport() const;
    /// \ru Вернуть указатель на содержимое сцены. \en NO TRANSLATION. \~
    GraphicsScene* GetGraphicsScene() const;
    /// \ru Вернуть указатель на содержимое сцены. \en NO TRANSLATION. \~
    SceneContentPtr GetSceneContent() const;
    /// \ru Вернуть указатель на GraphicsView. \en NO TRANSLATION. \~
    GraphicsViewPtr GetGraphicsView() const;
public:
    /// \ru Создать CSceneRenderer и захватить все необходимые рисурсы. \en NO TRANSLATION. \~
    void DoCreate(HWND hWnd);
    /// \ru Разрушить и освободить ресурсы Vision. \en NO TRANSLATION. \~
    void DoDestroy();
    /// \ru Подготовка Vision для отрисовки сцены. \en NO TRANSLATION. \~
    void DoPreparingToDisplay();
    /// \ru Отрисовать сцену. \en NO TRANSLATION. \~
    void DoDraw();
    /// \ru Изменить размер Viewport. \en NO TRANSLATION. \~
    void DoResize(int w, int h);
    //
    void DoSetFocus(CWnd* pOldWnd);
    void DoKillFocus(CWnd* pNewWnd);

    /// \ru Перегрузка для внутренних работ. \en Overload for internal workings.
    virtual bool OnWinEvent(MSG* pMsg, long* result);
public:
    VSN_SLOT(Public, RepaintWindow, void RepaintWindow())
protected:
    virtual void InitializeOpenGL();
    virtual void PaintOpenGL();
private:
    VSN_DECLARE_PRIVATE(CSceneRenderer)
};

enum ProcessType
{
    pt_Pan = 0x01,
    pt_Orbit = 0x02,
    pt_Zoom = 0x04,
    pt_AllProcess = pt_Orbit | pt_Zoom | pt_Pan,
};
VSN_DECLARE_FLAGS(ProcessTypes, ProcessType)


/// \ru Создание процессов для управления камерой. \en Creating processes to control the camera. \~
MFC_FUNC(void) CreateProcessesCameraControls(Viewport* pViewport, Node* pParent, ProcessTypes prType = pt_AllProcess);

} // namespace MfcVision

VSN_END_NAMESPACE

#endif /* __OPENGLWINDOW_H */
