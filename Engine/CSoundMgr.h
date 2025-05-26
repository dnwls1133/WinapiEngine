#pragma once

class CSoundMgr
{
	SINGLE(CSoundMgr);
public:
	void Play(std::wstring_view name_, bool isLoop_ = false);
	void Pause(std::wstring_view name_);
	void Stop(std::wstring_view name_);
	void StopAll();

};

