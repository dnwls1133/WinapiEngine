#pragma once
#include "CObject.h"


struct tMonInfo
{
    float           fSpeed;         // 속도
    float           fHP;            // 체력
    float           fRecogRange;    // 인지 범위
    float           fAttRange;      // 공격 범위
    float           fAtt;           // 공격력
    MISSILE_PTRN    ePattern;        // 공격 패턴
};






class AI;
class CTexture;

class CMonster :
    public CObject
{
protected:
   
    tMonInfo    m_tInfo;
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
    void SetSpeed(float _f) { m_tInfo.fSpeed = _f;}
    float GetSpeed() { return m_tInfo.fSpeed; }
    void SetAI(AI* _AI);
    const tMonInfo& GetInfo() { return m_tInfo; }
    void SetAnim(MON_TYPE eType);

private:
    void SetMonInfo(const tMonInfo& _info)
    {
        m_tInfo = _info;
    }

public:

    CLONE(CMonster);
public:
    CMonster();
    virtual ~CMonster();

    friend class CMonFactory;
};

