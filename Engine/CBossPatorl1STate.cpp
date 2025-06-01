#include "pch.h"
#include "CBossPatorl1STate.h"

#include "time.h"
#include "MissileMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CMissile.h"

#include "CCore.h"




#include "CAnimator.h"
#include "CAnimation.h"


#include "CTimeMgr.h"
CBossPatorl1STate::CBossPatorl1STate()
    :CState(MON_STATE::MBOSS0)
    ,m_fXdir(2*PI)
    ,m_fMTimeAcc(0.f)
    ,m_fFlip(1.f)
    ,m_pDesPos{}
    ,m_iDestType(0)
{
    
}

CBossPatorl1STate::~CBossPatorl1STate()
{
   
}
void CBossPatorl1STate::update()
{
    srand(time(NULL));
    Vec2 vResolution = CCore::GetInst()->GetResolution();
    Vec2 vBackPos = CSceneMgr::GetInst()->GetCurScene()->GetBackground()->GetPos();
    Vec2 vBackScale = CSceneMgr::GetInst()->GetCurScene()->GetBackground()->GetScale();
    RECT rBackrect = { (vBackPos.x - vBackScale.x / 2.f),(vBackPos.y - vBackScale.y / 2.f),(vBackPos.x + vBackScale.x / 2.f),(vBackPos.x + vBackScale.y / 2.f) };
    Vec2 vMonPos = GetMonster()->GetPos();
    Vec2 vMonScale = GetMonster()->GetScale();
    Vec2 vDestPos = GetMonster()->GetInfo().vDestPos;
    Vec2 vDir = vDestPos - vMonPos;
    vDir.Normalize();
    
    Vec2 vDiff = vDestPos - vMonPos;
    float fLen = vDiff.Length();
    if (fLen < GetMonster()->GetInfo().fRecogRange)
    {
        GetMonster()->SetDestPos(m_pDesPos[m_iDestType++]);
        if (m_iDestType > 2)
        {
            m_iDestType = 0;
        }
    }
    vMonPos += vDir * GetMonster()->GetInfo().fSpeed * 0.5f * fDT;

    m_fAdt += fDT;
    m_fSTimeAcc += fDT;
    m_fMTimeAcc += fDT;
    if (GetMonster()->GetInfo().fHP <= 30)
    {
        m_fSTimeAcc = 0.f;
        ChangeAIState(GetAi(), MON_STATE::RUN);
    }
    switch (GetMonster()->GetInfo().ePattern)
    {
    case MISSILE_PTRN::PTRN1:
    {

        if (m_fMTimeAcc > 2.f)
        {
            if (m_fAdt > 0.1f)
            {
                CreateStraightMissile(Vec2(vMonPos.x - vMonScale.x/2.f,vMonPos.y), vMonScale, MISSILE_TYPE::SMALL);
                CreateStraightMissile(Vec2(vMonPos.x + vMonScale.x / 2.f, vMonPos.y), vMonScale, MISSILE_TYPE::SMALL);
                m_fAdt = 0.f;
            }
            if (m_fMTimeAcc > 2.5f)
            {
                GetMonster()->SetMissiletype(MISSILE_PTRN::PTRN2);
                m_fMTimeAcc = 0.f;
            }
        }

    }
    break;
    case MISSILE_PTRN::PTRN2:
    {
        if (m_fAdt> 0.5f)
        {
            CreateMissile1(vMonPos, vMonScale, MISSILE_TYPE::SMALL);
            CreateMissile2(vMonPos, vMonScale, MISSILE_TYPE::SMALL);
            if (m_fAdt > 1.f + fDT)
            {
                CreateMissile1(vMonPos, vMonScale, MISSILE_TYPE::SMALL);
                CreateMissile2(vMonPos, vMonScale, MISSILE_TYPE::SMALL);
                m_fAdt = 0.f;
            }

        }
        if (m_fMTimeAcc > 2.f)
        {
            CreateMissile4(vMonPos, vMonScale, MISSILE_TYPE::SPIN);
            GetMonster()->SetMissiletype(MISSILE_PTRN::PTRN1);
            m_fMTimeAcc = 0.f;
        }
    }
    break;
    case MISSILE_PTRN::PTRN3:
    {

    }
    break;
    }



    GetMonster()->SetPos(vMonPos);
}

void CBossPatorl1STate::Enter()
{
    Vec2 vResolution = CCore::GetInst()->GetResolution();
    Vec2 vBackPos = CSceneMgr::GetInst()->GetCurScene()->GetBackground()->GetPos();
    Vec2 vBackScale = CSceneMgr::GetInst()->GetCurScene()->GetBackground()->GetScale();
    RECT rBackrect = { (vBackPos.x - vBackScale.x / 2.f),(vBackPos.y - vBackScale.y / 2.f),(vBackPos.x + vBackScale.x / 2.f),(vBackPos.x + vBackScale.y / 2.f) };
    m_pDesPos[0] = Vec2(vBackPos.x + 100.f, vBackPos.y - 200.f);
    m_pDesPos[1] = Vec2(vBackPos.x - 100.f, vBackPos.y - 200.f);
    m_pDesPos[2] = Vec2((float)vBackPos.x, (float)rBackrect.bottom / 2.f - 300.f);
}

void CBossPatorl1STate::Exit()
{
}


