#pragma once

#include "CScene.h"
class CScene;

class CTitleBackground;
class CTitleLogo;
// class CTitleMessage;

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
    CTitleBackground* m_pBackground;    // 배경

    CObject* m_pLogo;                   // 로고
    CObject* m_pMessage;                // 메시지

    CBtnUI* m_pStartButton;             // 시작 버튼
    CBtnUI* m_pHowToPlayButton;         // 조작법 버튼
    CBtnUI* m_pOptionButton;            // 옵션 버튼
    CBtnUI* m_pCreditButton;            // 크레딧 버튼
    CBtnUI* m_pExitButton;              // 종료 버튼

};
