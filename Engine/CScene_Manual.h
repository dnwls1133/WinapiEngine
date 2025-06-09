#pragma once

#include "CScene.h"

class CSound;
class CMenuItem;

class CScene_Manual
    : public CScene
{
public:
    CScene_Manual();
    virtual ~CScene_Manual() override;

    virtual void Enter() override;
    virtual void update() override;
    virtual void Exit() override;

private:
    CSound* m_pTheme;
    CMenuItem* m_pBackButton;

};
