#include "GameController.h"

CGameLevel*	CGameController::m_pCurrentLevel	= nullptr;
bool		CGameController::m_bLoading			= false;

static const int KEY_COUNT = 128;

void CGameController::LoadInitialLevel(CGameLevel* lev)
{
	m_bLoading = true;
	m_pCurrentLevel = lev;
	m_pCurrentLevel->Load();
	m_bLoading = false;
	
}

void CGameController::SwitchLevel(CGameLevel* lev)
{
	m_bLoading = true;
	m_pCurrentLevel->Unload();
	m_pCurrentLevel = lev;
	m_pCurrentLevel->Load();
	m_bLoading = false;
}

void CGameController::Update(float delta_time )
{
	if (m_bLoading) return;
	m_pCurrentLevel->Update();

}

void CGameController::Render()
{
	if (m_bLoading) return;
	m_pCurrentLevel->Render();
}

void CGameController::KeyEvent(int key, bool pressed)
{
	if (m_pCurrentLevel)
		m_pCurrentLevel->KeyEvent(key, pressed);
}