#pragma once

#include "CResource.h"

class CSound 
    : public CResource
{
public:
    CSound();
    virtual ~CSound() override;

    void Load(std::wstring_view filePath_);
    void Create(std::wstring_view filePath_);

    void Play();
    void Pause();
    void Stop();

private:
    

};

