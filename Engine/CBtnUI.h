#pragma once
#include "CUI.h"

typedef void(*BRN_FUNC) (DWORD_PTR, DWORD_PTR);

class CBtnUI :
    public CUI
{
private:
    BRN_FUNC    m_pFunc;
    DWORD_PTR   m_param1;
    DWORD_PTR   m_param2;
public:
    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUP();
    virtual void MouseLbtnClicked();

    void SetClickedCallBack(BRN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2 )
    {
        m_pFunc = _pFunc;
        m_param1 = _param1;
        m_param2 = _param2;
    }

    CLONE(CBtnUI);
public:
    CBtnUI();
    ~CBtnUI();
};

