#pragma once

#include "CScene.h"

class CSound;
class CMenuItem;

class CScene_Ranking
    : public CScene
{
public:
    CScene_Ranking();
    virtual ~CScene_Ranking() override;

    virtual void Enter() override;
    virtual void update() override;
    virtual void Exit() override;

private:
    CSound* m_pTheme;
    CMenuItem* m_pBackButton;

};

