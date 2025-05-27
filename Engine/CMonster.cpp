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



CMonster::CMonster()
	:m_fSpeed(100.f)
	, dAccTime0(0.)
	, dAccTime1(0.)
	, m_pTex(nullptr)
{
	//Texture 로딩하기
	m_pTex = CResMgr::GetInst()->LoadTexture(L"Enemie0Tex", L"texture\\Enemie0.bmp");
	CreaeteCollider();
	GetCollider()->SetScale(Vec2(50.f, 50.f));
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
	int iWidith = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();
	Vec2 vPos = GetPos();
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(vPos);
	//BitBlt(_dc, int(vPos.x - (float)(iWidith / 2))
	//	, int(vPos.y - (float)(iHeight / 2))
	//	, iWidith, iHeight
	//	, m_pTex->GetDC()
	//	, 0, 0, SRCCOPY);

	
	TransparentBlt(_dc
		, (int)vRenderPos.x - iWidith / 2
		, (int)vRenderPos.y - iHeight / 2
		, iWidith
		, iHeight
		, m_pTex->GetDC()
		, 0, 0, iWidith, iHeight
		,RGB(255,0,255)
	);
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
	

}
void CMonster::SetAI(AI* _AI)
{
    m_pAI = _AI;
    m_pAI->m_pOwner = this;
}

