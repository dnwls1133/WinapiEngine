#pragma once
#include "CAnimationBase.h"

class CTexture;

class CAnimationBase;
class CAnimator;

/**
 * @brief 시트 방식의 애니메이션을 정의합니다.
 */
class CSheetAnimation
	: public CAnimationBase
{
	friend class CAnimationBase;
public:
	CSheetAnimation();
	virtual ~CSheetAnimation() override;

protected:
	/**
	 * @brief 
	 */
	virtual void OnUpdate() override;

	/**
	 * @brief 화면에 그리기 작업을 수행할 때 호출되는 가상 함수입니다.
	 * @param canvas_ 그리기 작업에 사용할 디바이스 컨텍스트 핸들(HDC)입니다.
	 */
	virtual void OnRender(HDC canvas_) const override;

private:
	/**
	 * @brief 사용할 시트.
	 */
	CTexture* m_pTexture;

	/**
	 * @brief 오프셋.
	 */
	Vec2 m_vOffset;

	/**
	 * @brief 잘라낼 크기.
	 */
	Vec2 m_vSliceSize;

};

