#include "pch.h"
#include "CMenuItem.h"

#include "CTexture.h"

void CMenuItem::MouseOn()
{
    if (m_pHoverTexture)
        m_pTexture = m_pHoverTexture;

    const float curScaleX = GetScale().x * 1.25f;
    const float curScaleY = GetScale().y * 1.25f;

    SetScale(Vec2(curScaleX, curScaleY));
}

void CMenuItem::MouseLbtnUP()
{
    if (m_pIdleTexture)
        m_pTexture = m_pIdleTexture;

    const float curScaleX = GetScale().x * 1.25f;
    const float curScaleY = GetScale().y * 1.25f;
    SetScale(Vec2(curScaleX, curScaleY));
}

void CMenuItem::MouseLbtnDown()
{
    if (m_pHoverTexture)
        m_pTexture = m_pHoverTexture;

    const float curScaleX = GetScale().x / 1.25f;
    const float curScaleY = GetScale().y / 1.25f;
    SetScale(Vec2(curScaleX, curScaleY));
}

void CMenuItem::render(HDC canvas_)
{
    if (!m_pTexture)
        return;

    Vec2 position = GetFinalPos();
    Vec2 scale = GetScale();

    BitBlt(
        canvas_,
        position.x, position.y,
        scale.x, scale.y,
        m_pTexture->GetDC(),
        0, 0,
        SRCCOPY);

    CUI::render(canvas_);
}
