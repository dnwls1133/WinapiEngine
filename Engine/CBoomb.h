#pragma once
#include "CObject.h"
class CCollider;

class CBoomb :
    public CObject
{
private:
    float m_fAcc;
public:
    virtual void update();
    virtual void render(HDC _dc);

    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);

    CLONE(CBoomb);
public:
    CBoomb();
    ~CBoomb();
};

