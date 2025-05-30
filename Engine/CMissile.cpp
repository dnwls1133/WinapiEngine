#include "pch.h"
#include "CMissile.h"
#include "CTimeMgr.h"
#include "CResMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CTexture.h"
#include "CBackground.h"

#include "CCore.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"


CMissile::CMissile()
	: m_dAcc(0.f)
    ,m_fTheta(0.f)
	, m_vDir(Vec2(1.f,1.f))
	, m_pTex(nullptr)
	, m_fVec(0.f)

{
	
	m_vDir.Normalize();
	CreaeteCollider();
	GetCollider()->SetScale(Vec2(15.f, 15.f));
	

	
	

}

CMissile::~CMissile()
{
}

void CMissile::init(GROUP_TYPE _eType)
{
	switch (_eType)
	{
	case GROUP_TYPE::PROJ_PLAYER:
	{
		m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerMissileTex0", L"texture\\Missile00.bmp");
		CreaeteAnimator();
		GetAnimator()->CreateAnimation(L"Missile0", m_pTex, Vec2(0.f, 0.f), Vec2(50.f, 89.f), Vec2(50.f, 0.f), 0.5f, 4);
		GetAnimator()->Play(L"Missile0", true);
	}
		
		break;
	case GROUP_TYPE::PROJ_MONSTER:
	{
		m_pTex = CResMgr::GetInst()->LoadTexture(L"MonsterMissileTex0", L"texture\\Monster_Middle_Bullet.png");
		CreaeteAnimator();
		GetAnimator()->CreateAnimation(L"MonsterMissile0", m_pTex, Vec2(0.f, 0.f), Vec2(42.f, 42.f), Vec2(42.f, 0.f), 0.5f, 2);
		GetAnimator()->Play(L"MonsterMissile0", true);
	}
	break;
	}

}
void CMissile::update()
{
	Vec2 vPos = GetPos();
	Vec2 resolution = CCore::GetInst()->GetResolution();
    CBackground* Background = (CBackground*)CSceneMgr::GetInst()->GetCurScene()->GetBackground();
    Vec2 vBackPos = Background->GetPos();
    Vec2 vBackScale = Background->GetScale();

	if (vPos.y > resolution.y || vPos.y < -100.f
        || vPos.x > vBackPos.x + vBackScale.x/2 + 50.f
        || vPos.x < vBackPos.x - vBackScale.x/2 - 50.f)
	{
		DeleteObject(this);
	}
	//vPos.x += 700.f * cos(m_fTheta) * fDT;
	//vPos.y -= 700.f * sin(m_fTheta) * fDT;
   
    if (GetName() == L"MsMissile")
    {
        if (m_dAcc >= 0)
        {
            m_dAcc += fDT;
        }
      
        if ( m_dAcc > 1.f)
        {
            m_fVec /= 2.f;
            m_dAcc = -1.f;
        }
    }
	vPos.x += m_fVec * m_vDir.x * fDT;
	vPos.y -= m_fVec * m_vDir.y * fDT;
	SetPos(vPos);
	if (nullptr != GetAnimator())
	{
		GetAnimator()->update();
	}
	
}

void CMissile::render(HDC _dc)
{
	//Vec2 vPos = GetPos();
	//Vec2 vScale = GetScale();

	//Ellipse(_dc, (int)vPos.x - vScale.x / 2.f
	//	, (int)vPos.y - vScale.y / 2.f
	//	, (int)vPos.x + vScale.x / 2.f
	//	, (int)vPos.y + vScale.y / 2.f);

	//switch (m_iType)
	//{
	//case 0:
	//{
	//	
	//	Vec2 Scale;
	//	Scale.x = (1 * m_pTex->Width()) / 3;
	//	Scale.y = (1 * m_pTex->Height())/3;
	//	GetCollider()->SetScale(Scale);
	//	
	//}
	//break;
	//case 1:
	//{
	//	m_pTex = CResMgr::GetInst()->LoadTexture(L"MissileTex0R", L"texture\\Missile0R.bmp");
	//	GetCollider()->SetScale(Vec2(20.f, 20.f));
	//	int iWidith = (int)m_pTex->Width();
	//	int iHeight = (int)m_pTex->Height();
	//	Vec2 vPos = GetPos();



	//	//BitBlt(_dc, int(vPos.x - (float)(iWidith / 2))
	//	//	, int(vPos.y - (float)(iHeight / 2))
	//	//	, iWidith, iHeight
	//	//	, m_pTex->GetDC()
	//	//	, 0, 0, SRCCOPY);

	//	TransparentBlt(_dc
	//		, int(vPos.x - (float)(iWidith / 2))
	//		, int(vPos.y - (float)(iHeight / 2))
	//		, iWidith, iHeight
	//		, m_pTex->GetDC()
	//		, 0, 0, iWidith, iHeight
	//		, RGB(255, 0, 255)); // 색상을 무시하고 나머지 복사해라
	//	break;
	//}
	//case 3:
	//{
	//	m_pTex = CResMgr::GetInst()->LoadTexture(L"Missileboom0Tex", L"texture\\Missileboom0.bmp");
	//	int iWidith = (int)m_pTex->Width();
	//	int iHeight = (int)m_pTex->Height();
	//	Vec2 vPos = GetPos();



	//	//BitBlt(_dc, int(vPos.x - (float)(iWidith / 2))
	//	//	, int(vPos.y - (float)(iHeight / 2))
	//	//	, iWidith, iHeight
	//	//	, m_pTex->GetDC()
	//	//	, 0, 0, SRCCOPY);

	//	TransparentBlt(_dc
	//		, int(vPos.x - (float)(iWidith / 2))
	//		, int(vPos.y - (float)(iHeight / 2))
	//		, iWidith, iHeight
	//		, m_pTex->GetDC()
	//		, 0, 0, iWidith, iHeight
	//		, RGB(255, 0, 255)); // 색상을 무시하고 나머지 복사해라
	//}
	//break;
	//}
	
	component_render(_dc);
}



void CMissile::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Monster")
	{
		m_pTex = CResMgr::GetInst()->LoadTexture(L"MissileTex1", L"texture\\Missile_explosion.png");
		CreaeteAnimator();
		GetAnimator()->CreateAnimation(L"Missile1", m_pTex, Vec2(0.f, 0.f), Vec2(33.88f, 78.f), Vec2(33.88f, 0.f), 0.05f, 17);
		GetAnimator()->Play(L"Missile1", false);
		CAnimation* pAnim = GetAnimator()->FindAnimation(L"Missile1");
		
		for (int i = 0; i < pAnim->GetMaxFrame(); ++i)
		{
			pAnim->GetFrame(i).vOffset = Vec2(0.f, -100.f);
		}
		
		m_fVec = 100.f;
	}
}

void CMissile::OnCollision(CCollider* _pOther)
{
	
}

void CMissile::OnCollisionExit(CCollider* _pOther)
{
    CObject* pOtherObj = _pOther->GetObj();
 
    if (pOtherObj->GetName() == L"Monster")
    {
       
           DeleteObject(this);

       
    }
}
