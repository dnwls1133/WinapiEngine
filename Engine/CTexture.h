#pragma once
#include "CResource.h"
class CTexture :
    public CResource
{
private:
    HDC         m_hdc;
    HBITMAP     m_hBit;
    Image*      m_pImage;
    BITMAP      m_bitInfo;
public:
    void Load(const wstring& _strFilePath);


    UINT Width() { return m_bitInfo.bmWidth; }
    UINT Height() { return m_bitInfo.bmHeight; }

    HDC GetDC() { return m_hdc; }
    HBITMAP GetBitmap() { return m_hBit; }
    Image* GetImage() { return m_pImage; }
public:
    CTexture();
   virtual  ~CTexture();
};

