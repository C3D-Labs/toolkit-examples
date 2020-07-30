////////////////////////////////////////////////////////////////////////////////
/**
\file
\brief \ru Класс OpenGLWidget - это виджет для рендеринга графики Vision с помощью OpenGL.
       \en NO TRANSLATION. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __OPENGLVIEW_H
#define __OPENGLVIEW_H

#include <afxwin.h>
#include <vsn_vision.h>
#include "mfc_openglview.h"
#include <vsn_global.h>

#include "mfc_visiondef.h"

VSN_BEGIN_NAMESPACE

/** \brief \ru ВНИМАНИЕ! Этот файл не является частью API Vision. Он необходим для иллюстрации использования
               ядра Vision с библиотекой MFC и ее классами. Этот заголовочный файл может изменяться от версии
               к версии без предупреждения или полностью удаляться.
            \en NO TRANSLATION. \~
*/

class Viewport;
class SceneContent;

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
class MFC_CLASS COpenGLView : public CView
{
    DECLARE_DYNCREATE(COpenGLView)
public:
    /// \ru Конструктор по умолчанию. \en NO TRANSLATION.
    explicit COpenGLView();
    /// \ru Деструктор COpenGLView освобождает созданные ресурсы. \en NO TRANSLATION.
    virtual ~COpenGLView();
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
    /// \ru Вернуть указатель на содержимое сцены. \en NO TRANSLATION. \~
    ObjectPickSelection*  GetObjectPickSelection() const;
protected:
    /// \ru Функция вызывается после инициализации Vision. \en NO TRANSLATION. \~
    virtual void InitializeOpenGL();
public:
    //!< We overload the Create method to modify the CWnd window style; necessary for OpenGL support
#ifdef _UNICODE
    virtual BOOL Create(__wchar_t const * lpszClassName, __wchar_t const * lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = nullptr);
    virtual BOOL Create(unsigned short const * lpszClassName, unsigned short const *  lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = nullptr);
#else
    virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = nullptr);
#endif
    virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
protected:
    virtual void OnDraw(CDC* pDC); //!< overridden but currently does nothing
    // for translating Windows messages in main message pump
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    //!< We overload the PreCreateWindow method to modify the CWnd window class; necessary for OpenGL support
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected: // Generated message map functions
    afx_msg void OnPaint();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDestroy();
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnKillFocus(CWnd* pNewWnd);
protected:
    DECLARE_MESSAGE_MAP()

    CSceneRenderer* m_pSceneRenderer;
};

} // namespace MfcVision

VSN_END_NAMESPACE

#endif // __OPENGLVIEW_H
