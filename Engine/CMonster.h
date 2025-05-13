#pragma once
#include "CObject.h"

class CTexture;

class CMonster :
    public CObject
{
private:
    CTexture* m_pTex;

    Vec2        m_vCenterPos; //움직임의 중심축이되는 점
    float       m_fSpeed;
    float       m_fMaxDistance;
    int         m_iDir;
    int         m_vxDir1;
    float       m_vxDir;
    int         m_vxrDir1;
    float       m_vxrDir;
    double      dAccTime0;
    double      dAccTime1;
public:
    virtual void update();
    virtual void render(HDC _dc);
public:
    void CreateMissileP0();
    void CreateMissileP1();
    void CreatereverseMissileP1();
    void CreaeteMisiileP2();

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
    ~CMonster();
};

