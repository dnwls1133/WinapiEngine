#include "pch.h"
#include "CScene_Title.h"

#include "CCore.h"
#include "CKeyMgr.h"
#include "CObject.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CScene.h"
#include "CSceneMgr.h"

#include "CSound.h"
#include "CSoundMgr.h"

#include "CResMgr.h"

#include "CTitleBackground.h"
#include "CTitleLogo.h"

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

    auto testBGM = CResMgr::GetInst()->LoadSound(L"Test BGM", L"content\\sound\\BGM_Test.mp3");
    if (!testBGM)
    {
        return;
    }

    CSoundMgr::GetInst()->PlayBGM(testBGM);
}

void CScene_Title::update()
{
    CScene::update();

    if (KEY_TAP(KEY::ENTER))
    {
        if (!m_pBackground)
            return;

        if (m_pBackground->IsPlayIntroAnimation())
        {
            m_pBackground->ChangeState();
            return;
        }
        else
        {
            ChangeScene(SCENE_TYPE::START);
        }
    }

    static CSound* testSE = CResMgr::GetInst()->LoadSound(L"Test SE", L"content\\sound\\SE_Test.mp3");
    if (KEY_TAP(KEY::SPACE))
        CSoundMgr::GetInst()->PlaySE(testSE);
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
