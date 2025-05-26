#include "pch.h"
#include "CSheetAnimation.h"

#include "CObject.h"
#include "CTexture.h"

#include "CAnimator.h"

#include "CCamera.h"
#include "CCellAnimation.h"

CSheetAnimation::CSheetAnimation(std::wstring_view filePath_, Vec2 slice_, Vec2_ offset_)
{
	
}

CSheetAnimation::~CSheetAnimation()
{
}

void CSheetAnimation::OnUpdate()
{
	
}

void CSheetAnimation::OnRender(HDC canvas_) const
{
	CObject* const pOwner = GetAnimator()->GetObj();

	Vec2 vOwnerPosition = pOwner->GetPos();
	Vec2 vRenderPosition = CCamera::GetInst()->GetRenderPos(vOwnerPosition);
	vRenderPosition += m_vOffset;

	TransparentBlt(canvas_
		, (int)(vRenderPosition.x - m_vSliceSize.x / 2.f)
		, (int)(vRenderPosition.y - m_vSliceSize.y / 2.f)
		, (int)(m_vSliceSize.x)
		, (int)(m_vSliceSize.y)
		, m_pTexture->GetDC()
		, 0
		, 0
		, m_vSliceSize.x
		, m_vSliceSize.y
		, RGB(255, 0, 255));
}
