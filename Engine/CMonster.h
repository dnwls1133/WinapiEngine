#pragma once
#include "CObject.h"
class AI;
class CTexture;

class CMonster :
    public CObject
{
protected:
    CTexture*   m_pTex;
    float       m_fSpeed;
    double      dAccTime0;
    double      dAccTime1;
    AI*         m_pAI;
public:
    virtual void update();
    virtual void render(HDC _dc);
public:
    virtual void CreateMissile(int type);
    

public:
    virtual void OnCollisionEnter(CCollider* _pOther);
public:
    void SetSpeed(float _f) { m_fSpeed = _f;}
    float GetSpeed() { return m_fSpeed; }

    void SetAI(AI* _AI);

    CLONE(CMonster);
public:
    CMonster();
    virtual ~CMonster();
};

