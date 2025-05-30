#include "pch.h"
#include "CMonFactory.h"

#include "CMonster.h"
#include "AI.h"

#include "CIdleState.h"
#include "CTraceState.h"
#include "CPatorl1State.h"
#include "CDeadState.h"
#include "CRunState.h"

CMonFactory::CMonFactory()
{
}

CMonFactory::~CMonFactory()
{
}
CMonster* CMonFactory::CreateMonster(MON_TYPE _eType,Vec2 _vPos,Vec2 _vDPos)
{

    CMonster* pMon = nullptr;
    switch (_eType)
    {
    case MON_TYPE::NORMAL1:
    {
        pMon = new CMonster;
        pMon->SetAnim(MON_TYPE::NORMAL1);

        pMon->SetPos(_vPos);



        tMonInfo info = {};
        info.fAtt = 1.f;
        info.fAttRange = 10.f;
        info.fHP = 30.f;
        info.fRecogRange = 3.f;
        info.fSpeed = 200.f;
        info.vDestPos = _vDPos;
        info.ePattern = MISSILE_PTRN::PTRN1;
        info.eMType = MON_TYPE::NORMAL1;
        pMon->SetMonInfo(info);

        AI* pAI = new AI;
        pAI->AddState(new CIdleState);
        pAI->AddState(new CPatorl1State);
        pAI->AddState(new CDeadState);
        pAI->AddState(new CRunState);
        pAI->SetCurState(MON_STATE::IDLE);
        pMon->SetAI(pAI);
    }
        break;
    case MON_TYPE::NORMAL2:
    {
        pMon = new CMonster;
        pMon->SetAnim(MON_TYPE::NORMAL2);

        pMon->SetPos(_vPos);



        tMonInfo info = {};
        info.fAtt = 1.f;
        info.fAttRange = 10.f;
        info.fHP = 30.f;
        info.fRecogRange = 3.f;
        info.fSpeed = 200.f;
        info.vDestPos = _vDPos;
        info.ePattern = MISSILE_PTRN::PTRN2;
        info.eMType = MON_TYPE::NORMAL2;
        pMon->SetMonInfo(info);

        AI* pAI = new AI;
        pAI->AddState(new CIdleState);
        pAI->AddState(new CPatorl1State);
        pAI->AddState(new CDeadState);
        pAI->AddState(new CRunState);
        pAI->SetCurState(MON_STATE::IDLE);
        pMon->SetAI(pAI);
    }
    break;
    case MON_TYPE::RARE:
    {

    }
        break;
    case MON_TYPE::EPIC:
    {

    }
        break;
    case MON_TYPE::BOSS:
    {

    }
        break;
    default:
        break;
    }

    assert(pMon);
    return pMon;
}
