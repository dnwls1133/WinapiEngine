#pragma once
#include "CObject.h"

class CTexture;
class CBackground :
    public CObject
{ 
private:
    CTexture* m_pTex;
    float     m_dAcc;
    wstring   m_strRelativePath;
    wstring   m_strKey;

    int       m_iAnimationidx;
public:
    virtual void update();
    virtual void render(HDC _dc);
    CLONE(CBackground);
  
public:
    CBackground();
    ~CBackground();

};

