#include "pch.h"
#include "CPlayer.h"


#include "CSceneMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"



#include "CScene.h"
#include "CMissile.h"
#include "CPlayerDead.h"

#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
CPlayer::CPlayer()
	:dAcc(0.)
	,m_iHp(3)
    ,m_bHit(false)
	
{
	//Texture 로딩하기
	//m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player.bmp");
	CreaeteCollider();
	GetCollider()->SetScale(Vec2(10.f, 15.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, 20.f));


	CTexture* m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerWalk", L"texture\\Player\\Player_Walk.png");
	CreaeteAnimator();

    GetAnimator()->LoadAnimation(L"animation\\player_walk_left.anim");

	/*GetAnimator()->CreateAnimation(L"Player_walk",m_pTex, Vec2(0.f, 0.f), Vec2(140.f, 140.f), Vec2(140.f, 0.f), 0.05f, 19);
    m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerInvincible", L"texture\\Player\\Player_Invincible.png");
    GetAnimator()->CreateAnimation(L"Player_Invincible", m_pTex, Vec2(0.f, 0.f), Vec2(140.f, 140.f), Vec2(140.f, 0.f), 0.05f, 20);

    Animation 저장해보기
    GetAnimator()->FindAnimation(L"Player_walk")->Save(L"animation\\player_walk_left.anim");
    GetAnimator()->FindAnimation(L"Player_Invincible")->Save(L"animation\\player_Invincible.anim");*/

    GetAnimator()->Play(L"Player_walk", true);
}

CPlayer::~CPlayer()
{
	
}
void CPlayer::update()
{
	Vec2 vPos = GetPos();

	if (m_bHit == true)
	{
		dAcc += fDT;
        if (dAcc < 1.5f)
        {
            vPos.y -= 300.f * fDT;
        }
		
		if (dAcc > 2.f)
		{
			dAcc = 0;
            GetAnimator()->LoadAnimation(L"animation\\player_walk_left.anim");
            GetAnimator()->Play(L"Player_walk", true);
			SetCollideron();
			m_bHit = false;
		}
		SetPos(vPos);

	}
    {
		if (KEY_HOLD(KEY::W))
		{
			vPos.y -= 250.f * fDT;
		}
		if (KEY_HOLD(KEY::S))
		{
			vPos.y += 250.f * fDT;
		}
		if (KEY_HOLD(KEY::A))
		{
			vPos.x -= 250.f * fDT;
		}
		if (KEY_HOLD(KEY::D))
		{
			vPos.x += 250.f * fDT;
		}
		if (KEY_HOLD((KEY::SPACE)))
		{
			dAcc += fDT;
			if (dAcc > 0.15f)
			{
				dAcc = 0;
				CreateMissile(0);
				//CreateMissile(1);
				//CreateMissile(2);
			}




		}
		SetPos(vPos);
	}
	
	//GetAnimator()->update();
}

void CPlayer::render(HDC _dc)
{
	/*int iWidith = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();
	Vec2 vPos = GetPos();*/

	//BitBlt(_dc, int(vPos.x - (float)(iWidith / 2))
	//	, int(vPos.y - (float)(iHeight / 2))
	//	, iWidith, iHeight
	//	, m_pTex->GetDC()
	//	, 0, 0, SRCCOPY);

	//TransparentBlt(_dc
	//	, int(vPos.x - (float)(iWidith / 2))
	//	, int(vPos.y - (float)(iHeight / 2))
	//	, iWidith, iHeight
	//	, m_pTex->GetDC()
	//	, 0, 0, iWidith, iHeight
	//	, RGB(255, 0, 255)); // 색상을 무시하고 나머지 복사해라
	
	component_render(_dc);
   /* CTexture* pTex  = CResMgr::GetInst()->LoadTexture(L"M4Tex", L"texture\\Player_Walk_A.png");

    Vec2 vPos = GetPos();
    vPos = CCamera::GetInst()->GetRenderPos(vPos);

    float width = (float)pTex->Width();
    float height = (float)pTex->Height();

    BLENDFUNCTION bf = {};

    bf.BlendOp = AC_SRC_OVER;
    bf.BlendFlags = 0;
    bf.AlphaFormat = AC_SRC_ALPHA;
    bf.SourceConstantAlpha = 255;

    AlphaBlend(_dc
        , int(vPos.x - width / 2.f)
        , int(vPos.y - height / 2.f)
        , width, height
        , pTex->GetDC()
        , 0, 0, width, height
        , bf);*/
}

void CPlayer::CreateMissile(int type)
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;
	switch (type)
	{
	case 1:
	{
		vMissilePos.x -= 30.f;
	}
		break;
	case 2:
	{
		vMissilePos.x += 30.f;
	}
		break;
	}
	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->init(GROUP_TYPE::PROJ_PLAYER);
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f,1.f));
	pMissile->SetVec(2000);
	pMissile->SetType(0);
	pMissile->SetName(L"Missile_Player");

	CreateObject(pMissile,GROUP_TYPE::PROJ_PLAYER);
}


void CPlayer::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"MsMissile" && m_bHit == false)
	{
        GetAnimator()->LoadAnimation(L"animation\\player_Invincible.anim");
        GetAnimator()->Play(L"Player_Invincible", true);
		CPlayerDead* pDead = new CPlayerDead;
		pDead->SetPos(GetPos());
		pDead->SetName(L"Player_Dead");
		CreateObject(pDead, GROUP_TYPE::DEAD_PLAYER);
		--m_iHp;
		m_bHit = true;
		Vec2 vPos = GetPos();
		vPos.y = 1200;
		SetPos(vPos);
		SetCollideroff();
	}
		
	
}





