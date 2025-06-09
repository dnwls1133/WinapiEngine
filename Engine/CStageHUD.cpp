#include "pch.h"
#include "CStageHUD.h"

#include "CPathMgr.h"
#include "CRankMgr.h"

CStageHUD::CStageHUD()
    :CUI(false)
{
    // m_fontPath = CPathMgr::GetInst()->GetContentPath();
    // m_fontPath += L"font\\BMDOHYEON_ttf.ttf";

    // 폰트를 현재 프로세스에 등록
    AddFontResourceEx(L"font\\BMHANNAPro.ttf", FR_PRIVATE, nullptr);
    AddFontResourceEx(L"font\\BMHANNAAir.ttf", FR_PRIVATE, nullptr);

    m_hLabelFont = CreateFont(
        -15,            // height (픽셀 기준, 숫자를 키우면 글자가 커짐)
        0,             // width (0이면 자동)
        0, 0,          // escapement, orientation
        FW_BOLD,       // 굵기
        FALSE, FALSE, FALSE, // italic, underline, strikeout
        HANGUL_CHARSET,// charset
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE,
        L"배달의민족 한나체 Pro"    // 글꼴 이름
    );

    m_hValueFont = CreateFont(
        -10,            // height (픽셀 기준, 숫자를 키우면 글자가 커짐)
        0,             // width (0이면 자동)
        0, 0,          // escapement, orientation
        FW_BOLD,       // 굵기
        FALSE, FALSE, FALSE, // italic, underline, strikeout
        HANGUL_CHARSET,// charset
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE,
        L"배달의민족 한나체 Air"    // 글꼴 이름
    );
}

CStageHUD::~CStageHUD()
{
    // if (m_hFont)
    //     DeleteObject(m_hFont);
    // 
    // if (!m_fontPath.empty())
    //     RemoveFontResourceEx(m_fontPath.c_str(), FR_PRIVATE, nullptr);
}

void CStageHUD::update()
{
    // 
}

void CStageHUD::render(HDC hdc)
{
    if (!m_bIsActive)
        return;

    // if (!m_hFont)
    //     return;

   // auto currentScore = CRankMgr::GetInst()->CurrentRanking.Score;
   // auto hiScore = CRankMgr::GetInst()->GetFirstRanking().Score;
   // // 텍스트 생성
   // std::wstring str = L"SCORE: " + ToString(currentScore) + L"  HI-SCORE: " + ToString(hiScore);
   // 
   // HFONT hOldFont = (HFONT)SelectObject(hdc, m_hFont);
   // SetBkMode(hdc, TRANSPARENT);
   // SetTextColor(hdc, RGB(255, 255, 255));
   // 
   // int bgX = (1280 - 540) / 2;
   // int y = 20;
   // TextOut(hdc, bgX + 20, y, str.c_str(), (int)str.length());
   // 
   // SelectObject(hdc, hOldFont);
}
