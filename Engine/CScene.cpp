#include "pch.h"
#include "CScene.h"

#include "CResMgr.h"
#include "CPathMgr.h"

#include "CObject.h"
#include "CTile.h"

#include "CCamera.h"
#include "CCore.h"

CScene::CScene()
	: is_change(false)
	, m_iTileX(0)
	, m_iTileY(0)
{
}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			// m_arrObj[i] 그룹 벡터의 j 물체 삭제
			if (nullptr != m_arrObj[i][j])
			{
				delete m_arrObj[i][j];
			}
			
		}
	}
}

void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			// m_arrObj[i] 그룹 벡터의 j 물체 업데이트
			if (!m_arrObj[i][j]->IsDead())
			{
				m_arrObj[i][j]->update();
			}
		
		}
	}
}

void CScene::finalupdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			// m_arrObj[i] 그룹 벡터의 j 물체 삭제
			m_arrObj[i][j]->finalupdate();
		}
	}
}

void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
        if ((UINT)GROUP_TYPE::TILE == i)
        {
            render_tile(_dc);
            continue;
        }
		vector<CObject*>::iterator iter = m_arrObj[i].begin();
        

		for (iter; iter != m_arrObj[i].end();)
		{
			
			if (!(*iter)->IsDead())
			{
				(*iter)->render(_dc);
				++iter;
			}
			else
			{
				
				iter = m_arrObj[i].erase(iter);
			}
		}
	}
}

void CScene::render_tile(HDC _dc)
{
    const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

    Vec2 vCamLook = CCamera::GetInst()->GetLookAt();
    Vec2 vResolution = CCore::GetInst()->GetResolution();
    Vec2 vLeftTop = vCamLook - vResolution;

    int iTileSize = TILE_SIZE;

    int iLTCol = (int)vLeftTop.x / iTileSize;
    int iLTRow = (int)vLeftTop.y / iTileSize;

    int LTiIdx = m_iTileX * iLTRow + iLTCol;

    int iClientWidth = (int)vResolution.x / iTileSize;
    int iClientHeight = (int)vResolution.y / iTileSize;

    for (int iCurRow = iLTRow; iCurRow < (iLTRow + iClientWidth); ++iCurRow)
    {
        for (int iCurCol = iLTCol; iCurCol < (iLTCol + iClientWidth); ++iCurCol)
        {
            if (iCurCol < 0 || m_iTileX <= iCurCol
                || iCurRow < 0 || m_iTileY <= iCurRow)
            {
                continue;
            }


            int iIdx = (m_iTileX * iCurRow) + iCurCol;



            vecTile[iIdx]->render(_dc);
        }
    }
}


void CScene::DeleteGroup(GROUP_TYPE _eTarget)
{
	Safe_Delete_Vec<CObject*>(m_arrObj[(UINT)_eTarget]);
}

void CScene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}

void CScene::CreateTile(UINT _iXCount, UINT _iYCount)
{
    DeleteGroup(GROUP_TYPE::TILE);

	m_iTileX = _iXCount;
	m_iTileY = _iYCount;

	CTexture* pTileTex = CResMgr::GetInst()->LoadTexture(L"Tile", L"texture\\tile\\Tile_0.bmp");
	for (UINT i = 0; i < _iXCount; ++i)
	{
		for (UINT j = 0; j < _iYCount; ++j)
		{
			CTile* pTile = new CTile;
			pTile->SetPos(Vec2((float)(j * TILE_SIZE), (float)(i * TILE_SIZE)));
			pTile->SetTexture(pTileTex);
			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
}

void CScene::LoadTile(const wstring& _strRelativePath)
{
    wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
    strFilePath += _strRelativePath;
    // 커널 오브젝트
    FILE* pFile = nullptr;
    _wfopen_s(&pFile, strFilePath.c_str(), L"rb");
    assert(pFile);

    UINT xCount = 0;
    UINT yCount = 0;
    fread(&xCount, sizeof(UINT), 1, pFile);
    fread(&yCount, sizeof(UINT), 1, pFile);

    // 불러온 개수에 맞게 EmptyTile 들 ㄷ만들어주기
    CreateTile(xCount, yCount);

    // 만들어진 타일 개별로 필요한 정보를 저장함
    const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

    for (size_t i = 0; i < vecTile.size(); ++i)
    {
        ((CTile*)vecTile[i])->Load(pFile);
    }
    fclose(pFile);
}
