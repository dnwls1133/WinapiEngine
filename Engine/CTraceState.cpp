#include "pch.h"
#include "CTraceState.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CMissile.h"

#include "CTimeMgr.h"
void CreateMissile(Vec2 vMonPos, Vec2 vMonScale);
void CreateMissile1(Vec2 vMonPos, Vec2 vMonScale);
void CreateMissile2(Vec2 vMonPos, Vec2 vMonScale);
void CreateMissile3(Vec2 vMonPos, Vec2 vMonScale);
CTraceState::CTraceState()
    :CState(MON_STATE::TRACE)
{
}

CTraceState::~CTraceState()
{
}
void CTraceState::update()
{
    // 타겟팅 된 Player 를 쫒아간다.
    CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
    Vec2 vPlayerPos = pPlayer->GetPos();
    Vec2 vMonPos = GetMonster()->GetPos();
    Vec2 vMonScale = GetMonster()->GetScale();
    Vec2 vMonDir = vPlayerPos - vMonPos;
    vMonDir.Normalize();
    Vec2 vStraight = { -10,10 };
    vStraight.Normalize();
    vMonPos += vStraight * GetMonster()->GetInfo().fSpeed* fDT;
    m_fAdt += fDT;
    if (m_fAdt > 0.02f)
    {
        CreateMissile(vMonPos, vMonScale);
        CreateMissile1(vMonPos, vMonScale);
        CreateMissile2(vMonPos, vMonScale);
        CreateMissile3(vMonPos, vMonScale);
        m_fAdt = 0.f;
      
    }
   
  
    //GetMonster()->SetPos(vMonPos);
}

void CTraceState::Enter()
{
}

void CTraceState::Exit()
{
}

void CreateMissile(Vec2 vMonPos,Vec2 vMonScale )
{
    Vec2 vMissilePos = vMonPos;
    vMissilePos.y += vMonScale.y / 2.f;
  
    CScene* CurScene = CSceneMgr::GetInst()->GetCurScene();
    CObject* pInfo = CurScene->GetPlayer();
    Vec2 vpPos = pInfo->GetPos();
    double dx = vMissilePos.x;
    double dy = vMissilePos.y;
    double distance = sqrt(dx * dx + dy * dy);
    if (vMissilePos.x - vpPos.x < 0)
    {
        vpPos.x = -(vMissilePos.x - vpPos.x);
    }
    else if (vMissilePos.x - vpPos.x > 0)
    {
        vpPos.x = -(vMissilePos.x - vpPos.x);
    }
    vpPos.y = vMissilePos.y - vpPos.y;
    vpPos.Normalize();
    // Missile Object
    CMissile* pMissile = new CMissile;
    pMissile->init(GROUP_TYPE::PROJ_MONSTER);
    pMissile->SetPos(vMissilePos);
    pMissile->SetScale(Vec2(25.f, 25.f));
    pMissile->SetDir(vpPos);
    pMissile->SetVec(300);
    pMissile->SetType(1);
    pMissile->SetName(L"MsMissile");

    CreateObject(pMissile, GROUP_TYPE::PROJ_MONSTER);
}

void CreateMissile1(Vec2 vMonPos, Vec2 vMonScale)
{
    Vec2 vMissilePos = vMonPos;
    vMissilePos.y += vMonScale.y / 2.f;

    CScene* CurScene = CSceneMgr::GetInst()->GetCurScene();
    CObject* pInfo = CurScene->GetPlayer();
    Vec2 vpPos = pInfo->GetPos();
    
    double dx = vMissilePos.x;
    double dy = vMissilePos.y;
    double distance = sqrt(dx * dx + dy * dy);
    if (vMissilePos.x - vpPos.x < 0)
    {
        vpPos.x = -(vMissilePos.x - vpPos.x);
    }
    else if (vMissilePos.x - vpPos.x > 0)
    {
        vpPos.x = -(vMissilePos.x - vpPos.x);
    }
    vpPos.y = vMissilePos.y - vpPos.y;
    vpPos.Normalize();
    vpPos.x *= -1;
    vpPos.y *= -1;
    // Missile Object
    CMissile* pMissile = new CMissile;
    pMissile->init(GROUP_TYPE::PROJ_MONSTER);
    pMissile->SetPos(vMissilePos);
    pMissile->SetScale(Vec2(25.f, 25.f));
    pMissile->SetDir(vpPos);
    pMissile->SetVec(300);
    pMissile->SetType(1);
    pMissile->SetName(L"MsMissile");

    CreateObject(pMissile, GROUP_TYPE::PROJ_MONSTER);
}

void CreateMissile2(Vec2 vMonPos, Vec2 vMonScale)
{
    Vec2 vMissilePos = vMonPos;
    vMissilePos.y += vMonScale.y / 2.f;

    CScene* CurScene = CSceneMgr::GetInst()->GetCurScene();
    CObject* pInfo = CurScene->GetPlayer();
    Vec2 vpPos = pInfo->GetPos();

    double dx = vMissilePos.x;
    double dy = vMissilePos.y;
    double distance = sqrt(dx * dx + dy * dy);
    if (vMissilePos.x - vpPos.x < 0)
    {
        vpPos.x = -(vMissilePos.x - vpPos.x);
    }
    else if (vMissilePos.x - vpPos.x > 0)
    {
        vpPos.x = -(vMissilePos.x - vpPos.x);
    }
    vpPos.y = vMissilePos.y - vpPos.y;
    vpPos.Normalize();
    vpPos.x *= -1;
 
    // Missile Object
    CMissile* pMissile = new CMissile;
    pMissile->init(GROUP_TYPE::PROJ_MONSTER);
    pMissile->SetPos(vMissilePos);
    pMissile->SetScale(Vec2(25.f, 25.f));
    pMissile->SetDir(vpPos);
    pMissile->SetVec(300);
    pMissile->SetType(1);
    pMissile->SetName(L"MsMissile");

    CreateObject(pMissile, GROUP_TYPE::PROJ_MONSTER);
}

void CreateMissile3(Vec2 vMonPos, Vec2 vMonScale)
{
    Vec2 vMissilePos = vMonPos;
    vMissilePos.y += vMonScale.y / 2.f;

    CScene* CurScene = CSceneMgr::GetInst()->GetCurScene();
    CObject* pInfo = CurScene->GetPlayer();
    Vec2 vpPos = pInfo->GetPos();

    double dx = vMissilePos.x;
    double dy = vMissilePos.y;
    double distance = sqrt(dx * dx + dy * dy);
    if (vMissilePos.x - vpPos.x < 0)
    {
        vpPos.x = -(vMissilePos.x - vpPos.x);
    }
    else if (vMissilePos.x - vpPos.x > 0)
    {
        vpPos.x = -(vMissilePos.x - vpPos.x);
    }
    vpPos.y = vMissilePos.y - vpPos.y;
    vpPos.Normalize();
  
    vpPos.y *= -1;
    // Missile Object
    CMissile* pMissile = new CMissile;
    pMissile->init(GROUP_TYPE::PROJ_MONSTER);
    pMissile->SetPos(vMissilePos);
    pMissile->SetScale(Vec2(25.f, 25.f));
    pMissile->SetDir(vpPos);
    pMissile->SetVec(300);
    pMissile->SetType(1);
    pMissile->SetName(L"MsMissile");

    CreateObject(pMissile, GROUP_TYPE::PROJ_MONSTER);
}
