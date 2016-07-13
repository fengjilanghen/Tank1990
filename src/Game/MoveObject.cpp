#include "MoveObject.h"
#include <string>
using namespace std;

extern int g_WindowWidth, g_WindowHeight;

#define FASLE_RETURN(exp) if (!(exp)){ return; }

CMoveObject::CMoveObject()
	:CGameObject()
	, m_bAuto(false)
	, m_nLast(0)
	, m_Orientation(ORIEN_COUNT)
	, m_Velocity({0, 0})
	, m_Speed(0)
{
}

CMoveObject::~CMoveObject()
{
	Release();
}

bool CMoveObject::Init(bool bAuto, bool bUseAnimator, IRenderObject* pro, const sPoint& pos, const sSize& sz, int speed, int orient)
{
	bool res = super::Init(bUseAnimator, pro, pos, sz);
	SetSpeed(speed);
	SetAuto(bAuto);
	SetOrientation(orient);
	return res;
}

void CMoveObject::Release()
{

}

void CMoveObject::Update(float delta_time)
{
	super::Update(delta_time);

	if (IsAuto())
	{
		StupidAuto();
	}
}


void CMoveObject::Move(int orient)
{
	if (m_Orientation != orient)
	{
		SetOrientation(orient);
		return;
	}

	sPoint newPos = { m_Position.x + m_Velocity.x, m_Position.y + m_Velocity.y };
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

///////////////////////////////////////////////////////////////////
//
//	called by self
//
/////////////////////////////////////////////////////////////////////
void CMoveObject::StupidAuto()
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

void CMoveObject::SetOrientation(int orient)
{
	CAnimator *pAni = dynamic_cast<CAnimator*>(m_pRenderObject);
	if (!pAni) return;

	pAni->Stop();
	string action;
	switch (m_Orientation)
	{
	case LEFT:
		m_Velocity.x = -m_Speed;
		action = "left";
		break;
	case RIGHT:
		m_Velocity.x = m_Speed;
		action = "right";
		break;
	case UP:
		m_Velocity.y = -m_Speed;
		action = "up";
		break;
	case DOWN:
		m_Velocity.y = m_Speed;
		action = "down";
		break;
	default:
		ASSERT(false);
		return;
	}
	pAni->Start(action);
	m_Orientation = orient;
}