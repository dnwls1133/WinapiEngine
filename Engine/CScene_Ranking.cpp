#include "pch.h"
#include "CScene_Ranking.h"
#include "CCore.h"
#include "CRankMgr.h"
#include "CMenuItem.h";
#include "CTexture.h"
#include "CSound.h"
#include "CSoundMgr.h"
#include "CResMgr.h"
#include "CColliderMgr.h"

CScene_Ranking::CScene_Ranking()
{
}

CScene_Ranking::~CScene_Ranking()
{

}

void CScene_Ranking::Enter()
{
    // CRankMgr::GetInst()->LoadRanking();
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

    m_pTheme = CResMgr::GetInst()->LoadSound(L"Ranking Scene Theme", L"sound\\BGM\\BGM_MenuTheme.mp3");
    CSoundMgr::GetInst()->PlayBGM(m_pTheme, true);
}

void CScene_Ranking::update()
{
    int lineHeight = 20; // 줄 간격
    int y = 50;

    std::wstring title = L"=== 랭킹 ===";
    TextOut(CCore::GetInst()->GetMainDC(), 50, y, title.c_str(), (int)title.length());
    y += lineHeight;

    for (size_t i = 0; i < 5; ++i) {
        const RankingData& rec = CRankMgr::GetInst()->GetRanking(i);

        std::wstring line = std::to_wstring(i + 1) + L"위: 점수 " + std::to_wstring(rec.Score) + L", 날짜: " + rec.DateTime;
        TextOut(CCore::GetInst()->GetMainDC(), 50, y, line.c_str(), (int)line.length());
        y += lineHeight;
    }
}

void CScene_Ranking::Exit()
{
    DeleteAll();
    CColliderMgr::GetInst()->Reset();
}
