#include "pch.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CMonster.h"
#include "CPlayer.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CMissile.h"
#include "CCollider.h"

CMonster::CMonster()
	:m_vCenterPos(Vec2(0.f,0.f))
	,m_fSpeed(100.f)
	,m_fMaxDistance(100.f)
	,m_iDir(1)
	, m_vxDir1(1)
	, m_vxDir(0.f)
	, m_vxrDir1(1)
	, m_vxrDir(0.f)
	, dAccTime0(0.)
	, dAccTime1(0.)
	, m_pTex(nullptr)
{
	//Texture 로딩하기
	m_pTex = CResMgr::GetInst()->LoadTexture(L"Enemie0Tex", L"texture\\Enemie1.png");
	CreaeteCollider();
	GetCollider()->SetScale(Vec2(50.f, 50.f));
}

CMonster::~CMonster()
{
}

void CMonster::update()
{
	Vec2 vCurPos = GetPos();
	// 진행 방향으로 시간당 m_fSpeed로 이동가능 
	vCurPos.x += fDT * m_fSpeed * m_iDir;
	float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance;
	if (0.f < fDist)
	{
		m_iDir *= -1;
		vCurPos.x += fDist * m_iDir; // 한계점에서 초과한 거리만큼 다시 빼준다.
	}
	SetPos(vCurPos);
	dAccTime0 += fDT;
	dAccTime1 += fDT;
	if (dAccTime0 < 3.f)
	{
		if (dAccTime1 > 0.25f)
		{
			dAccTime1 = 0;
			//CreateMissileP0();
			//CreaeteMisiileP2();

			CreateMissileP1();
			//CreatereverseMissileP1();
		}
	}
	if(3.f <= dAccTime0 && dAccTime0 < 4.5f)
	{
		if (dAccTime1 > 0.05f)
		{
			dAccTime1 = 0;
			//CreateMissileP1();


			//CreatereverseMissileP1();
			//();
		}
	}
	if(dAccTime0 >= 6.0f)
	{
		dAccTime0 = 0;
	}

	
}

void CMonster::render(HDC _dc)
{
	int iWidith = (int)m_pTex->GetImage()->GetWidth();
	int iHeight = (int)m_pTex->GetImage()->GetHeight();
	Vec2 vPos = GetPos();



	//BitBlt(_dc, int(vPos.x - (float)(iWidith / 2))
	//	, int(vPos.y - (float)(iHeight / 2))
	//	, iWidith, iHeight
	//	, m_pTex->GetDC()
	//	, 0, 0, SRCCOPY);

	Graphics graphics(_dc);
	graphics.SetInterpolationMode(InterpolationModeNearestNeighbor);

	

	graphics.DrawImage(
		m_pTex->GetImage()
		, int(vPos.x - (float)(iWidith / 2))
		, int(vPos.y - (float)(iHeight / 2))
		, iWidith
		, iHeight
	);
	component_render(_dc);
}

void CMonster::CreateMissileP0()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y += GetScale().y / 2.f;
	CScene* CurScene = CSceneMgr::GetInst()->GetCurScene();

	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f));
	pMissile->SetVec(200);
	pMissile->SetType(1);
	pMissile->SetName(L"MsMissile");

	CreateObject(pMissile, GROUP_TYPE::PROJ_MONSTER);
}

void CMonster::CreateMissileP1()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y += GetScale().y / 2.f;
	CScene* CurScene = CSceneMgr::GetInst()->GetCurScene();
	
	
	m_vxDir += ((2 * PI) / 36 )* m_vxDir1;

	if (m_vxDir > PI / 4 || m_vxDir < -1.f)
	{
		m_vxDir1 *= -1;
	}
	

	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(m_vxDir,-1.f));
	pMissile->SetVec(200);
	pMissile->SetType(1);
	pMissile->SetName(L"MsMissile");
	CreateObject(pMissile, GROUP_TYPE::PROJ_MONSTER);
}

void CMonster::CreatereverseMissileP1()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y += GetScale().y / 2.f;
	CScene* CurScene = CSceneMgr::GetInst()->GetCurScene();


	m_vxrDir -= ((2 * PI) / 36) * m_vxrDir1;

	if (m_vxrDir > PI / 4 || m_vxrDir < -1.f)
	{
		m_vxrDir1 *= -1;
	}


	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(m_vxrDir, -1.f));
	pMissile->SetVec(200);
	pMissile->SetType(1);
	pMissile->SetName(L"MsMissile");
	CreateObject(pMissile, GROUP_TYPE::PROJ_MONSTER);
}

void CMonster::CreaeteMisiileP2()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y += GetScale().y / 2.f;
	CScene* CurScene = CSceneMgr::GetInst()->GetCurScene();


	m_vxDir += ((2 * PI) /100) * m_vxDir1;

	if (m_vxDir > PI /2  || m_vxDir < -1.f)
	{
		m_vxDir1 *= -1;
	}


	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(m_vxDir, -1.f));
	pMissile->SetVec(200);
	pMissile->SetType(1);
	pMissile->SetName(L"MsMissile");
	CreateObject(pMissile, GROUP_TYPE::PROJ_MONSTER);
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherobj = _pOther->GetObj();
	

}

