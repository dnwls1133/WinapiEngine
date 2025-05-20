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
	
{
	//Texture 로딩하기
	//m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player.bmp");
	CreaeteCollider();
	GetCollider()->SetScale(Vec2(10.f, 20.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, 30.f));


	CTexture* m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player_Walk.bmp");
	CreaeteAnimator();
	GetAnimator()->CreateAnimation(L"Player_walk0",m_pTex, Vec2(0.f, 0.f), Vec2(170.f, 170.f), Vec2(170.f, 0.f), 0.05f, 19);

	GetAnimator()->Play(L"Player_walk0",true);
	
	
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
		vPos.y -= 350.f * fDT;
		if (dAcc > 1.5f)
		{
			dAcc = 0;
			SetCollideron();
			m_bHit = false;
		}
		SetPos(vPos);

	}
	else
	{
		if (KEY_HOLD(KEY::W))
		{
			vPos.y -= 500.f * fDT;
		}
		if (KEY_HOLD(KEY::S))
		{
			vPos.y += 500.f * fDT;
		}
		if (KEY_HOLD(KEY::A))
		{
			vPos.x -= 500.f * fDT;
		}
		if (KEY_HOLD(KEY::D))
		{
			vPos.x += 500.f * fDT;
		}
		if (KEY_HOLD((KEY::SPACE)))
		{
			dAcc += fDT;
			if (dAcc > 0.15f)
			{
				dAcc = 0;
				CreateMissile(0);
				CreateMissile(1);
				CreateMissile(2);
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
	pMissile->SetVec(1000);
	pMissile->SetType(0);
	pMissile->SetName(L"Missile_Player");

	CreateObject(pMissile,GROUP_TYPE::PROJ_PLAYER);
}


void CPlayer::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"MsMissile")
	{
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





