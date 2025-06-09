#pragma once
#include "CScene.h"

class CSound;

class CScene_Stage01 :
    public CScene
{
private:
    vector<SpawnEvent> m_vEvents;
    bool               m_bClear;
    bool               m_bFail;
    float              m_fClearAcc;

    CSound* m_pStageTheme;          // 스테이지 메인테마.
    CSound* m_pBossTheme;           // 보스 테마.
    CSound* m_pStageClear;          // 스테이지 클리어 테마.
    CSound* m_pStageFail;           // 스테이지 페일 테마.

public:
    virtual void update();
    virtual void Enter();
    virtual void render(HDC _dc);
    virtual void Exit();

    void Clear() { m_bClear = true; }
    void Fail() { m_bFail = true; }
    void InitEvents();
public:
    CScene_Stage01();
    ~CScene_Stage01();
};

