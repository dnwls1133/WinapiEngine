#include "pch.h"
#include "CTexture.h"
#include "CCore.h"

CTexture::CTexture()
	: m_hBit(0)
	, m_hdc(0)
	, m_bitInfo{}
{
}

CTexture::~CTexture()
{
	
	DeleteDC(m_hdc);
	DeleteObject(m_hBit);
}

void CTexture::Load(const wstring& _strFilePath)
{
	//CImage image;
	//HRESULT hr = image.Load(_strFilePath.c_str());
	/*m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP
		, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);*/
	// 비트맵과 연결할 DC
	//m_hdc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());
	if (m_pImage)
		delete m_pImage;
	m_pImage = new Image(_strFilePath.c_str());
	assert(m_pImage && m_pImage->GetLastStatus() == Gdiplus::Ok);
	// 비트맵과 DC 연결

	//HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hdc, m_hBit);
	//DeleteObject(hPrevBit);
	
	// 비트맵 정보
	//GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);

	
	//assert(m_hBit);
}
