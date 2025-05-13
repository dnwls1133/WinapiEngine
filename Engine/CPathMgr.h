#pragma once
class CPathMgr
{
	SINGLE(CPathMgr);
private:
	wchar_t		m_szContentPath[255]; // 윈도우 경로 제한 255글자
public:
	void init();
	const wchar_t* GetContentPath() { return m_szContentPath; }
};

