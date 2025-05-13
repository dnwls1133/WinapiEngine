#pragma once
#include "CObject.h"
class CTexture;

class CPlayer :
    public CObject
{

private:
  //  CTexture*   m_pTex;
    double      dAcc;

public:
    virtual void update();
    virtual void render(HDC _dc);
private:
    void CreateMissile(int type);


    CLONE(CPlayer);
public:
    CPlayer();
    ~CPlayer();
};



