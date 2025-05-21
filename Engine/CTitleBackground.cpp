#include "pch.h"
#include "CTitleBackground.h"

CTitleBackground::CTitleBackground()
{
}

CTitleBackground::~CTitleBackground()
{

}

void CTitleBackground::update()
{
    static constexpr size_t minAnimationIdx = 0;   // 최소
    static constexpr size_t maxAnimationIdx = 0;   // 최대
    static size_t curAnimationIdx;                 // 현재

    std::wstring filePath = TEXT(""); // 파일 경로.

    if (curAnimationIdx >= maxAnimationIdx)
    {
        curAnimationIdx = 0;
        return;
    }

    std::wstring textureKey = std::format(L"Title Background");
    std::wstring filePath = std::format(L"texture\\Backgrounds\\Title\\Opening\\Sprite_Background_Opening_{}.bmp", curAnimationIdx);
    m_pTexture = std::unique_ptr<CTexture>(CResMgr::GetInst()->LoadTexture(textureKey, filePath));
}
