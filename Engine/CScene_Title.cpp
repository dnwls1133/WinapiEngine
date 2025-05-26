#include "pch.h"
#include "CScene_Title.h"

#include "CCore.h"
#include "CKeyMgr.h"
#include "CObject.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CScene.h"
#include "CSceneMgr.h"

#include "CTitleBackground.h"

CScene_Title::CScene_Title()
    : m_pBackground(nullptr)
    , m_pLogo(nullptr)
    // , m_pMessage(nullptr)
{
}

CScene_Title::~CScene_Title()
{

}

void CScene_Title::Enter()
{
    const Vec2 vResolution = CCore::GetInst()->GetResolution();

    m_pBackground = new CTitleBackground();
    m_pBackground->SetPos(Vec2(vResolution.x / 2, vResolution.y / 2));
    m_pBackground->SetScale(Vec2(1, 1));
    m_pBackground->SetName(L"Background");
    AddObject(m_pBackground, GROUP_TYPE::BACKGROUND);
}

void CScene_Title::update()
{
    CScene::update();

}

void CScene_Title::Exit()
{
    if (nullptr != m_pBackground)
        delete m_pBackground;

    if (nullptr != m_pLogo)
        delete m_pLogo;

    // if (nullptr != m_pMessage)
    //     delete m_pMessage;
}
