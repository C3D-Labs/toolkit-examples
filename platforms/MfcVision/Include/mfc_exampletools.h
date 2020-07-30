#ifndef __EXAMPLETOOLS_H
#define __EXAMPLETOOLS_H


#include <afxwin.h>
#include "mfc_visiondef.h"

#include <vsn_application.h>
#include <mfc_openglview.h>
#include "mfc_licensewnd.h"
#include "mfc_exampleview.h"
#include <functional>

VSN_BEGIN_NAMESPACE
namespace MfcVision {

template<class Type>
class ExampleInput
{
public:
    virtual ExampleInput & operator = (std::function<void(Type)>);
public:
    virtual void setValue(const Type &) {};
protected:
    std::function<void(Type)> m_callBack;
};

template<typename Type>
ExampleInput<Type> & ExampleInput<Type>::operator = (std::function<void(Type)> func)
{
    m_callBack = func;
    return *this;
}

class MFCExampleInputIterface
{
public:
    virtual ~MFCExampleInputIterface() {};
    virtual HWND Create(CWnd * parent) = 0;
    virtual const char * GetLabel() const = 0;
    virtual int SetPosition(int top, int width, int height) = 0; // return own height

    virtual void RunCommand() = 0;
};

template<class CClass, class ValueType>
class MFCExampleInput : public ExampleInput<ValueType>,
                        public MFCExampleInputIterface
{
public:
    using creator = std::function<bool(CClass&, CWnd * parent)>;
public:
    MFCExampleInput( const std::string & label, creator);
public:
    virtual HWND   Create(CWnd * parent) override;
    virtual const char * GetLabel() const override { return m_label.c_str(); }
    virtual int SetPosition(int top, int width, int height) override; // return own height

    virtual void RunCommand() override {};
private:
    std::string  m_label;
    CStatic   m_wndLabel;
    CClass    m_wndInput;

    creator   m_creator;
};

template<class CClass, class ValueType>
MFCExampleInput<CClass, ValueType>::MFCExampleInput(const std::string & label, typename MFCExampleInput<CClass, ValueType>::creator c)
    : m_label(label)
    , m_creator(c)
{

}

template<class CClass, class ValueType>
HWND MFCExampleInput<CClass, ValueType>::Create(CWnd * parent)
{
    if (m_creator && m_creator(m_wndInput, parent))
    {
        if (!m_label.empty())
        {

        }

        return m_wndInput.GetSafeHwnd();
    }

    return  0;
}

template<class CClass, class ValueType>
int MFCExampleInput<CClass, ValueType>::SetPosition(int top, int width, int height)
{
    int left = 5;
    int w = width - left * 2;

    if (m_wndInput.GetSafeHwnd() != 0)
        m_wndInput.SetWindowPos(NULL, left, top, w, 100, SWP_NOZORDER);

    return height;
}

void MFCExampleInput<CComboBox, int>::RunCommand()
{
    if (m_callBack && m_wndInput.GetSafeHwnd())
        m_callBack(m_wndInput.GetCurSel());
}

class MFC_CLASS CExampleTools : public CWnd
{
public:
    void addItem(std::shared_ptr<MFCExampleInputIterface>);

    bool IsEmpty() const { return m_items.empty(); }
protected:
    afx_msg BOOL OnCreate(LPCREATESTRUCT);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);

protected:
    virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam) override;
private:
    void updateLayout();
    void changeSelect(CWnd * pComboBox);

    std::list<std::shared_ptr<MFCExampleInputIterface>> m_items;
    std::map<HWND, std::weak_ptr<MFCExampleInputIterface>> m_events;
protected:
    DECLARE_MESSAGE_MAP()
};

class MFC_CLASS ExampleWindow : public CFrameWnd
{
public:
    ExampleWindow( ExampleView * pView );
    virtual ~ExampleWindow();

public:
    ExampleInput<int> & comboBox(const std::string & label, const std::vector<std::string> & items, int default = 0);
public:
    void SetSceneLoader(std::function<void(GraphicsScene * pScene)> callback);// load scene after activate license
protected:
    afx_msg BOOL OnCreate(LPCREATESTRUCT);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg LRESULT OnActivateLicense(WPARAM, LPARAM);
private:
    void updateLayout();
    void showExampleView();
    void showExampleInput();
private:
    LicenceWnd m_licenceWnd;
    ExampleView * m_pView = nullptr;
    CExampleTools m_inputPanel;

    std::function<void(GraphicsScene * pScene)> m_loadSceneCallback; // load scene after activate license
protected:
    DECLARE_MESSAGE_MAP()
};

} // namespace MfcVision
VSN_END_NAMESPACE

#endif /*__EXAMPLETOOLS_H*/