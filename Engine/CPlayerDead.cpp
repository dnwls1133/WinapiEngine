#include "pch.h"
#include "CPlayerDead.h"
#include"CResMgr.h"
#include"CTimeMgr.h"


#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
CPlayerDead::CPlayerDead()
	:m_fAcc(0.f)
{

	CTexture* m_pTex = CResMgr::GetInst()->LoadTexture(L"MissileTex1", L"texture\\missile_explosion.png");
	CreaeteAnimator();
	GetAnimator()->CreateAnimation(L"Missile1", m_pTex, Vec2(0.f, 0.f), Vec2(25.4f, 72.f), Vec2(25.4f, 0.f), 0.05f, 17);
	GetAnimator()->Play(L"Missile1", false);
}

CPlayerDead::~CPlayerDead()
{
}

void CPlayerDead::update()
{
	m_fAcc += fDT;
	if (m_fAcc > 0.9f)
	{
		DeleteObject(this);
	}
	GetAnimator()->update();
}

void CPlayerDead::render(HDC _dc)
{
	component_render(_dc);
}

