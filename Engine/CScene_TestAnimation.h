#pragma once
#include "CScene.h"

class CScene_TestAnimation
	: public CScene
{
public:
    CScene_TestAnimation();
    ~CScene_TestAnimation();

    virtual void Enter() override;
    virtual void update() override;
    virtual void Exit() override;

public:
    CObject* m_pTestObject;

};

