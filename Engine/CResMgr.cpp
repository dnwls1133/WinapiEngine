#include "pch.h"
#include "CResMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"
#include "CResource.h"
CResMgr::CResMgr()
{

}
CResMgr::~CResMgr()
{
	Safe_Delete_Map(m_TextureBank);
}

CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{

	CTexture* pTex = FindTexture(_strKey);
	if (nullptr != pTex)
	{
		return pTex;
	}
	wstring strFilPath = CPathMgr::GetInst()->GetContentPath();
	strFilPath += _strRelativePath;

	pTex = new CTexture;
	pTex->Load(strFilPath);
	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);
	m_TextureBank.insert(make_pair(_strKey, pTex));
	
	
	
	return pTex;
}

CTexture* CResMgr::CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight)
{
    CTexture* pTex = FindTexture(_strKey);
    if (nullptr != pTex)
    {
        return pTex;
    }
   

    pTex = new CTexture;
    pTex->Create(_iWidth, _iHeight);
    pTex->SetKey(_strKey);
    m_TextureBank.insert(make_pair(_strKey, pTex));



    return pTex;
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
	auto iter = m_TextureBank.find(_strKey);
	
	if (iter == m_TextureBank.end())
	{
		return nullptr;
	}
	return (CTexture*)iter->second;
	
}
