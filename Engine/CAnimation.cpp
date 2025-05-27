#include "pch.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CObject.h"

#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"


CAnimation::CAnimation()
	: m_pAnimator(nullptr)
	, m_pTex(nullptr)
	, m_iCurFrm(0)
	, m_fAccTime(0.f)
	, m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::update()
{
	if (m_bFinish)
		return;

	m_fAccTime += fDT;

	if (m_fAccTime > m_vecFrm[m_iCurFrm].fDuration)
	{

		++m_iCurFrm;
		
		if (m_vecFrm.size() <= m_iCurFrm)
		{
			m_iCurFrm = -1;
			m_bFinish = true;
			m_fAccTime = 0;
			return;
		}

		m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fDuration;
		
	}
}

void CAnimation::render(HDC _dc)
{
	if (m_bFinish)
		return;
	CObject* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(vPos);
	vRenderPos += m_vecFrm[m_iCurFrm].vOffset; // Ovject Position Offset만큼 추가 이동위치


	
	int iWidith = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();


	//BitBlt(_dc, int(vPos.x - (float)(iWidith / 2))
	//	, int(vPos.y - (float)(iHeight / 2))
	//	, iWidith, iHeight
	//	, m_pTex->GetDC()
	//	, 0, 0, SRCCOPY);

	
	
	TransparentBlt(_dc
		, (int)(vRenderPos.x - m_vecFrm[m_iCurFrm].vSlicce.x / 2.f)
		, (int)(vRenderPos.y - m_vecFrm[m_iCurFrm].vSlicce.y / 2.f)
		, (int)(m_vecFrm[m_iCurFrm].vSlicce.x )
		, (int)(m_vecFrm[m_iCurFrm].vSlicce.y )
		, m_pTex->GetDC()
		, (int)m_vecFrm[m_iCurFrm].vLT.x
		, (int)m_vecFrm[m_iCurFrm].vLT.y
		, (int)m_vecFrm[m_iCurFrm].vSlicce.x
		, (int)m_vecFrm[m_iCurFrm].vSlicce.y
		, RGB(255,0,255));
}

void CAnimation::Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;

	tAnimFrm frm = {};
	for (int i = 0; i < _iFrameCount; ++i)
	{
		frm.fDuration = _fDuration;
		frm.vSlicce = _vSliceSize;
		frm.vLT = _vLT + _vStep * i;
		frm.vOffset = Vec2(0.f, 0.f);
		m_vecFrm.push_back(frm);
	}
}

void CAnimation::Save(const wstring& _strRelativePath)
{
    wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
    strFilePath += _strRelativePath;

    FILE* pFile = nullptr;
    _wfopen_s(&pFile,strFilePath.c_str(),L"wb");

    assert(pFile);

   

    //Animation 의 이름을 저장한다. ( 데이터 직렬화 )
    fprintf(pFile, "[Animation Name]\n");
    string strName = string(m_strName.begin(), m_strName.end());
    fprintf(pFile, strName.c_str());
    //SaveWString(m_strName, pFile);
    fprintf(pFile, "\n");


    // Animation 이 사용하는 텍스쳐
    fprintf(pFile, "[Texture Name]\n");
    strName = string(m_pTex->GetKey().begin(), m_pTex->GetKey().end());
    fprintf(pFile, strName.c_str());
    fprintf(pFile, "\n");

    fprintf(pFile, "[Texture Path]\n");
    strName = string(m_pTex->GetRelativePath().begin(), m_pTex->GetRelativePath().end());
    fprintf(pFile, strName.c_str());
    fprintf(pFile, "\n");
   

    // 프레임 개수
    fprintf(pFile, "[Frame Count]\n");
    fprintf(pFile, "%d\n", m_vecFrm.size());

    for (size_t i = 0; i < m_vecFrm.size(); ++i)
    {
        fprintf(pFile, "[Frame Index]\n");
        fprintf(pFile, "%d\n", (int)i);

        fprintf(pFile, "[Left Top]\n");
        fprintf(pFile, "%d,%d\n", (int)m_vecFrm[i].vLT.x, (int)m_vecFrm[i].vLT.y);

        fprintf(pFile, "[Slice Size]\n");
        fprintf(pFile, "%d,%d\n", (int)m_vecFrm[i].vSlicce.x, (int)m_vecFrm[i].vSlicce.y);

        fprintf(pFile, "[Offset]\n");
        fprintf(pFile, "%d,%d\n", (int)m_vecFrm[i].vOffset.x, (int)m_vecFrm[i].vOffset.y);

        fprintf(pFile, "[Duration]\n");
        fprintf(pFile, "%f\n", (int)m_vecFrm[i].fDuration);

        fprintf(pFile, "\n\n");
    }

   
  

   fclose(pFile);
}

void CAnimation::Load(const wstring& _strRelativePath)
{
    wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
    strFilePath += _strRelativePath;

    FILE* pFile = nullptr;
    _wfopen_s(&pFile, strFilePath.c_str(), L"rb");
    assert(pFile);

    // Animaiton 이름 읽기
    LoadWString(m_strName, pFile);
    // 텍스쳐
    wstring strTexKey,strTexPath;
    LoadWString(strTexKey, pFile);
    LoadWString(strTexPath, pFile);
    m_pTex = CResMgr::GetInst()->LoadTexture(strTexKey,strTexPath);



    //프레임 개수
    size_t iFrameCount = 0;
    fread(&iFrameCount, sizeof(size_t), 1, pFile);

    // 모든 프레임 정보
    m_vecFrm.resize(iFrameCount);
    fread(m_vecFrm.data(), sizeof(tAnimFrm), iFrameCount, pFile);



    fclose(pFile);
}
