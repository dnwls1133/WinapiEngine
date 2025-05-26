#pragma once
#include "CAnimationBase.h"

class CTexture;

class CAnimationBase;
class CAnimator;

/**
 * @brief 셀 방식의 애니메이션을 정의합니다.
 */
class CCellAnimation 
    : public CAnimationBase
{
    friend class CAnimationBase;
    friend class CAnimator;
public:
    /**
     * @brief 생성자.
     */
    CCellAnimation();

    /**
     * @brief 소멸자.
     */
    virtual ~CCellAnimation() override;

protected:
    /**
     * @brief 해당 애니메이션을 업데이트합니다.
     */
    virtual void OnUpdate() override;

    /**
     * @brief 해당 애니메이션을 그립니다.
     * @param canvas_ 
     */
    virtual void OnRender(HDC canvas_) const override;

private:
    /**
     * @brief 애니메이션 셀.
     */
    std::vector<CTexture*> m_pTextures;

};

