#pragma once

class CSound;

class CSoundMgr
{
    SINGLE(CSoundMgr);
public:
    void PlayBGM(CSound* const bgm_) const;
    void PlaySE(const std::wstring& path_);

    // void StopBGM();
    // void PauseBGM();
    // 
    // CSound* const GetCurrentBGM() const;
    // 
    // float GetBGMVolume() const;
    // void SetBGMVolume(float volume_);
    // 
    // float GetSEVolume() const;
    // void SetSEVolume(float volume_);

private:
    CSound* m_pCurrentBGM;

    float m_fBGMVolume;
    float m_fSEVolume;

};
