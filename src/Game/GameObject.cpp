#include "GameObject.h"

CGameObject::CGameObject()
	: m_Position({ 0, 0 })
	, m_Size({ 0, 0 })
	, m_bReleaseFlag(false)
	, m_pRenderObject(NULL)
	, m_Animator()
	, m_bUseAnimator(false)
{
}

bool CGameObject::Init(bool bUseAnimator, IRenderObject *pro, const sPoint& pos /*= { 0, 0 }*/, const sSize& sz /*= { 0, 0 }*/)
{
	bool res = pro;
	m_bUseAnimator = bUseAnimator;
	m_pRenderObject = pro;
	m_Position = pos;
	m_Size = sz;

	if (bUseAnimator)
	{
		res = res && m_Animator.Init(dynamic_cast<CActionSet*>(pro));
	}
	return res;
}

void CGameObject::Update(float delta_time)
{
	if (m_bHasAnimator)
	{
		m_Animator.Update(delta_time);
	}
}

void CGameObject::Draw()
{
	sRect dest = { m_Position.x, m_Position.y, m_Position.x + m_Size.cx, m_Position.y + m_Size.cy };
	if (m_bHasAnimator)
	{
		m_pRenderObject->Draw(dest);
	}
	else
	{
		m_Animator.Draw(dest);
	}
}
