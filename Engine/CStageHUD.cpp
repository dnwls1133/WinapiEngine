#include "pch.h"
#include "CStageHUD.h"

#include "CPathMgr.h"
#include "CRankMgr.h"

inline const std::wstring ToString(int score)
{
    std::wstring result;
    int count = 0;

    if (score == 0)
        return L"0";

    while (score > 0) {
        if (count > 0 && count % 3 == 0)
            result = L"'" + result;

        result = std::to_wstring(score % 10) + result;
        score /= 10;
        ++count;
    }

    return result;
}



inline const RankingData& GetFirstRanking()
{
    return CRankMgr::GetInst()->GetFirstRanking();
}

inline RankingData& GetCurrentRanking()
{
    return CRankMgr::GetInst()->CurrentRanking;
}

inline const RankingData& GetRanking(size_t index_)
{
    return CRankMgr::GetInst()->GetRanking(index_);
}


CStageHUD::CStageHUD()
    :CUI(false)
{
    m_fontPath = CPathMgr::GetInst()->GetContentPath();
    m_fontPath += L"font\\BMDOHYEON_ttf.ttf";

    // 폰트를 현재 프로세스에 등록
    AddFontResourceEx(m_fontPath.c_str(), FR_PRIVATE, nullptr);

    // 원하는 폰트 이름과 크기 설정
    LOGFONT lf = {};
    lf.lfHeight = -16; // 글자 크기
    lf.lfWeight = FW_NORMAL;
    wcscpy_s(lf.lfFaceName, L"YourFontName"); // TTF 내에 정의된 폰트 이름

    m_hFont = CreateFontIndirect(&lf);
}

CStageHUD::~CStageHUD()
{
    if (m_hFont)
        DeleteObject(m_hFont);

    if (!m_fontPath.empty())
        RemoveFontResourceEx(m_fontPath.c_str(), FR_PRIVATE, nullptr);
}

void CStageHUD::update()
{
    // 
}

void CStageHUD::render(HDC hdc)
{
    if (!m_bIsActive)
        return;

    if (!m_hFont)
        return;

    auto currentScore = CRankMgr::GetInst()->CurrentRanking.Score;
    auto hiScore = CRankMgr::GetInst()->GetFirstRanking().Score;
    // 텍스트 생성
    std::wstring str = L"SCORE: " + ToString(currentScore) + L"  HI-SCORE: " + ToString(hiScore);

    HFONT hOldFont = (HFONT)SelectObject(hdc, m_hFont);
    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, RGB(255, 255, 255));

    int bgX = (1280 - 540) / 2;
    int y = 20;
    TextOut(hdc, bgX + 20, y, str.c_str(), (int)str.length());

    SelectObject(hdc, hOldFont);
}
