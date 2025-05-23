#include "pch.h"
#include "CTitleBackground.h"

CTitleBackground::CTitleBackground()
{
    const std::wstring textureKey = L"Title Background No.0";
    const std::wstring filePath = L"texture\\Sprites\\Backgrounds\\Title\\Opening\\Sprite_Background_Opening_0.bmp";
    m_pTexture = CResMgr::GetInst()->LoadTexture(textureKey, filePath);
}

CTitleBackground::~CTitleBackground()
{

}

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
    m_dAnimDeltaTime += CTimeMgr::GetInst()->GetfDT();

    if (m_dAnimDeltaTime >= m_dAnimTime)
    {
        m_dAnimDeltaTime = 0.0f;
        if (++m_currentIndex >= IDX_INTRO_END)
        {
            m_currentIndex = IDX_INTRO_START;
        }
    }

    const std::wstring textureKey = std::format(L"Title Background No.{}", m_currentIndex);
    const std::wstring filePath = std::format(L"texture\\Sprites\\Backgrounds\\Title\\Opening\\Sprite_Background_Opening_{}.bmp", m_currentIndex);
    m_pTexture = CResMgr::GetInst()->LoadTexture(textureKey, filePath);
}

void CTitleBackground::render(HDC dc)
{
    const int iWidith = static_cast<int>(m_pTexture->Width());
    const int iHeight = static_cast<int>(m_pTexture->Height());
    const Vec2 vPos = GetPos();

    //BitBlt(_dc, int(vPos.x - (float)(iWidith / 2))
    //	, int(vPos.y - (float)(iHeight / 2))
    //	, iWidith, iHeight
    //	, m_pTex->GetDC()
    //	, 0, 0, SRCCOPY);

    TransparentBlt(dc
        , static_cast<int>(vPos.x - (float)(iWidith / 2))
        , static_cast<int>(vPos.y - (float)(iHeight / 2))
        , iWidith, iHeight
        , m_pTexture->GetDC()
        , 0, 0, iWidith, iHeight
        , RGB(255, 0, 255)); // 색상을 무시하고 나머지 복사해라

    //BitBlt(_dc, int(vPos.x - (float)(iWidith / 2))
    //	, int(vPos.y - (float)(iHeight / 2))
    //	, iWidith, iHeight
    //	, m_pTex->GetDC()
    //	, 0, 0, SRCCOPY);


}
