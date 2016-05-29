#pragma once

#include "GameLevel.h"
#include <vector>


class CGameController
{
private:
	static CGameLevel*			m_pCurrentLevel;
	static bool					m_bLoading;

public:
	static void LoadInitialLevel(CGameLevel* lev);
	static void SwitchLevel(CGameLevel* lev);
	static void Render();
	static void Update(float delta_time);
	static void KeyEvent(int key, bool pressed);
private:
	CGameController() = delete;
};