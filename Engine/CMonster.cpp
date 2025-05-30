#include "pch.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CMonster.h"
#include "CPlayer.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "AI.h"


#include "CMissile.h"
#include "CCollider.h"

#include "CAnimator.h"
#include "CAnimation.h"

CMonster::CMonster()
	: m_tInfo{}
	, dAccTime0(0.)
	, dAccTime1(0.)
	
    , m_pAI(nullptr)
{

    CreaeteCollider();
    GetCollider()->SetScale(Vec2(50.f, 50.f));

	//Texture 로딩하기
    CTexture* m_pTex = CResMgr::GetInst()->LoadTexture(L"N1Enemy_Move", L"texture\\Enemies\\normal1_enemy_Move.png");
    CreaeteAnimator();

   
    {
        //GetAnimator()->CreateAnimation(L"N1Enemy_Move", m_pTex, Vec2(0.f, 0.f), Vec2(190.f, 190.f), Vec2(190.f, 0.f), 0.05f, 40);
   ////Animation 저장
   //GetAnimator()->FindAnimation(L"N1Enemy_Move")->Save(L"animation\\N1Enemy_Move.anim");

   //m_pTex = CResMgr::GetInst()->LoadTexture(L"N2Enemy_Move", L"texture\\Enemies\\normal2_enemy_Move.png");
   //GetAnimator()->CreateAnimation(L"N2Enemy_Move", m_pTex, Vec2(0.f, 0.f), Vec2(150.f, 150.f), Vec2(150.f, 0.f), 0.05f, 40);
   ////Animation 저장
   //GetAnimator()->FindAnimation(L"N2Enemy_Move")->Save(L"animation\\N2Enemy_Move.anim");

   //m_pTex = CResMgr::GetInst()->LoadTexture(L"N2Enemy_Dead", L"texture\\Enemies\\normal2_enemy_Dead.png");
   //GetAnimator()->CreateAnimation(L"N2Enemy_Dead", m_pTex, Vec2(0.f, 0.f), Vec2(150.f, 150.f), Vec2(150.f, 0.f), 0.05f, 12);
   ////Animation 저장
   //GetAnimator()->FindAnimation(L"N2Enemy_Dead")->Save(L"animation\\N2Enemy_Dead.anim");

   //m_pTex = CResMgr::GetInst()->LoadTexture(L"N3Enemy_Move", L"texture\\Enemies\\normal3_enemy_Move.png");
   //GetAnimator()->CreateAnimation(L"N3Enemy_Move", m_pTex, Vec2(0.f, 0.f), Vec2(170.f, 170.f), Vec2(170.f, 0.f), 0.05f, 20);
   ////Animation 저장
   //GetAnimator()->FindAnimation(L"N3Enemy_Move")->Save(L"animation\\N3Enemy_Move.anim");

   //m_pTex = CResMgr::GetInst()->LoadTexture(L"N4Enemy_Move", L"texture\\Enemies\\normal4_enemy_Move.png");
   //GetAnimator()->CreateAnimation(L"N4Enemy_Move", m_pTex, Vec2(0.f, 0.f), Vec2(170.f, 170.f), Vec2(170.f, 0.f), 0.05f, 20);
   ////Animation 저장
   //GetAnimator()->FindAnimation(L"N4Enemy_Move")->Save(L"animation\\N4Enemy_Move.anim");

   //m_pTex = CResMgr::GetInst()->LoadTexture(L"E1Enemy_Move", L"texture\\Enemies\\Epic1_Enemy_Move.png");
   //GetAnimator()->CreateAnimation(L"E1Enemy_Move", m_pTex, Vec2(0.f, 0.f), Vec2(300.f, 300.f), Vec2(300.f, 0.f), 0.05f, 40);
   ////Animation 저장
   //GetAnimator()->FindAnimation(L"E1Enemy_Move")->Save(L"animation\\E1Enemy_Move.anim");

   //m_pTex = CResMgr::GetInst()->LoadTexture(L"E1Enemy_Dead", L"texture\\Enemies\\Epic1_Enemy_Dead.png");
   //GetAnimator()->CreateAnimation(L"E1Enemy_Dead", m_pTex, Vec2(0.f, 0.f), Vec2(300.f, 300.f), Vec2(300.f, 0.f), 0.05f, 13);
   ////Animation 저장
   //GetAnimator()->FindAnimation(L"E1Enemy_Dead")->Save(L"animation\\E1Enemy_Dead.anim");

   //m_pTex = CResMgr::GetInst()->LoadTexture(L"Boss1Enemy_Move", L"texture\\Enemies\\Boss1_Enemy_Move.png");
   //GetAnimator()->CreateAnimation(L"Boss1Enemy_Move", m_pTex, Vec2(0.f, 0.f), Vec2(300.f, 300.f), Vec2(300.f, 0.f), 0.05f, 60);
   ////Animation 저장
   //GetAnimator()->FindAnimation(L"Boss1Enemy_Move")->Save(L"animation\\Boss1Enemy_Move.anim");

   //m_pTex = CResMgr::GetInst()->LoadTexture(L"Boss1Enemy_Dead", L"texture\\Enemies\\Boss1_Enemy_Dead.png");
   //GetAnimator()->CreateAnimation(L"Boss1Enemy_Dead", m_pTex, Vec2(0.f, 0.f), Vec2(300.f, 300.f), Vec2(300.f, 0.f), 0.05f, 50);
   ////Animation 저장
   //GetAnimator()->FindAnimation(L"Boss1Enemy_Dead")->Save(L"animation\\Boss1Enemy_Dead.anim");
    }
   
   
}

CMonster::~CMonster()
{
    if (nullptr != m_pAI)
    {
        delete m_pAI;
    }
}

void CMonster::update()
{
    m_pAI->update();

	
}

void CMonster::render(HDC _dc)
{
	
	component_render(_dc);
}

void CMonster::CreateMissile(int type)
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y += GetScale().y / 2.f;
	vMissilePos.x += GetScale().x * type;
	CScene* CurScene = CSceneMgr::GetInst()->GetCurScene();
	CObject* pInfo = CurScene->GetGroupObject(GROUP_TYPE::PLAYER)[0];
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
	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->init(GROUP_TYPE::PROJ_MONSTER);
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(vpPos);
	pMissile->SetVec(500);
	pMissile->SetType(1);
	pMissile->SetName(L"MsMissile");

	CreateObject(pMissile, GROUP_TYPE::PROJ_MONSTER);
}


void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherobj = _pOther->GetObj();
    if (pOtherobj->GetName() == L"Missile_Player")
    {
      
        m_tInfo.fHP -= 1;
        if (m_tInfo.fHP < 0)
        {
           // m_pAI->ChangeState(MON_STATE::DEAD);
            DeleteObject(this);
        }
       
    }

}
void CMonster::SetAI(AI* _AI)
{
    m_pAI = _AI;
    m_pAI->m_pOwner = this;
}

void CMonster::SetAnim(MON_TYPE eType)
{
    switch (eType)
    {
    case MON_TYPE::NORMAL1:
    {
        GetAnimator()->LoadAnimation(L"animation\\N1Enemy_Move.anim");
        GetAnimator()->Play(L"N1Enemy_Move", true);
    }
        break;
    case MON_TYPE::NORMAL2:
    {
        GetAnimator()->LoadAnimation(L"animation\\N2Enemy_Move.anim");
        GetAnimator()->Play(L"N2Enemy_Move", true);
    }
        break;
    case MON_TYPE::NORMAL3:
    {
        GetAnimator()->LoadAnimation(L"animation\\N3Enemy_Move.anim");
        GetAnimator()->Play(L"N3Enemy_Move", true);
    }
        break;
    case MON_TYPE::NORMAL4:
    {
        GetAnimator()->LoadAnimation(L"animation\\N4Enemy_Move.anim");
        GetAnimator()->Play(L"N4Enemy_Move", true);
    }
        break;
    case MON_TYPE::RARE:
    {
        GetAnimator()->LoadAnimation(L"animation\\Boss1Enemy_Move.anim");
        GetAnimator()->Play(L"Boss1Enemy_Move", true);
    }
        break;
    case MON_TYPE::EPIC:
    {
        GetAnimator()->LoadAnimation(L"animation\\E1Enemy_Move.anim");
        GetAnimator()->Play(L"E1Enemy_Move", true);
    }
        break;
    case MON_TYPE::BOSS:
    {
        GetAnimator()->LoadAnimation(L"animation\\N2Enemy_Move.anim");
        GetAnimator()->Play(L"N2Enemy_Move", true);
    }
        break;
    default:
        break;
    }
   
   
}

