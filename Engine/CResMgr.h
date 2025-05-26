#pragma once

class CResource;
class CTexture;
class CSound;

class CResMgr
{
	SINGLE(CResMgr);
private:
	std::map<std::wstring, CTexture*> m_TextureBank;
	std::map<std::wstring, CSound*> m_AudioBank;
	// std::map<std::wstring, >

public:
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
    CTexture* CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight);
	CTexture* FindTexture(const wstring& _strKey);

	CSound* const LoadSound(std::wstring_view key_, std::wstring_view filePath_);
	CSound* const CreateSound(std::wstring_view key_, std::wstring_view filePath_);
	CSound* const FindSound(std::wstring_view key_);

};

