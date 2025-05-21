#include "pch.h"
#include "CScene_Title.h"

CScene_Title::CScene_Title()
    : m_pBackground(nullptr)
    , m_pTitleLogo(nullptr)
    , m_pMessage(nullptr)
    , m_bIsIntro(false)
{
}

CScene_Title::~CScene_Title()
{
    m_pBackground.reset();
    m_pTitleLogo.reset();
    m_pMessage.reset();
}

void CScene_Title::Enter()
{
    POINT resolution = CCore::GetInst()->GetResolution();

    m_pBackground = std::make_unique<CTitleBackground>();
    m_pBackground->SetName(L"Background");
    m_pBackground->SetPos(Vec2(resolution.x / 2, resolution.y / 2));
    m_pBackground->SetScale(Vec2(100.0f, 100.0f));
    m_pBackground->GetAnimator()->CreateAnimation(
        TEXT("Intro"),
        CRes)
    AddObject(m_pBackground.get(), GROUP_TYPE::BACKGROUND);

    m_pTitleLogo = std::make_unique<CObject>();
    m_pTitleLogo->SetName(TEXT("Title Logo"));
    m_pTitleLogo->SetPos(Vec2(100.0f, 200.0f)); // 임시. 테스트 해볼 것.
    m_pTitleLogo->SetScale(Vec2(1.0f, 1.0f));   // 임시. 테스트 해볼 것.
    AddObject(m_pTitleLogo.get(), GROUP_TYPE::BACKGROUND);

    m_pMessage = std::make_unique<CObject>();
    m_pMessage->SetName(L"Message");
    m_pMessage->SetPos(Vec2(500.0f, 400.0f));   // 임시. 테스트 해볼 것.
    m_pMessage->SetScale(Vec2(1.0f, 1.0f));     // 임시. 테스트 해볼 것.
    AddObject(m_pMessage.get(), GROUP_TYPE::BACKGROUND);

    m_bIsIntro = false;
}

void CScene_Title::update()
{

}

void CScene_Title::Exit()
{
    m_pBackground.reset();
    m_pTitleLogo.reset();
    m_pMessage.reset();
}
