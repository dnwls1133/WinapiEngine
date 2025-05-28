#pragma once

#include "CObject.h"

class CObject;
class CTexture;

/**
 * @brief 타이틀 Scene 내 재생되는 백그라운드 오브젝트에 대해 정의합니다.
 */
class CTitleBackground :
    public CObject
{
public:
    CTitleBackground();
    virtual ~CTitleBackground() override;

    virtual void update() override;
    virtual void render(HDC dc) override;

    void ChangeState() noexcept;

    void PlayIntroAnimation();
    void PlayTitleAnimation();

    bool IsPlayIntroAnimation() const noexcept;

    CLONE(CTitleBackground)

private:
    /**
     * @brief 인트로 시작 지점.
     */
    static constexpr size_t IDX_INTRO_START = 0;

    /**
     * @brief 인트로 종료 지점.
     */
    static constexpr size_t IDX_INTRO_END = 70;

    /**
     * @brief 타이틀 시작 지점.
     */
    static constexpr size_t IDX_TITLE_START = 0;

    /**
     * @brief 타이틀 종료 지점.
     */
    static constexpr size_t IDX_TITLE_END = 25;

    /**
     * @brief 텍스쳐.
     */
    CTexture* m_pTexture = nullptr;

    /**
     * @brief 현재 지점.
     */
    size_t m_currentIndex = 0;

    static constexpr float m_fAnimTime = 0.05f;

    /**
     * @brief 스프라이트 
     */
    float m_fAnimDeltaTime = 0.0f;

    bool m_bIsIntroState = false;
};
