#include "pch.h"
#include "CCellAnimation.h"

#include "CObject.h"
#include "CTexture.h"
#include "CAnimator.h"

CCellAnimation::CCellAnimation()
{
}

CCellAnimation::~CCellAnimation()
{
}

void CCellAnimation::OnUpdate()
{

}

void CCellAnimation::OnRender(HDC canvas_) const
{
    const int width = static_cast<int>(m_pTextures[GetCurrentFrame()]->GetWidth());
    const int height = static_cast<int>(m_pTextures[GetCurrentFrame()]->GetHeight());
    const Vec2 pos = GetAnimator()->GetObj()->GetPos();

    const int drawX = static_cast<int>(pos.x - static_cast<float>(width) / 2.0f);
    const int drawY = static_cast<int>(pos.y - static_cast<float>(height) / 2.0f);

    TransparentBlt(
        canvas_,
        drawX, drawY,
        width, height,
        m_pTextures[GetCurrentFrame()]->GetDC(),
        0, 0, 
        width, height,
        RGB(255, 0, 255) // 마젠타 색상 투명 처리
    );
}