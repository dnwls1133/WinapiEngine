#pragma once

#include "CObject.h"

class CObject;
class CTexture;

class CTitleLogo
    : public CObject
{
public:
    virtual void update() override;
    virtual void render(HDC dc) override;
    CLONE(CTitleLogo)

private:
    /**
     * @brief 로고 텍스쳐.
     */
    CTexture* m_pTexture = nullptr;

};
