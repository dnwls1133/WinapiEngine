#pragma once

#include "CScene.h"
class CScene;

class CTitleLogo;
class CTitleBackground;
// class CTitleMessage;

class CSound;

class CBtnUI;

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
    // void mChangeToIntro();
    // void mChangeToTitle();

    CTitleBackground* m_pBackground;    // 배경

    CTitleLogo* m_pLogo;                   // 로고
    CObject* m_pMessage;                // 메시지

    CBtnUI* m_pStartButton;             // 시작 버튼
    CBtnUI* m_pManuelButton;            // 조작법 버튼
    CBtnUI* m_pExitButton;              // 종료 버튼

    CSound* m_pTitleTheme;

    enum class EState
    {
        None,
        Intro,
        Title,
    };

    EState m_CurrentState;
};
