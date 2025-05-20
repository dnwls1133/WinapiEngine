#pragma once
#include "CObject.h"
class CTexture;

class CPlayer :
    public CObject
{

private:
  //  CTexture*   m_pTex;
    double      dAcc;
    int         m_iHp;
    bool        m_bHit;
public:
    virtual void update();
    virtual void render(HDC _dc);
private:
    void CreateMissile(int type);
    
    virtual void OnCollisionEnter(CCollider* _pOther);

    CLONE(CPlayer);
public:
    CPlayer();
    ~CPlayer();
};



