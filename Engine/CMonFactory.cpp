#include "pch.h"
#include "CMonFactory.h"

#include "CMonster.h"
#include "AI.h"

#include "CIdleState.h"
#include "CTraceState.h"

CMonFactory::CMonFactory()
{
}

CMonFactory::~CMonFactory()
{
}
CMonster* CMonFactory::CreateMonster(MON_TYPE _eType,Vec2 _vPos)
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
        info.fHP = 50.f;
        info.fRecogRange = 3.f;
        info.fSpeed = 50.f;
        info.ePattern = MISSILE_PTRN::PTRN1;

        pMon->SetMonInfo(info);

        AI* pAI = new AI;
        pAI->AddState(new CIdleState);
        pAI->AddState(new CTraceState);
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
