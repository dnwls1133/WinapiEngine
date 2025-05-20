#pragma once

// 전방 선언
class CObject;
class CPlayer;
class CScene
{
private: // 자식 클래스에게 멤버함수 권한 부여
	vector<CObject*> m_arrObj[(UINT)GROUP_TYPE::END]; // 오브젝트를 저장 및 관리할 벡터를 그룹 개수만큼 선언
	wstring			 m_strName; // Scene 이름

	UINT			 m_iTileX;  // 타일 가로 개수
	UINT			 m_iTileY;  // 타일 세로 개수


	bool			 is_change;
public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }
	UINT GetTileX() { return m_iTileX; }
	UINT GetTileY() { return m_iTileY; }
	
	
	
	
	
	
	void SetChange() 
	{
		is_change = true;
	}
	bool GetChange() { return is_change; }
	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);

	virtual void Enter() = 0; // 해당 Scene 에 진입 시 호출
	virtual void Exit() = 0; // 해당 Scenen 에 탈출 시 호출
public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; }
	
	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();
	
	void CreateTile(UINT _iXCount, UINT _iYCount);
	vector<CObject*>& GetUIGroup() { return m_arrObj[(UINT)GROUP_TYPE::UI]; }
	
public:
	CScene();
	virtual ~CScene(); // 상속하는 순간 소멸자 가상함수 만들어주어야합니다.
	
};

