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
	
}

void CScene_Start::Enter()
{
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	
		// BackGround Object 추가
		CObject* pBackgroundObj = new CBackground;
		pBackgroundObj->SetPos(Vec2(vResolution.x / 2, vResolution.y / 2));
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
		int Monstercount = 4;
		float fMoveDist = 25.f;
		float fObjScale = 50.f;



		float fTerm = (vResolution.x - ((fMoveDist + fObjScale / 2) * 2)) / (float)(Monstercount - 1);
		CMonster* pMonsterObj = nullptr;
		for (int i = 0; i < Monstercount; ++i)
		{
			CMonster* pMonsterObj = new CMonster;
			pMonsterObj->SetPos(Vec2((fMoveDist + fObjScale / 2) + (float)i * fTerm, 50.f));
			pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
			pMonsterObj->SetMoveDistance(fMoveDist);
			pMonsterObj->SetScale(Vec2(50.f, 50.f));
			pMonsterObj->SetName(L"Monster");
			AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
		}

	
	
	// 충돌 지정
	// Player 그룹과 Monster 그룹간의 충돌체크
	CColliderMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PROJ_MONSTER);
	CColliderMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);

}


void CScene_Start::Exit()
{
	DeleteAll();
	CColliderMgr::GetInst()->Reset();
}
