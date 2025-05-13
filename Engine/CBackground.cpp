#include "pch.h"
#include "CBackground.h"
#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CTexture.h"

CBackground::CBackground()
	: m_pTex(nullptr)
	, m_dAcc(0.f)
	, m_strRelativePath{}
	, m_strKey{}
	, m_iAnimationidx(0)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"Background0tex", L"texture\\Background110.bmp");
	m_strKey = L"Background0tex";
	m_strRelativePath = L"texture\\Background0.bmp";
}
CBackground::~CBackground()
{

}

void CBackground::update()
{
	//m_dAcc += fDT;

	if (m_dAcc < -0.08f)
	{
		m_strKey.clear();
		m_strKey += L"Background";
		m_strKey += to_wstring(m_iAnimationidx);
		m_strKey += L"tex";

		m_strRelativePath.clear();
		m_strRelativePath += L"texture\\Background";
		m_strRelativePath += to_wstring(m_iAnimationidx);
		m_strRelativePath += L".bmp";

		
		
		if (m_iAnimationidx >= 55)
		{
			m_iAnimationidx = 0;
		}
		else
		{
			++m_iAnimationidx;
		}

		m_pTex = CResMgr::GetInst()->LoadTexture(m_strKey, m_strRelativePath);
		m_dAcc = 0;
	}
	
}

void CBackground::render(HDC _dc)
{
//	int iWidith = (int)m_pTex->Width();
//	int iHeight = (int)m_pTex->Height();
//	Vec2 vPos = GetPos();
//
//	//BitBlt(_dc, int(vPos.x - (float)(iWidith / 2))
//	//	, int(vPos.y - (float)(iHeight / 2))
//	//	, iWidith, iHeight
//	//	, m_pTex->GetDC()
//	//	, 0, 0, SRCCOPY);
//
//	TransparentBlt(_dc
//		, int(vPos.x - (float)(iWidith / 2))
//		, int(vPos.y - (float)(iHeight / 2))
//		, iWidith, iHeight
//		, m_pTex->GetDC()
//		, 0, 0, iWidith, iHeight
//		, RGB(255, 0, 255)); // 색상을 무시하고 나머지 복사해라
	int iWidith = (int)m_pTex->GetImage()->GetWidth();
	int iHeight = (int)m_pTex->GetImage()->GetHeight();
	Vec2 vPos = GetPos();



	//BitBlt(_dc, int(vPos.x - (float)(iWidith / 2))
	//	, int(vPos.y - (float)(iHeight / 2))
	//	, iWidith, iHeight
	//	, m_pTex->GetDC()
	//	, 0, 0, SRCCOPY);

	Graphics graphics(_dc);
	graphics.SetInterpolationMode(InterpolationModeHighQualityBicubic);

	

	graphics.DrawImage(
		m_pTex->GetImage()
		, int(vPos.x - (float)(iWidith / 2))
		, int(vPos.y - (float)(iHeight / 2))
		, iWidith
		, iHeight
	);
}
