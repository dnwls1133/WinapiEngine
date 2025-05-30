#include "pch.h"
#include "CDeadState.h"

#include "CTimeMgr.h"
#include "CResMgr.h"

#include "CTexture.h"
#include "CObject.h"
#include "CMonster.h"
#include "CAnimation.h"
#include "CAnimator.h"
CDeadState::CDeadState()
    :CState(MON_STATE::DEAD)
{
}

CDeadState::~CDeadState()
{
}
void CDeadState::update()
{
    m_fAdt += fDT;
    if (m_fAdt > 1.0f)
    {
        m_fAdt = 0;
        Exit();
    }
}

void CDeadState::Enter()
{
    switch (GetMonster()->GetInfo().eMType)
    {
    case MON_TYPE::NORMAL1:
    {
        CTexture* m_pTex = CResMgr::GetInst()->LoadTexture(L"N1Enemy_Dead", L"texture\\Enemies\\normal1_enemy_Dead.png");
        GetMonster()->GetAnimator()->CreateAnimation(L"N1Enemy_Dead", m_pTex, Vec2(0.f, 0.f), Vec2(190.f, 190.f), Vec2(190.f, 0.f), 0.05f, 13);
        //Animation 저장
        GetMonster()->GetAnimator()->FindAnimation(L"N1Enemy_Dead")->Save(L"animation\\N1Enemy_Dead.anim");
        //GetMonster()->GetAnimator()->LoadAnimation(L"animation\\N1Enemy_Dead.anim");
        GetMonster()->GetAnimator()->Play(L"N1Enemy_Dead", false);
    }
    break;
    case MON_TYPE::NORMAL2:
    {
        GetMonster()->GetAnimator()->LoadAnimation(L"animation\\N2Enemy_Dead.anim");
        GetMonster()->GetAnimator()->Play(L"N2Enemy_Dead", false);
    }
    break;
    case MON_TYPE::NORMAL3:
    {
        GetMonster()->GetAnimator()->LoadAnimation(L"animation\\N3Enemy_Dead.anim");
        GetMonster()->GetAnimator()->Play(L"N3Enemy_Dead", false);
    }
    break;
    case MON_TYPE::NORMAL4:
    {
        GetMonster()->GetAnimator()->LoadAnimation(L"animation\\N4Enemy_Dead.anim");
        GetMonster()->GetAnimator()->Play(L"N4Enemy_Dead", false);
    }
    break;
    case MON_TYPE::RARE:
    {
        GetMonster()->GetAnimator()->LoadAnimation(L"animation\\Boss1Enemy_Dead.anim");
        GetMonster()->GetAnimator()->Play(L"Boss1Enemy_Dead", false);
    }
    break;
    case MON_TYPE::EPIC:
    {
        GetMonster()->GetAnimator()->LoadAnimation(L"animation\\E1Enemy_Dead.anim");
        GetMonster()->GetAnimator()->Play(L"E1Enemy_Dead", false);
    }
    break;
    case MON_TYPE::BOSS:
    {
         GetMonster()->GetAnimator()->LoadAnimation(L"animation\\N2Enemy_Dead.anim");
         GetMonster()->GetAnimator()->Play(L"N2Enemy_Dead", false);
    }
    }
}

void CDeadState::Exit()
{
    DeleteObject(GetMonster());
}



