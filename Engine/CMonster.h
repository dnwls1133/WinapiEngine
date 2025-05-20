#pragma once
#include "CObject.h"

class CTexture;

class CMonster :
    public CObject
{
protected:
    CTexture*   m_pTex;
    Vec2        m_vCenterPos; //움직임의 중심축이되는 점
    float       m_fSpeed;
    float       m_fMaxDistance;
    int         m_iDir;
    double      dAccTime0;
    double      dAccTime1;
public:
    virtual void update();
    virtual void render(HDC _dc);
public:
    virtual void CreateMissile(int type);
    

public:
    virtual void OnCollisionEnter(CCollider* _pOther);
public:
    void SetSpeed(float _f) { m_fSpeed = _f;}
    void SetMoveDistance(float _f) { m_fMaxDistance = _f; }
    void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }
    float GetSpeed() { return m_fSpeed; }

    CLONE(CMonster);
public:
    CMonster();
    virtual ~CMonster();
};

