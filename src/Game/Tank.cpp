#include "Tank.h"

extern int g_WindowWidth, g_WindowHeight;

#define FASLE_RETURN(exp) if (!(exp)){ return; }

CTank::CTank()
	:CGameObject({ 0, 0 }, { 0, 0 }, { 0, 0 })
	, m_bAuto(false)
	, m_nLast(0)
{
}

CTank::~CTank()
{
	Release();
}

bool CTank::Init(bool bAuto, const char* fname, const sPoint& pos, const sSize& sz, int speed, int orient)
{
	if (!m_AniSprite.Init(CSprite::ST_ANIMATOR, fname)) return false;
	SetAuto(bAuto);
	SetPosition(pos);
	SetSize(sz);
	SetSpeed(speed);

	CSpriteAnimator* pAni = GetAnimator();
	if (!pAni) return false;
	Move(orient);
	return true;
}

void CTank::Release()
{

}

void CTank::Update(float delta_time)
{
	CSpriteAnimator* pAni = GetAnimator();
	if (pAni)
	{
		pAni->Animate(delta_time);
	}

	if (IsAuto())
	{
		StupidAuto();
	}
}


void CTank::Move(int orientation)
{
	CSpriteAnimator* pAni = GetAnimator();
	if(!pAni) return;

	sPoint off = { 0, 0 };
	switch (orientation)
	{
	case LEFT:
	{
		pAni->Stop();
		pAni->Start("left");
		if (m_Orientation == orientation)
			off.x = -m_Speed;

		m_Orientation = orientation;
	}break;
	case RIGHT:
	{
		pAni->Stop();
		pAni->Start("right");
		if (m_Orientation == orientation)
			off.x = m_Speed;
		m_Orientation = orientation;
	}break;
	case UP:
	{
		pAni->Stop();
		pAni->Start("up");
		if (m_Orientation == orientation)
			off.y = -m_Speed;
		m_Orientation = orientation;
	}break;
	case DOWN:
	{
		pAni->Stop();
		pAni->Start("down");
		if (m_Orientation == orientation)
			off.y = m_Speed;
		m_Orientation = orientation;
	}break;
	default:
		ASSERT(false);
		break;
	}

	sPoint newPos = { m_Position.x + off.x, m_Position.y + off.y };
	if (newPos.x <= 0)
		newPos.x = 0;

	if (newPos.x >= g_WindowWidth - m_Size.cx)
		newPos.x = g_WindowWidth - m_Size.cx;

	if (newPos.y <= 0)
		newPos.y = 0;

	if (newPos.y >= g_WindowHeight - m_Size.cy)
		newPos.y = g_WindowHeight - m_Size.cy;

	m_Position = newPos;
}


void CTank::Draw()
{
	sRect dest = { m_Position.x, m_Position.y, m_Position.x + m_Size.cx, m_Position.y + m_Size.cy };
	m_AniSprite.Draw(dest);
}

///////////////////////////////////////////////////////////////////
//
//	called by self
//
/////////////////////////////////////////////////////////////////////
void CTank::StupidAuto()
{
	if (m_nLast-- == 0)
	{
		int ori = rand() % ORIEN_COUNT;
		m_nLast = rand() % 5;
		Move(ori);
		return;
	}
	Move(m_Orientation);
}