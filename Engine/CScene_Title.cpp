#include "pch.h"
#include "CScene_Title.h"

#include "CCamera.h"
#include "CCore.h"
#include "CKeyMgr.h"
#include "CObject.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CScene.h"
#include "CSceneMgr.h"

#include "CResMgr.h"

#include "CBtnUI.h"
#include "CMenuItem.h"

#include "CTitleBackground.h"
#include "CTitleLogo.h"
// #include "CTitleMessage.h"

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
    // CCamera::GetInst()->SetLookAt(vResolution / 2.f);

    m_pBackground = new CTitleBackground();
    m_pBackground->SetPos(Vec2(vResolution.x / 2, vResolution.y / 2));
    m_pBackground->SetScale(Vec2(1, 1));
    m_pBackground->SetName(L"Background");
    AddObject(m_pBackground, GROUP_TYPE::BACKGROUND);

    m_pStartButton = new CMenuItem(
        CResMgr::GetInst()->LoadTexture(L"Start_Game_Idle", L"texture\\Sprites\\GUI\\Menu Items\\Labels\\Start Game\\Sprite_Label_StartGame_0.bmp"),
        CResMgr::GetInst()->LoadTexture(L"Start_Game_Hover", L"texture\\Sprites\\GUI\\Menu Items\\Labels\\Start Game\\Sprite_Label_StartGame_1.bmp")
    );
    m_pStartButton->SetPos(Vec2(vResolution.x / 2, vResolution.y * 0.75f));
    m_pStartButton->SetScale(Vec2(300.0f, 100.f));
    m_pStartButton->SetClickedCallBack(
        [](DWORD_PTR, DWORD_PTR) {
            ChangeScene(SCENE_TYPE::TOOL);
        },
        (DWORD_PTR)0, (DWORD_PTR)0
    );
    AddObject(m_pStartButton, GROUP_TYPE::UI);
}

void CScene_Title::update()
{
    CScene::update();

}

void CScene_Title::Exit()
{

}
