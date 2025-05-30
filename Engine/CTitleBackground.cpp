#include "pch.h"
#include "CTitleBackground.h"

#include "CTexture.h"
#include "CObject.h"
#include "CResMgr.h"
#include "CTimeMgr.h"

CTitleBackground::CTitleBackground()
{
    const std::wstring textureKey = L"Introduction No.0";
    const std::wstring filePath = L"texture\\Sprites\\Backgrounds\\Title\\Opening\\Sprite_Background_Opening_0.bmp";
    m_pTexture = CResMgr::GetInst()->LoadTexture(textureKey, filePath);
}

CTitleBackground::~CTitleBackground()
{

}

void CTitleBackground::update()
{
    if (!m_bIsPlaying)
        return;

    m_dAnimDeltaTime += CTimeMgr::GetInst()->GetfDT();

    if (m_dAnimDeltaTime >= m_dAnimTime)
    {
        m_dAnimDeltaTime = 0.0f;

        if (!m_bIsIntroState)
        {
            if (++m_currentIndex >= IDX_INTRO_END)
            {
                m_bIsPlaying = false;
                m_currentIndex = IDX_INTRO_END;
            }

            const std::wstring textureKey = std::format(L"Introduction No.{}", m_currentIndex);
            const std::wstring filePath = std::format(L"texture\\Sprites\\Backgrounds\\Title\\Opening\\Sprite_Background_Opening_{}.bmp", m_currentIndex);
            m_pTexture = CResMgr::GetInst()->LoadTexture(textureKey, filePath);
        }
        else
        {
            if (++m_currentIndex >= IDX_TITLE_END)
            {
                m_bIsPlaying = false;
                m_currentIndex = IDX_TITLE_END;
            }

            const std::wstring textureKey = std::format(L"Main Title No.{}", m_currentIndex);
            const std::wstring filePath = std::format(L"texture\\Sprites\\Backgrounds\\Title\\Main Title\\Sprite_Background_MainTitle_{}.bmp", m_currentIndex);
            m_pTexture = CResMgr::GetInst()->LoadTexture(textureKey, filePath);
        }
    }
}

void CTitleBackground::render(HDC dc)
{
    if (!m_pTexture)
        return;

    const int width = static_cast<int>(m_pTexture->Width());
    const int height = static_cast<int>(m_pTexture->Height());
    const Vec2 pos = GetPos();

    const int drawX = static_cast<int>(pos.x - static_cast<float>(width) / 2.0f);
    const int drawY = static_cast<int>(pos.y - static_cast<float>(height) / 2.0f);

    TransparentBlt(
        dc,
        drawX, drawY,
        width, height,
        m_pTexture->GetDC(),
        0, 0, 1280, 960,
        RGB(255, 0, 255) // 마젠타 색상 투명 처리
    );
}

void CTitleBackground::PlayIntroAnimation() noexcept
{
    m_bIsIntroState = true;
    m_currentIndex = IDX_INTRO_START;
}

void CTitleBackground::PlayTitleAnimation() noexcept
{
    m_bIsIntroState = false;
    m_currentIndex = IDX_TITLE_START;
}

bool CTitleBackground::IsPlayIntroAnimation() const noexcept
{
    return m_bIsIntroState;
}
