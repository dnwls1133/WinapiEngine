#include "pch.h"
#include "CBoomb.h"

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



CBoomb::CBoomb()
    :m_fAcc(0.f)
{
    CreaeteCollider();
    GetCollider()->SetScale(Vec2(500.f, 900.f));

    CTexture* m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerBoombTex", L"texture\\Boomb.png");
    CreaeteAnimator();


    GetAnimator()->CreateAnimation(L"PlayerBoom0", m_pTex, Vec2(0.f, 0.f), Vec2(540.f, 960.f), Vec2(540.f, 0.f), 0.025f, 40);
    GetAnimator()->FindAnimation(L"PlayerBoom0")->Save(L"animation\\PlayerBoom0.anim");

    GetAnimator()->Play(L"PlayerBoom0", false);
}

CBoomb::~CBoomb()
{
    
}


void CBoomb::update()
{
    m_fAcc += fDT;
    if (m_fAcc > 1.0f)
    {
        SetCollideroff();
        DeleteObject(this);
        m_fAcc = 0.f;
        return;
    }
}

void CBoomb::render(HDC _dc)
{
    Vec2 vres = CCore::GetInst()->GetResolution();
    BLENDFUNCTION bf = {};

    bf.BlendOp = AC_SRC_OVER;
    bf.BlendFlags = 0;
    bf.AlphaFormat = 0;
    bf.SourceConstantAlpha = 125.f;

    AlphaBlend(_dc, 0, 0
        , vres.x
        , vres.y
        , _dc
        , 0, 0
        , vres.x
        , vres.y
        , bf);
    component_render(_dc);
}

void CBoomb::OnCollisionEnter(CCollider* _pOther)
{
}

void CBoomb::OnCollision(CCollider* _pOther)
{
}

void CBoomb::OnCollisionExit(CCollider* _pOther)
{
}


