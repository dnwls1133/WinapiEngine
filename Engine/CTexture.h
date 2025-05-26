#pragma once
#include "CResource.h"
class CTexture :
    public CResource
{
private:
    HDC         m_hdc;
    HBITMAP     m_hBit;
  
    BITMAP      m_bitInfo;
public:
    void Load(const wstring& _strFilePath);
    void Create(UINT _iWidth, UINT _iHeight);

    UINT GetWidth() const { return m_bitInfo.bmWidth; }
    UINT GetHeight() const { return m_bitInfo.bmHeight; }

    HDC GetDC() const { return m_hdc; }
    HBITMAP GetBitmap() const { return m_hBit; }
  
public:
    CTexture();
    virtual ~CTexture();
};

