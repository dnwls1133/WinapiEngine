#include "pch.h"
#include "MissileMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CMissile.h"

#include "CTimeMgr.h"

void CreateMissile(Vec2 vMonPos, Vec2 vMonScale)
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
    pMissile->SetScale(Vec2(20.f, 20.f));
    pMissile->SetDir(vpPos);
    pMissile->SetVec(500);
    pMissile->SetType(1);
    pMissile->SetName(L"MsMissile");

    CreateObject(pMissile, GROUP_TYPE::PROJ_MONSTER);
}

