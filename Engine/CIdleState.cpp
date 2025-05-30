#include "pch.h"
#include "CIdleState.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "CTimeMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
CIdleState::CIdleState()
    :CState(MON_STATE::IDLE)
{
}

CIdleState::~CIdleState()
{
}


void CIdleState::update()
{
    // 가만히 있는다.
    CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();

    // Player 의 위치 체크
    Vec2 vPlayerPos = pPlayer->GetPos();

    // 몬스터의 범위 안에 들어오면 추적 상태로 전환
    CMonster* pMonster = GetMonster();
    Vec2 vMonPos = pMonster->GetPos();
    Vec2 vDestPos = Vec2(600.f, 150.f);
    Vec2 vDir = vDestPos - vMonPos;
    vDir.Normalize();

   

    Vec2 vDiff = vDestPos - vMonPos;
    float fLen = vDiff.Length();

    // 플레이어가 몬스터의 인식범위 안으로 진입
    if (fLen < pMonster->GetInfo().fRecogRange)
    {
        ChangeAIState(GetAi(), MON_STATE::TRACE);
    }
    vMonPos += vDir * GetMonster()->GetInfo().fSpeed * fDT;
    GetMonster()->SetPos(vMonPos);

}

void CIdleState::Enter()
{
}

void CIdleState::Exit()
{
}
