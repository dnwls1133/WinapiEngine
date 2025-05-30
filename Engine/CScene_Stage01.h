#pragma once
#include "CScene.h"
class CScene_Stage01 :
    public CScene
{
public:
    virtual void update();
    virtual void Enter();
    virtual void render(HDC _dc);
    virtual void Exit();
public:
    CScene_Stage01();
    ~CScene_Stage01();
};

