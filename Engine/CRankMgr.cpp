#include "pch.h"
#include "CRankMgr.h"

CRankMgr::CRankMgr()
{
    
}

CRankMgr::~CRankMgr()
{

}

void CRankMgr::LoadRanking()
{
    FILE* pFile = nullptr;
    _wfopen_s(&pFile, L"Ranking.txt", L"rt");
    assert(pFile);

    wchar_t szLine[128];
    m_vecGameRankings.clear();

    while (fgetws(szLine, 128, pFile))
    {
        if (wcsncmp(szLine, L"[Record]", 8) == 0)
        {
            int score = 0;
            std::wstring date;

            fgetws(szLine, 128, pFile); // [Score]
            fgetws(szLine, 128, pFile);
            score = _wtoi(szLine);

            fgetws(szLine, 128, pFile); // [Date]
            fgetws(szLine, 128, pFile);
            date = szLine;
            if (!date.empty() && date.back() == L'\n')
                date.pop_back();

            m_vecGameRankings.emplace_back(score, date);
        }
    }

    fclose(pFile);
}

void CRankMgr::SaveRanking()
{
    FILE* pFile = nullptr;
    _wfopen_s(&pFile, L"Ranking.txt", L"wt");
    assert(pFile);

    fwprintf(pFile, L"[Ranking_Count]\n");
    fwprintf(pFile, L"%d\n\n", (int)m_vecGameRankings.size());

    for (const auto& rec : m_vecGameRankings) {
        fwprintf(pFile, L"[Record]\n");
        fwprintf(pFile, L"[Score]\n%d\n", rec.Score);
        fwprintf(pFile, L"[Date]\n%s\n\n", rec.DateTime.c_str());
    }

    fclose(pFile);
}

void CRankMgr::AddRanking()
{
    m_vecGameRankings.push_back(CurrentRanking);

    std::sort(m_vecGameRankings.begin(), m_vecGameRankings.end(),
        [](const RankingData& a, const RankingData& b) {
            return a.Score > b.Score; // 내림차순 정렬
        });

    if (m_vecGameRankings.size() > 5) {
        m_vecGameRankings.resize(5); // 상위 5개만 남김
    }
}
