#pragma once
#include "CObject.h"
class CTexture;

class CPlayer :
    public CObject
{

private:
  //  CTexture*   m_pTex;
    double      dAcc;
    double      dStartAcc;
    int         m_iHp;
    bool        m_bHit;
    int         m_iAtk;

public:
    virtual void update();
    virtual void render(HDC _dc);

    int GetPlayerAtk() { return m_iAtk; }
private:
    void CreateMissile(int type);
    
    virtual void OnCollisionEnter(CCollider* _pOther);

    CLONE(CPlayer);
public:
    CPlayer();
    ~CPlayer();
};



