#include "pch.h"
#include "CAnimationBase.h"

#include "CObject.h"
#include "CTexture.h"
#include "CAnimator.h"

#include "CTimeMgr.h"

CAnimationBase::CAnimationBase()
	: m_pAnimator(nullptr)
	, m_bIsPlaying(false)
{

}

CAnimationBase::~CAnimationBase()
{

}

void CAnimationBase::Update()
{
	if (!m_bIsLoop) 
	{
		return;
	}

	if ((m_fDelayTimer += CTimeMgr::GetInst()->GetfDT()) >= m_fDelayTime)
	{
		if ((++m_iCurrentFrame) >= m_iFrameCount)
		{
			if (!m_bIsLoop)
			{
				m_bIsPlaying = false;
				m_iCurrentFrame = m_iFrameCount;
				m_fDelayTimer = m_fDelayTime;
			}
			else
			{
				m_iCurrentFrame = 0;
				m_fDelayTimer = 0.0f;
			}
		}
	}
}

void CAnimationBase::Render(HDC canvas_) const
{
	if (!m_pAnimator)
	{
		return;
	}

	OnRender(canvas_);
}

CAnimator* const CAnimationBase::GetAnimator() const
{
	return m_pAnimator;
}

bool CAnimationBase::GetLoop() const
{
	return m_bIsLoop;
}

void CAnimationBase::SetLoop(bool isLoop_)
{
	m_bIsLoop = isLoop_;
}

bool CAnimationBase::IsPlaying() const
{
	return m_bIsPlaying;
}

void CAnimationBase::Play()
{
	m_bIsPlaying = true;
}

void CAnimationBase::Pause()
{
	m_bIsPlaying = false;
}

void CAnimationBase::Stop()
{
	m_bIsPlaying = false;
	m_fDelayTimer = 0.0f;
}

size_t CAnimationBase::GetFrameCount() const
{
	return m_iFrameCount;
}

size_t CAnimationBase::GetCurrentFrame() const
{
	return m_iCurrentFrame;
}
