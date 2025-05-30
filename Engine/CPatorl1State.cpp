#include "pch.h"
#include "CPatorl1State.h"

#include "MissileMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CMissile.h"

#include "CTimeMgr.h"
CPatorl1State::CPatorl1State()
    :CState(MON_STATE::PATROL1)
{
}

CPatorl1State::~CPatorl1State()
{
}
void CreateMissile(Vec2 vMonPos, Vec2 vMonScale);
void CPatorl1State::update()
{
    // 타겟팅 된 Player 를 쫒아간다.
    CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
    Vec2 vPlayerPos = pPlayer->GetPos();
    Vec2 vMonPos = GetMonster()->GetPos();
    Vec2 vMonScale = GetMonster()->GetScale();
    Vec2 vMonDir = vPlayerPos - vMonPos;
    vMonDir.Normalize();
    Vec2 vStraight = { -15,10 };
    vStraight.Normalize();
    vMonPos += vStraight * GetMonster()->GetInfo().fSpeed * 0.1f * fDT;
    m_fAdt += fDT;
    m_fSTimeAcc += fDT;
    if (m_fSTimeAcc >= 10.f)
    {
        m_fSTimeAcc = 0.f;
        ChangeAIState(GetAi(), MON_STATE::RUN);
    }
    if (m_fAdt > 1.f)
    {
        CreateMissile(vMonPos, vMonScale);
       
        //CreateMissile2(vMonPos, vMonScale);
       // CreateMissile3(vMonPos, vMonScale);
        m_fAdt = 0.f;

    }
    

    GetMonster()->SetPos(vMonPos);
   
}

void CPatorl1State::Enter()
{
}

void CPatorl1State::Exit()
{
    
}



