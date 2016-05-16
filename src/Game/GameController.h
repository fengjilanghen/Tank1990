#pragma once

#include "GameLevel.h"

class CGameController
{
private:
	static CGameLevel*	m_pCurrentLevel;
	static bool			m_bLoading;

public:
	static void LoadInitialLevel(CGameLevel* lev);
	static void SwitchLevel(CGameLevel* lev);
	static void Render();
	static void Update();

private:
	CGameController() = delete;
};