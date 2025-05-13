#include "pch.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CObject.h"

#include "CTimeMgr.h"


CAnimation::CAnimation()
	: m_pAnimator(nullptr)
	, m_pTex(nullptr)
	, m_iCurFrm(0)
	, m_fAccTime(0.f)
	, m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}
void CAnimation::update()
{
	if (m_bFinish)
		return;

	m_fAccTime += fDT;

	if (m_fAccTime > m_vecFrm[m_iCurFrm].fDuration)
	{

		++m_iCurFrm;
	
		if (m_vecFrm.size() <= m_iCurFrm)
		{
			m_iCurFrm = -1;
			m_bFinish = true;
		}
		m_fAccTime = m_fAccTime - m_vecFrm[0].fDuration;
		
	}
}

void CAnimation::render(HDC _dc)
{
	if (m_bFinish)
		return;
	CObject* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();
	int iWidith = (int)m_pTex->GetImage()->GetWidth();
	int iHeight = (int)m_pTex->GetImage()->GetHeight();


	//BitBlt(_dc, int(vPos.x - (float)(iWidith / 2))
	//	, int(vPos.y - (float)(iHeight / 2))
	//	, iWidith, iHeight
	//	, m_pTex->GetDC()
	//	, 0, 0, SRCCOPY);

	Graphics graphics(_dc);
	graphics.SetInterpolationMode(InterpolationModeNearestNeighbor);

	
	Rect rect(
		(int)vPos.x - m_vecFrm[m_iCurFrm].vSlicce.x / 2.f,
		(int)vPos.y - m_vecFrm[m_iCurFrm].vSlicce.y / 2.f,
		(int)m_vecFrm[m_iCurFrm].vSlicce.x,
		(int)m_vecFrm[m_iCurFrm].vSlicce.y);
	
	graphics.DrawImage(
		m_pTex->GetImage()
	    , rect
		, (int)m_vecFrm[m_iCurFrm].vLT.x
		, (int)m_vecFrm[m_iCurFrm].vLT.y
		, (int)m_vecFrm[m_iCurFrm].vSlicce.x
		, (int)m_vecFrm[m_iCurFrm].vSlicce.y
		,UnitPixel
	);
	/*TransparentBlt(_dc
		, (int)vPos.x - m_vecFrm[m_iCurFrm].vSlicce.x / 2.f
		, (int)vPos.y - m_vecFrm[m_iCurFrm].vSlicce.y / 2.f
		, (int)m_vecFrm[m_iCurFrm].vSlicce.x
		, (int)m_vecFrm[m_iCurFrm].vSlicce.y
		, m_pTex->GetDC()
		, (int)m_vecFrm[m_iCurFrm].vLT.x
		, (int)m_vecFrm[m_iCurFrm].vLT.y
		, (int)m_vecFrm[m_iCurFrm].vSlicce.x
		, (int)m_vecFrm[m_iCurFrm].vSlicce.y
		, RGB(255,0,255));*/
}

void CAnimation::Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;

	tAnimFrm frm = {};
	for (UINT i = 0; i < _iFrameCount; ++i)
	{
		frm.fDuration = _fDuration;
		frm.vSlicce = _vSliceSize;
		frm.vLT = _vLT + _vStep * i;

		m_vecFrm.push_back(frm);
	}
}
