#include "Level1.h"
#include "../Graphics.h"

bool CLevel1::Load()
{
	y = 0;
	yspeed = 0.0f;
	return true;
}

void CLevel1::Unload()
{
	y = 0;
	yspeed = 0.0f;
}


void CLevel1::Update()
{

	yspeed += 1.0f;
	y += yspeed;
	if (y > 600)
	{
		y = 600;
		yspeed = -30.f;
	}
}

void CLevel1::Render()
{
	g_Graphics.ClearScreen(0, 0, 0);
	g_Graphics.DrawCircle(255.f, y, 100.f, 60.f);
}