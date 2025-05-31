#pragma once
#include "CScene.h"
class CScene_Stage01 :
    public CScene
{
private:
    vector<SpawnEvent> m_vEvents;
public:
    virtual void update();
    virtual void Enter();
    virtual void render(HDC _dc);
    virtual void Exit();

    void InitEvents();
public:
    CScene_Stage01();
    ~CScene_Stage01();
};

