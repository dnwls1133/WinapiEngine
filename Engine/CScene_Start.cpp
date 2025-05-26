#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CBackground.h"

#include "CCore.h"

#include "CColliderMgr.h"
#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"

#include "CTexture.h"
#include "CCamera.h"

#include "AI.h"
#include "CState.h"
#include "CIdleState.h"
#include "CTraceState.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{
	CScene::update();
	
	if (KEY_TAP(KEY::ESC))
	{
		
		ChangeScene(SCENE_TYPE::TOOL);
	}

	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		CCamera::GetInst()->SetLookAt(vLookAt);
	}
	

}

void CScene_Start::Enter()
{
	Vec2 vResolution = CCore::GetInst()->GetResolution();


	// BackGround Object 추가
	CObject* pBackgroundObj = new CBackground;
	pBackgroundObj->SetPos(Vec2(vResolution.x / 3, vResolution.y / 2));
	pBackgroundObj->SetScale(Vec2(100.f, 100.f));
	pBackgroundObj->SetName(L"Background");
	AddObject(pBackgroundObj, GROUP_TYPE::BACKGROUND);

    
	// Player Object 추가
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	pObj->SetName(L"Player");
	AddObject(pObj, GROUP_TYPE::PLAYER);

	


	// Monster Object 추가
	int Monstercount = 1;
	float fObjScale = 50.f;

    AI* pAI = new AI;
    pAI->AddState(new CIdleState);
    //pAI->AddState(new CTraceState);

	CMonster* pMonsterObj = nullptr;
	for (int i = 0; i < Monstercount; ++i)
	{
		CMonster* pMonsterObj = new CMonster;
		pMonsterObj->SetPos(vResolution/2.f - Vec2(0.f,300.f));
		pMonsterObj->SetScale(Vec2(50.f, 50.f));
		pMonsterObj->SetName(L"Monster");
        pMonsterObj->SetAI(pAI);


		AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	}

    // 타일 로딩
    //LoadTile(L"Tile\\Start.tile");
	
	
	// 충돌 지정
	// Player 그룹과 Monster 그룹간의 충돌체크
	CColliderMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PROJ_MONSTER);
	CColliderMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);

	//Camera 지정
   
	CCamera::GetInst()->SetLookAt(vResolution /2.f);

    CCamera::GetInst()->FadeOut(1.f);
    CCamera::GetInst()->FadeIn(1.f);
 
    //Camera 효과 지정
   // CCamera::GetInst()->Fadeout(5.f);



}


void CScene_Start::Exit()
{
	DeleteAll();
	CColliderMgr::GetInst()->Reset();
}
