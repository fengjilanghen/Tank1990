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
	ID2D1Bitmap *bm;
	g_Graphics.LoadBitmapFromFile(L"E:/github/Tank1990/bin/pic/tank.png", &bm);
	g_Graphics.Draw(bm, D2D1::RectF(0, 0, 400, 400));
	bm->Release();
}