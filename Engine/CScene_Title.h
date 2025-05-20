#pragma once

#include <memory>

#include "CCore.h"
#include "CObject.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CScene.h"

#include "CTitleBackground.h"

class CScene_Title :
    public CScene
{
public:
    CScene_Title();
    virtual ~CScene_Title() override;

    virtual void Enter() override;
    virtual void update() override;
    virtual void Exit() override;

private:
    /**
     * @brief 백그라운드 이미지 오브젝트.
     */
    std::unique_ptr<CObject> m_pBackground;

    /**
     * @brief 타이틀 로고 오브젝트.
     */
    std::unique_ptr<CObject> m_pTitleLogo;

    /**
     * @brief "Enter 키를 눌러주세요" 메세지.
     */
    std::unique_ptr<CObject> m_pMessage;

    /**
     * @brief 현재 인트로 애니메이션 재생 중인가에 대한 여부.
     */
    bool m_bIsIntro;

};

