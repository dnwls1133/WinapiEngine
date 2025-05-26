#pragma once

class CAnimator;

/**
 * @brief 애니메이션의 기본 동작을 정의합니다.
 */
class CAnimationBase 
{
	friend class CAnimator;
public:
	/**
	 * @brief 생성자.
	 */
	CAnimationBase();

	/**
	 * @brief 소멸자.
	 */
	virtual ~CAnimationBase();

	/**
	 * @brief 해당 애나메이션을 업데이트합니다.
	 */
	void Update();
	
	/**
	 * @brief 해당 애니메이션을 그립니다.
	 * @param canvas_ 해당 애니메이션을 그릴 HDC.
	 */
	void Render(HDC canvas_) const;

	/**
	 * @brief 해당 애니메이션을 재생하는 Animator를 반환합니다.
	 * @return 해당 애니메이션을 재생하는 Animator.
	 */
	CAnimator* const GetAnimator() const;

	/**
	 * @brief 해당 애니메이션의 루프 여부를 반환합니다.
	 * @return 해당 애니메이션의 루프 여부.
	 */
	bool GetLoop() const;

	/**
	 * @brief 해당 애니메이션의 루프 여부를 설정합니다.
	 * @param isLoop_ 해당 애니메이션의 루프 여부.
	 */
	void SetLoop(bool isLoop_);

	/**
	 * @brief 해당 애니메이션의 재생 여부를 반환합니다.
	 * @return 
	 */
	bool IsPlaying() const;

	/**
	 * @brief 해당 애니메이션을 재생합니다.
	 */
	void Play();

	/**
	 * @brief 해당 애니메이션을 정지합니다.
	 */
	void Pause();

	/**
	 * @brief 해당 애니메이션을 중지합니다.
	 */
	void Stop();

	/**
	 * @brief 해당 애니메이션의 길이를 반환합니다.
	 * @return 해당 애니메이션의 길이.
	 */
	size_t GetFrameCount() const;

	/**
	 * @brief 현재 프레임의 인덱스를 반환합니다.
	 * @return 현재 프레임의 인덱스를 반환합니다.
	 */
	size_t GetCurrentFrame() const;

protected:
	/**
	 * @brief 해당 애니메이션을 업데이트합니다.
	 */
	virtual void OnUpdate() = 0;

	/**
	 * @brief 해당 애니메이션을 그립니다.
	 * @param context_ 해당 애니메이션을 그릴 HDC.
	 */
	virtual void OnRender(HDC canvas) const = 0;

private:
	/**
	 * @brief 해당 애니메이션을 재생하는 Animator.
	 */
	CAnimator* m_pAnimator;

	/**
	 * @brief 현재 재생되고 있는가에 대한 여부.
	 */
	bool m_bIsPlaying;

	/**
	 * @brief 루프에 대한 여부.
	 */
	bool m_bIsLoop;

	/**
	 * @brief 해당 애니메이션의 전체 프레임.
	 */
	size_t m_iFrameCount;

	/**
	 * @brief 현재 프레임.
	 */
	size_t m_iCurrentFrame;

	/**
	 * @brief 다음 프레임으로까지의 대기 시간.
	 */
	float m_fDelayTime;

	/**
	 * @brief 다음 프레임까지의 대기 시간 카운터.
	 */
	float m_fDelayTimer;

};

