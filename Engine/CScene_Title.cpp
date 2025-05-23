#include "pch.h"
#include "CScene_Title.h"

CScene_Title::CScene_Title()
    : m_pBackground(nullptr)
    , m_pLogo(nullptr)
    , m_pMessage(nullptr)
{
}

CScene_Title::~CScene_Title()
{
  
}

void CScene_Title::Enter()
{
    m_pBackground = new CTitleBackground();
}

void CScene_Title::update()
{
    

}

void CScene_Title::Exit()
{
    if (nullptr != m_pBackground)
        delete m_pBackground;

    if (nullptr != m_pLogo)
        delete m_pLogo;

    if (nullptr != m_pMessage)
        delete m_pMessage;
}
