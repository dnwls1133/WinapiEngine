#pragma once

#include "CScene.h"
class CScene;
class CSceneMgr;

class CTitleBackground;
class CTitleLogo;
// class CTitleMessage;

class CSound;

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
    CTitleBackground* m_pBackground;

    CTitleLogo* m_pLogo;

    // CTitleMessage* m_pMessage;
    // CSound* m_pTheme;
};
