#pragma once

#include "CBtnUI.h"

class CTexture;

class CMenuItem
    : public CBtnUI
{
    friend class CBtnUI;
public:
    CMenuItem(CTexture* const idleTex_, CTexture* const hoverTex_)
        : m_pTexture(idleTex_)
        , m_pIdleTexture(idleTex_)
        , m_pHoverTexture(hoverTex_)
    {
        // SetScale();
    }

    virtual ~CMenuItem() override
    {
        // 텍스쳐는 외부에서 관리하므로 소멸자는 비워둠.
    }

    virtual void MouseOn() override;
    virtual void MouseLbtnDown() override;
    virtual void MouseLbtnUP() override;
    // virtual void MouseLbtnClicked() override;

    virtual void render(HDC canvas_) override;

private:
    bool m_bIsHover = false;

    CTexture* m_pTexture;               // 현재 사용중인 텍스쳐.
    CTexture* const m_pIdleTexture;     // 일반 텍스쳐.
    CTexture* const m_pHoverTexture;    // 호버 텍스쳐.

};

