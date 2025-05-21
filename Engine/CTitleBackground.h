#pragma once

#include <format>
#include <memory>

#include "CTexture.h"
#include "CObject.h"
#include "CResMgr.h"

class CTexture;

/**
 * @brief 타이틀 Scene 내 재생되는 백그라운드 오브젝트에 대해 정의합니다.
 */
class CTitleBackground :
    public CObject
{
public:
    /**
     * @brief 생성자.
     */
    CTitleBackground();

    /**
     * @brief 소멸자.
     */
    virtual ~CTitleBackground() override;

    /**
     * @brief 매 프레임마다 호출됩니다.
     */
    virtual void update() override;

private:
    /**
     * @brief 백그라운드 텍스쳐.
     */
    std::unique_ptr<CTexture> m_pTexture;

};

