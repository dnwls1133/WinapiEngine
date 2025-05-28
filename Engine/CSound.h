#pragma once
#include "CResource.h"
class CSound :
    public CResource
{
public:
    CSound();
    virtual ~CSound() override;

    void Load(const std::wstring& path_);
    void Play(bool isLoop_);
    void Pause();
    void Stop();

    float GetVolume() const;
    void SetVolume(float volume_);

private:
    size_t m_index;

};

