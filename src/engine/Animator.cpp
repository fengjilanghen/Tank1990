#include "Animator.h"
#include "XmlParser/XmlParser.h"
#include "SpriteFactory.h"
#include "CLog.h"


CAnimator::CAnimator()
	:m_State(STATE_NONE)
	, m_CurAction("")
	, m_CurFrame(0)
	, m_Counter(0)
	, m_pActionSet(NULL)
{
}

//////////////////////////////////////////////////////////////////////
//
//	functions called by others
//
//////////////////////////////////////////////////////////////////////
bool CAnimator::Init(CActionSet* pas)
{
	if (pas)
	{
		m_pActionSet = pas;
		m_State = STATE_PREPARED;
		return true;
	}
	ASSERT(false);
	return false;
}

void CAnimator::Release()
{
	m_State = STATE_NONE;
	m_CurAction = "";
	m_CurFrame = 0;
	m_Counter = 0;
	m_pActionSet = NULL;
}

void CAnimator::Update(float delta_time)
{
	if (m_State == STATE_RUNNING || m_State == STATE_PAUSE)
	{
		if (++m_Counter == m_pActionSet->GetCounterMax())
		{
			int frame_count = m_pActionSet->GetFrameCount(m_CurAction);
			ASSERT(frame_count > 0);
			if (frame_count > 0)
			{
				m_CurFrame = (m_CurFrame + 1) % frame_count;
				m_Counter = 0;
			}
		}
	}
}

void CAnimator::Draw(const sRect& dest)
{
	if (m_State <= STATE_PREPARED)
		return;

	sRect src = m_pActionSet->GetRect(m_CurAction, m_CurFrame);
	m_pActionSet->Draw(src, dest);
}

void CAnimator::Start(const std::string&  action)
{
	if (m_State != STATE_PREPARED || !m_pActionSet->HasAction(action))
	{
		ASSERT(false);
		return;
	}
	m_CurAction = action;
	m_CurFrame = 0;
	m_Counter = 0;
	m_State = STATE_RUNNING;
}

void CAnimator::Stop()
{
	if (m_State > STATE_NONE)
	{
		m_State = STATE_PREPARED;
	}
}

void CAnimator::Pause()
{
	ASSERT(m_State == STATE_RUNNING);
	if (m_State == STATE_RUNNING)
	{
		m_State = STATE_PAUSE;
	}
}

void CAnimator::Resume()
{
	ASSERT(m_State == STATE_PAUSE);
	if (m_State == STATE_PAUSE)
	{
		m_State = STATE_RUNNING;
	}
}
