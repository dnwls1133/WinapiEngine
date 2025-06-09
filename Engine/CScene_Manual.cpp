#include "pch.h"
#include "CScene_Manual.h"
#include "CCore.h"
#include "CRankMgr.h"
#include "CMenuItem.h";
#include "CTexture.h"
#include "CSound.h"
#include "CSoundMgr.h"
#include "CResMgr.h"
#include "CColliderMgr.h"

CScene_Manual::CScene_Manual()
{

}

CScene_Manual::~CScene_Manual()
{

}

void CScene_Manual::Enter()
{
    m_pBackButton = new CMenuItem(
        CResMgr::GetInst()->LoadTexture(L"Back Idle", L"texture\\Menu Items\\Go Back\\Sprite_Label_GoBack_0.png"),
        CResMgr::GetInst()->LoadTexture(L"Back Hover", L"texture\\Menu Items\\Go Back\\Sprite_Label_GoBack_1.png")
    );
    m_pBackButton->SetPos(Vec2(290.0f, 760.0f));
    m_pBackButton->SetScale(Vec2(210.0f, 70.0f));
    m_pBackButton->SetClickedCallBack(
        [](DWORD_PTR, DWORD_PTR) {
            ChangeScene(SCENE_TYPE::TITLE);
        },
        (DWORD_PTR)0, (DWORD_PTR)0
    );
    AddObject(m_pBackButton, GROUP_TYPE::UI);

    m_pTheme = CResMgr::GetInst()->LoadSound(L"Menu Theme", L"sound\\BGM\\BGM_MenuTheme.mp3");
    CSoundMgr::GetInst()->PlayBGM(m_pTheme, true);
}

void CScene_Manual::update()
{
    const wchar_t* const test = L"Not Yet!!";
    TextOut(CCore::GetInst()->GetMainDC(), 50, 50, test, sizeof(test));
}

void CScene_Manual::Exit()
{
    DeleteAll();
    CColliderMgr::GetInst()->Reset();
}
