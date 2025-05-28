#include "pch.h"
#include "CSoundMgr.h"

#include "CResMgr.h"
#include "CSound.h"

CSoundMgr::CSoundMgr()
    : m_fBGMVolume(0.5)
    , m_fSEVolume(0.5)
{

}

CSoundMgr::~CSoundMgr()
{

}

void CSoundMgr::PlayBGM(CSound* const bgm_) const
{
    // m_pCurrentBGM = bgm_;
    bgm_->SetVolume(m_fBGMVolume);
    bgm_->Play(true);
}

void CSoundMgr::PlaySE(CSound* const se_)
{
    se_->SetVolume(m_fSEVolume);
    se_->Play(false);
}
