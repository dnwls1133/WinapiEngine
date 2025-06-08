#pragma once
#include "CScene.h"
class CScene_Stage01 :
    public CScene
{
private:
    vector<SpawnEvent> m_vEvents;
    bool               m_bClear;
    bool               m_bFail;
    float              m_fClearAcc;
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

