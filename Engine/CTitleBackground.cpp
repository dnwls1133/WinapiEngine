#include "pch.h"
#include "CTitleBackground.h"

void CTitleBackground::update()
{
    // if (curAnimationIdx >= maxAnimationIdx)
    // {
    //     curAnimationIdx = 0;
    //     return;
    // }
    // 
    // std::wstring textureKey = std::format(L"Title Background No.{}", curAnimationIdx);
    // std::wstring filePath = std::format(L"texture\\Backgrounds\\Title\\Opening\\Sprite_Background_Opening_{}.bmp", curAnimationIdx);
    // m_pTexture = std::unique_ptr<CTexture>(CResMgr::GetInst()->LoadTexture(textureKey, filePath));
}

void CTitleBackground::render(HDC dc)
{

}
