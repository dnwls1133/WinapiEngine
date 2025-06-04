#include "pch.h"
#include "CScene_Stage01.h"
#include "CObject.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CBackground.h"

#include "CCore.h"

#include "CColliderMgr.h"
#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CTimeMgr.h"

#include "CTexture.h"
#include "CCamera.h"

#include "SelectGDI.h"

#include "AI.h"
#include "CState.h"
#include "CIdleState.h"
#include "CTraceState.h"
CScene_Stage01::CScene_Stage01()
    :m_bClear(false)
    ,m_fClearAcc(0.f)
{
}

CScene_Stage01::~CScene_Stage01()
{
}

void CScene_Stage01::update()
{
    CScene::update();
   


    m_dAcc += fDT;
   

    if (m_bClear)
    {
        if (m_fClearAcc == 0.f)
        {
            CCamera::GetInst()->FadeOut(3.f);
        }
        m_fClearAcc += fDT;
        if (m_fClearAcc > 3.f)
        {
           
            ChangeScene(SCENE_TYPE::TITLE);
            m_fClearAcc = 0;
        }
    }
    for (auto& evt : m_vEvents)
    {
        if (!evt.triggered && m_dAcc >= evt.triggerTime)
        {
            CMonster* pMon = CMonFactory::CreateMonster(evt.type,evt.mtype,evt.spawnPos,evt.targetPos,evt.exitPos );
            pMon->SetName(L"Monster");
            AddObject(pMon, GROUP_TYPE::MONSTER);
            evt.triggered = true;
        }
    }


}
void CScene_Stage01::render(HDC _dc)
{
    CScene::render(_dc);
    CBackground* back = (CBackground*)GetBackground();
    Vec2 backinfo = back->GetScale();
    Vec2 backPos = back->GetPos();
    POINT resolution = CCore::GetInst()->GetResolution();
    SelectGDI gdi(_dc, BRUSH_TYPE::BLACK);
    Rectangle(_dc, 0, 0
        , (int)(backPos.x - backinfo.x / 2)
        , (int)(backPos.y + backinfo.y / 2));
    Rectangle(_dc
        , (int)(backPos.x + backinfo.x / 2)
        , 0
        , (int)resolution.x
        , (int)resolution.y);
}
void CScene_Stage01::Enter()
{
    Vec2 vResolution = CCore::GetInst()->GetResolution();


    // BackGround Object 추가
    CObject* pBackgroundObj = new CBackground;
    pBackgroundObj->SetPos(Vec2(vResolution.x / 2.f, vResolution.y / 2.f));
    pBackgroundObj->SetScale(Vec2(540.f, 960.f));
    pBackgroundObj->SetName(L"Background");
    AddObject(pBackgroundObj, GROUP_TYPE::BACKGROUND);

    RegisterBackground(pBackgroundObj);

    // Player Object 추가
    CObject* pObj = new CPlayer;
    pObj->SetPos(Vec2(vResolution.x /2.f, vResolution.y + 200.f));
    pObj->SetScale(Vec2(100.f, 100.f));
    pObj->SetName(L"Player");
    AddObject(pObj, GROUP_TYPE::PLAYER);

    RegisterPlayer(pObj);


    // Monster Object 추가
   
    InitEvents();
    

    // 타일 로딩
    //LoadTile(L"Tile\\Start.tile");


    // 충돌 지정
    // Player 그룹과 Monster 그룹간의 충돌체크
    CColliderMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PROJ_MONSTER);
    CColliderMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
    CColliderMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::ITEM);
   
    //Camera 지정

    CCamera::GetInst()->SetLookAt(vResolution / 2.f);

    CCamera::GetInst()->FadeOut(1.5f);
    CCamera::GetInst()->FadeIn(1.5f);
    m_dAcc = 0.f;
    //Camera 효과 지정
   // CCamera::GetInst()->Fadeout(5.f);
}



void CScene_Stage01::Exit()
{
    DeleteAll();
    m_dAcc = 0;
    m_bClear = false;
    m_fClearAcc = 0.f;
    m_vEvents.clear();
    CColliderMgr::GetInst()->Reset();
}

void CScene_Stage01::InitEvents()
{
    Vec2 vResolution = CCore::GetInst()->GetResolution();
    Vec2 vBackPos = GetBackground()->GetPos();
    Vec2 vBackScale = GetBackground()->GetScale();
    RECT rBackrect = { (vBackPos.x - vBackScale.x / 2.f),(vBackPos.y - vBackScale.y / 2.f),(vBackPos.x + vBackScale.x / 2.f),(vBackPos.x + vBackScale.y / 2.f) };


    for (int i = 0; i < 25; ++i)
    {
        if (i % 2 == 0)
        {
            m_vEvents.push_back({ 5.0f * i,MON_TYPE::NORMAL3,MISSILE_PTRN::NONE, Vec2((float)rBackrect.left + 200.f, -100.f),Vec2((float)rBackrect.left + 200.f,(float)rBackrect.top + 200.f),Vec2((float)rBackrect.right + 400.f,vResolution.y) });
            m_vEvents.push_back({ (5.0f * i) + 0.5f,MON_TYPE::NORMAL4,MISSILE_PTRN::NONE, Vec2((float)rBackrect.left + 150.f, -100.f),Vec2((float)rBackrect.left + 150.f,(float)rBackrect.top + 150.f),Vec2((float)rBackrect.right + 400.f,vResolution.y) });
            m_vEvents.push_back({ (5.0f * i) + 1.f,MON_TYPE::NORMAL4, MISSILE_PTRN::NONE,Vec2((float)rBackrect.left + 100.f, -100.f),Vec2((float)rBackrect.left + 100.f,(float)rBackrect.top + 100.f),Vec2((float)rBackrect.right + 400.f,vResolution.y) });

        }
        else
        {
            m_vEvents.push_back({ 5.0f * i,MON_TYPE::NORMAL3,MISSILE_PTRN::NONE, Vec2((float)rBackrect.right - 200.f , -100.f),Vec2((float)rBackrect.right - 200.f,(float)rBackrect.top + 200.f),Vec2((float)rBackrect.left - 400.f,vResolution.y) });
            m_vEvents.push_back({ (5.0f * i) + 0.5f,MON_TYPE::NORMAL4,MISSILE_PTRN::NONE, Vec2((float)rBackrect.right - 150.f , -100.f),Vec2((float)rBackrect.right - 150.f,(float)rBackrect.top + 150.f),Vec2((float)rBackrect.left - 400.f,vResolution.y) });
            m_vEvents.push_back({ (5.0f * i) + 1.f,MON_TYPE::NORMAL4, MISSILE_PTRN::NONE,Vec2((float)rBackrect.right - 100.f , -100.f),Vec2((float)rBackrect.right - 100.f,(float)rBackrect.top + 100.f),Vec2((float)rBackrect.left - 400.f,vResolution.y) });
        }
        
    }
   
  
    // PTRN 2
    {
        for (int i = 0; i < 10; ++i)
        {
            if (i % 2 == 0)
            {
                m_vEvents.push_back({ 8.0f+0.2f*i,MON_TYPE::NORMAL2, MISSILE_PTRN::PTRN1,Vec2((float)rBackrect.left + 200.f , -100.f),Vec2((float)rBackrect.left + 200.f,(float)rBackrect.top + 500.f - 30.f*i),Vec2((float)rBackrect.right + 400.f,vResolution.y) });
            }
            else
            {
                m_vEvents.push_back({ 8.0f+0.2f*i,MON_TYPE::NORMAL2, MISSILE_PTRN::PTRN1,Vec2((float)rBackrect.left + 250.f , -100.f),Vec2((float)rBackrect.left + 150.f,(float)rBackrect.top + 500.f - 30.f*i),Vec2((float)rBackrect.right + 400.f,vResolution.y) });
            }
        }
        for (int i = 0; i < 10; ++i)
        {
            if (i % 2 == 0)
            {
                m_vEvents.push_back({ 13.0f + 0.2f * i,MON_TYPE::NORMAL2,MISSILE_PTRN::PTRN1, Vec2((float)rBackrect.right - 200.f , -100.f),Vec2((float)rBackrect.right - 200.f,(float)rBackrect.top + 500.f - 30.f * i),Vec2((float)rBackrect.left - 400.f,vResolution.y) });
            }
            else
            {
                m_vEvents.push_back({ 13.0f + 0.2f * i,MON_TYPE::NORMAL2, MISSILE_PTRN::PTRN1,Vec2((float)rBackrect.right - 250.f , -100.f),Vec2((float)rBackrect.right - 150.f,(float)rBackrect.top + 500.f - 30.f * i),Vec2((float)rBackrect.left - 400.f,vResolution.y) });
            }
        }
       
      
    }

    // PTRN 3
    {
        for (int i = 0; i < 10; ++i)
        {
            m_vEvents.push_back({ 15.0f + 0.4f*i,MON_TYPE::NORMAL5,MISSILE_PTRN::NONE, Vec2((float)rBackrect.left - 250.f,(float)rBackrect.bottom / 2.f),Vec2(vBackPos.x,(float)rBackrect.top + 150.f),Vec2((float)rBackrect.right + 250.f,(float)rBackrect.bottom / 2.f) });

        }
        for (int i = 0; i < 10; ++i)
        {
            m_vEvents.push_back({ 18.0f + 0.4f * i,MON_TYPE::NORMAL5,MISSILE_PTRN::NONE,Vec2((float)rBackrect.right + 250.f, (float)rBackrect.bottom / 2.f),Vec2(vBackPos.x,(float)rBackrect.top + 250.f),Vec2((float)rBackrect.left - 250.f, (float)rBackrect.bottom / 2.f) });

        }

    }


    // PTRN 3
    {
        m_vEvents.push_back({ 20.0f,MON_TYPE::NORMAL1,MISSILE_PTRN::PTRN1, Vec2((float)rBackrect.left - 200.f,  (float)rBackrect.top + 250.f),Vec2((float)rBackrect.left + 200.f, (float)rBackrect.top + 200.f),Vec2((float)rBackrect.left + 100.f, -400.f) });
        m_vEvents.push_back({ 25.0f,MON_TYPE::NORMAL1,MISSILE_PTRN::PTRN1,Vec2((float)rBackrect.right + 200.f, (float)rBackrect.top + 250.f),Vec2((float)rBackrect.right - 200.f,(float)rBackrect.top + 200.f),Vec2((float)rBackrect.right - 100.f, -400.f) });

    }
  
    for (int i = 0; i < 4; ++i)
    {
        if (i % 2 == 0)
        {
            m_vEvents.push_back({ 35.0f + 0.2f * i,MON_TYPE::NORMAL2,MISSILE_PTRN::PTRN2,Vec2((float)rBackrect.right - 200.f , -100.f),Vec2((float)rBackrect.right - 200.f,(float)rBackrect.top + 300.f - 50.f * i),Vec2((float)rBackrect.right + 400.f,vResolution.y/2.f) });
        }
        else
        {
            m_vEvents.push_back({ 35.0f + 0.2f * i,MON_TYPE::NORMAL2,MISSILE_PTRN::PTRN2,Vec2((float)rBackrect.right - 250.f , -100.f),Vec2((float)rBackrect.right - 150.f,(float)rBackrect.top + 300.f - 50.f * i),Vec2((float)rBackrect.right + 400.f,vResolution.y/2.f) });
        }
    }

    for (int i = 0; i < 4; ++i)
    {
        if (i % 2 == 0)
        {
            m_vEvents.push_back({ 35.5f + 0.2f * i,MON_TYPE::NORMAL2,MISSILE_PTRN::PTRN2,Vec2((float)rBackrect.left + 200.f , -100.f),Vec2((float)rBackrect.left + 200.f,(float)rBackrect.top + 300.f - 50.f * i),Vec2((float)rBackrect.left - 400.f,vResolution.y / 2.f) });
        }
        else
        {
            m_vEvents.push_back({ 36.0f + 0.2f * i,MON_TYPE::NORMAL2,MISSILE_PTRN::PTRN2,Vec2((float)rBackrect.left + 250.f , -100.f),Vec2((float)rBackrect.left + 150.f,(float)rBackrect.top + 300.f - 50.f * i),Vec2((float)rBackrect.left - 400.f,vResolution.y / 2.f) });
        }
    }



    for (int i = 0; i < 10; ++i)
    {
        m_vEvents.push_back({ 35.0f + 0.4f * i,MON_TYPE::NORMAL5,MISSILE_PTRN::NONE, Vec2((float)rBackrect.left - 250.f, (float)rBackrect.top - 100.f),Vec2(vBackPos.x + 200.f,(float)rBackrect.bottom/2.f),Vec2((float)rBackrect.left - 250.f, (float)rBackrect.bottom + 100.f) });

    }
    for (int i = 0; i < 10; ++i)
    {
        m_vEvents.push_back({ 40.0f + 0.4f * i,MON_TYPE::NORMAL5,MISSILE_PTRN::NONE,Vec2((float)rBackrect.right + 250.f, (float)rBackrect.top - 100.f),Vec2(vBackPos.x - 200.f,(float)rBackrect.bottom / 2.f),Vec2((float)rBackrect.right + 250.f, (float)rBackrect.bottom + 100.f) });
    }
    for (int i = 0; i < 4; ++i)
    {
        m_vEvents.push_back({ 45.0f + 0.4f * i,MON_TYPE::NORMAL2,MISSILE_PTRN::PTRN2, Vec2((float)rBackrect.left - 250.f, (float)rBackrect.bottom/2.f),Vec2(vBackPos.x,(float)rBackrect.bottom / 2.f - 50.f),Vec2((float)rBackrect.right + 250.f, (float)rBackrect.bottom/2.f) });

    }
    for (int i = 0; i < 4; ++i)
    {
        m_vEvents.push_back({ 47.5f + 0.4f * i,MON_TYPE::NORMAL2,MISSILE_PTRN::PTRN2, Vec2((float)rBackrect.right + 250.f, (float)rBackrect.bottom / 2.f-100.f),Vec2(vBackPos.x,(float)rBackrect.bottom / 2.f - 150.f),Vec2((float)rBackrect.left - 250.f, (float)rBackrect.bottom / 2.f - 100.f) });

    }
    for (int i = 0; i < 4; ++i)
    {
        m_vEvents.push_back({ 50.0f + 0.4f * i,MON_TYPE::NORMAL2,MISSILE_PTRN::PTRN2, Vec2((float)rBackrect.left - 250.f, (float)rBackrect.bottom / 2.f-300.f),Vec2(vBackPos.x,(float)rBackrect.bottom / 2.f - 350.f),Vec2((float)rBackrect.right + 250.f, (float)rBackrect.bottom / 2.f - 300.f)  });

    }
    for (int i = 0; i < 4; ++i)
    {
        m_vEvents.push_back({ 52.5f + 0.4f * i,MON_TYPE::NORMAL2,MISSILE_PTRN::PTRN2, Vec2((float)rBackrect.right + 250.f, (float)rBackrect.bottom / 2.f- 500.f),Vec2(vBackPos.x,(float)rBackrect.bottom / 2.f -550.f),Vec2((float)rBackrect.left - 250.f, (float)rBackrect.bottom / 2.f- 500.f) });

    }
    for (int i = 0; i < 10; ++i)
    {
        m_vEvents.push_back({ 55.0f + 0.4f * i,MON_TYPE::NORMAL5,MISSILE_PTRN::NONE, Vec2((float)rBackrect.left - 250.f, (float)rBackrect.top - 100.f),Vec2(vBackPos.x + 200.f,(float)rBackrect.bottom / 2.f),Vec2((float)rBackrect.left - 250.f, (float)rBackrect.bottom + 100.f) });

    }
    for (int i = 0; i < 10; ++i)
    {
        m_vEvents.push_back({ 57.5f + 0.4f * i,MON_TYPE::NORMAL5,MISSILE_PTRN::NONE,Vec2((float)rBackrect.right + 250.f, (float)rBackrect.top - 100.f),Vec2(vBackPos.x - 200.f,(float)rBackrect.bottom / 2.f),Vec2((float)rBackrect.right + 250.f, (float)rBackrect.bottom + 100.f) });
    }

    // PTRN 3
    {
        m_vEvents.push_back({ 60.0f,MON_TYPE::EPIC,MISSILE_PTRN::PTRN1, Vec2(vBackPos.x,  (float)rBackrect.top - 200.f),Vec2((float)vBackPos.x, (float)rBackrect.bottom/2.f-300.f),Vec2((float)vBackPos.x, -400.f) });
    }

    // PTRN 4
    {
        m_vEvents.push_back({ 80.0f,MON_TYPE::EPIC2,MISSILE_PTRN::PTRN1, Vec2((float)rBackrect.left + 150.f,  (float)rBackrect.top - 200.f),Vec2((float)rBackrect.left + 230.f, (float)rBackrect.bottom / 2.f - 250.f),Vec2((float)rBackrect.left + 100.f, -400.f) });
        m_vEvents.push_back({ 80.5f,MON_TYPE::EPIC2,MISSILE_PTRN::PTRN1, Vec2((float)rBackrect.right - 150.f,  (float)rBackrect.top - 200.f),Vec2((float)rBackrect.right - 180.f, (float)rBackrect.bottom / 2.f - 300.f),Vec2((float)rBackrect.right - 100.f, -400.f) });
    }

    for (int i = 0; i < 10; ++i)
    {
        m_vEvents.push_back({ 90.0f + 0.4f * i,MON_TYPE::NORMAL2,MISSILE_PTRN::PTRN3, Vec2((float)rBackrect.left + 300.f, (float)rBackrect.top - 100.f),Vec2((float)rBackrect.left + 100.f,(float)rBackrect.top + 150.f),Vec2((float)rBackrect.right + 250.f, (float)rBackrect.bottom + 100.f) });

    }
    for (int i = 0; i < 10; ++i)
    {
        m_vEvents.push_back({ 95.5f + 0.4f * i,MON_TYPE::NORMAL2,MISSILE_PTRN::PTRN3,Vec2((float)rBackrect.right - 300.f, (float)rBackrect.top - 100.f),Vec2((float)rBackrect.right - 100.f,(float)rBackrect.top + 150.f),Vec2((float)rBackrect.left - 250.f, (float)rBackrect.bottom + 100.f) });
    }

    for (int i = 0; i < 10; ++i)
    {
        m_vEvents.push_back({ 105.0f + 0.4f * i,MON_TYPE::NORMAL2,MISSILE_PTRN::PTRN3,Vec2((float)rBackrect.right - 300.f, (float)rBackrect.top - 100.f),Vec2((float)rBackrect.right - 100.f,(float)rBackrect.top + 150.f),Vec2((float)rBackrect.left - 250.f, (float)rBackrect.bottom + 100.f) });


    }
    for (int i = 0; i < 10; ++i)
    {
        m_vEvents.push_back({ 110.0f + 0.4f * i,MON_TYPE::NORMAL2,MISSILE_PTRN::PTRN3, Vec2((float)rBackrect.left + 300.f, (float)rBackrect.top - 100.f),Vec2((float)rBackrect.left + 100.f,(float)rBackrect.top + 150.f),Vec2((float)rBackrect.right + 250.f, (float)rBackrect.bottom + 100.f) });
    }
    m_vEvents.push_back({ 100.0f,MON_TYPE::NORMAL1,MISSILE_PTRN::PTRN2, Vec2((float)rBackrect.left + 100.f,  (float)rBackrect.top - 200.f),Vec2((float)rBackrect.left + 150.f, (float)rBackrect.top + 200.f),Vec2((float)rBackrect.right + 400.f, -400.f) });
    m_vEvents.push_back({ 105.0f,MON_TYPE::NORMAL1,MISSILE_PTRN::PTRN2,Vec2((float)rBackrect.right - 200.f, (float)rBackrect.top - 200.f),Vec2((float)rBackrect.right - 200.f,(float)rBackrect.top + 200.f),Vec2((float)rBackrect.left - 400.f, -400.f) });
    m_vEvents.push_back({ 115.0f,MON_TYPE::NORMAL1,MISSILE_PTRN::PTRN2, Vec2((float)rBackrect.left + 100.f,  (float)rBackrect.top - 200.f),Vec2((float)rBackrect.left + 150.f, (float)rBackrect.top + 200.f),Vec2((float)rBackrect.right + 400.f, -400.f) });
    m_vEvents.push_back({ 120.0f,MON_TYPE::NORMAL1,MISSILE_PTRN::PTRN2,Vec2((float)rBackrect.right - 200.f, (float)rBackrect.top - 200.f),Vec2((float)rBackrect.right - 200.f,(float)rBackrect.top + 200.f),Vec2((float)rBackrect.left - 400.f, -400.f) });
    for (int i = 0; i < 10; ++i)
    {
        m_vEvents.push_back({ 115.0f + 0.4f * i,MON_TYPE::NORMAL5,MISSILE_PTRN::NONE, Vec2((float)rBackrect.left - 250.f, (float)rBackrect.top - 100.f),Vec2(vBackPos.x + 200.f,(float)rBackrect.bottom / 2.f),Vec2((float)rBackrect.left - 250.f, (float)rBackrect.bottom + 100.f) });

    }
    for (int i = 0; i < 10; ++i)
    {
        m_vEvents.push_back({ 117.5f + 0.4f * i,MON_TYPE::NORMAL5,MISSILE_PTRN::NONE,Vec2((float)rBackrect.right + 250.f, (float)rBackrect.top - 100.f),Vec2(vBackPos.x - 200.f,(float)rBackrect.bottom / 2.f),Vec2((float)rBackrect.right + 250.f, (float)rBackrect.bottom + 100.f) });
    }
    for (int i = 0; i < 10; ++i)
    {
        m_vEvents.push_back({ 116.0f + 0.4f * i,MON_TYPE::NORMAL2,MISSILE_PTRN::PTRN3, Vec2((float)rBackrect.left + 300.f, (float)rBackrect.top - 100.f),Vec2((float)rBackrect.left + 100.f,(float)rBackrect.top + 150.f),Vec2((float)rBackrect.right + 250.f, (float)rBackrect.bottom + 100.f) });

    }
    for (int i = 0; i < 10; ++i)
    {
        m_vEvents.push_back({ 121.5f + 0.4f * i,MON_TYPE::NORMAL2,MISSILE_PTRN::PTRN3,Vec2((float)rBackrect.right - 300.f, (float)rBackrect.top - 100.f),Vec2((float)rBackrect.right - 100.f,(float)rBackrect.top + 150.f),Vec2((float)rBackrect.left - 250.f, (float)rBackrect.bottom + 100.f) });
    }









    m_vEvents.push_back({ 130.f,MON_TYPE::RARE,MISSILE_PTRN::PTRN1,Vec2(vBackPos.x,  (float)rBackrect.top - 200.f),Vec2((float)vBackPos.x, (float)rBackrect.bottom / 2.f - 300.f),Vec2((float)vBackPos.x, -400.f) });

}


