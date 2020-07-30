#ifndef __OPENGLWINDOW_H
#define __OPENGLWINDOW_H

#include <afxwin.h>
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

class CSceneRenderer;
//------------------------------------------------------------------------------
/** \brief \ru Класс COpenGLView - это окно для рендеринга графики Vision с помощью OpenGL.
           \en NO TRANSLATION. \~
    \details \ru .
             \en NO TRANSLATION. \n \~
    \ingroup Vision_OpenGL
*/
// ---
class MFC_CLASS COpenGLWnd : public CWnd
{
    DECLARE_DYNCREATE(COpenGLWnd)
public:
    /// \ru Конструктор по умолчанию. \en NO TRANSLATION.
    COpenGLWnd();
    /// \ru Деструктор OpenGLWnd освобождает созданные ресурсы. \en NO TRANSLATION.
    virtual ~COpenGLWnd();
public:
    /// \ru Вернуть указатель на источник освешения сцены. \en Returns a pointer to scene lighting source. \~
    Light* GetMainLight() const;
    /// \ru Вернуть указатель на Viewport для отображения сцены. \en NO TRANSLATION. \~
    Viewport* GetViewport() const;
    /// \ru Вернуть указатель на содержимое сцены. \en NO TRANSLATION. \~
    SceneContentPtr GetSceneContent() const;
    /// \ru Вернуть указатель на GraphicsView. \en NO TRANSLATION. \~
    GraphicsViewPtr GetGraphicsView() const;
protected:
    /// \ru Функция вызывается после инициализации Vision. \en NO TRANSLATION. \~
    virtual void InitializeOpenGL();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
    //{{AFX_MSG(MFCContext
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDestroy();
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg void OnPaint();
    afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
    DECLARE_MESSAGE_MAP()
private:
    CSceneRenderer* m_pSceneRenderer;
};

} // namespace MfcVision

VSN_END_NAMESPACE


#endif /* __OPENGLWINDOW_H */

