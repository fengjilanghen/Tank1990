#include "SpriteAnimator.h"
#include "CLog.h"


CSpriteAnimator::CSpriteAnimator()
	:m_State(STATE_NONE)
	, m_CurAction("")
	, m_CurFrame(0)
	, m_Counter(0)
	, m_CounterMax(0)
{
	m_AllActions.clear();
}

//////////////////////////////////////////////////////////////////////
//
//	functions called by others
//
//////////////////////////////////////////////////////////////////////

bool CSpriteAnimator::BeginSet()
{
	if (m_State <= STATE_PREPARED)
	{
		Reset();
		return true;
	}
	return false;
}

void CSpriteAnimator::AddAction(const std::string& action, const FramesVec& frames)
{
	if (m_State > STATE_PREPARED
		|| action.empty()
		|| frames.size() == 0)
	{
		ASSERT(false);
		return;
	}

	m_AllActions[action].assign(frames.begin(), frames.end());
}

void CSpriteAnimator::AddAction(const std::string& action, const sRect* frames, int num_frames)
{
	if (m_State > STATE_PREPARED
		|| action.empty()
		|| num_frames <= 0
		|| frames == NULL)
	{
		ASSERT(false);
		return;
	}

	m_AllActions[action].assign(frames, frames + num_frames);
}

void CSpriteAnimator::Start(const std::string&  action)
{
	if (m_State != STATE_PREPARED || m_AllActions.find(action) == m_AllActions.end())
	{
		ASSERT(false);
		return;
	}
	m_CurAction = action;
	m_CurFrame	= 0;
	m_Counter	= 0;
	m_State = STATE_RUNNING;
}

void CSpriteAnimator::Stop()
{
	if (m_State > STATE_NONE)
	{
		m_State = STATE_PREPARED;
	}
}

void CSpriteAnimator::Pause()
{
	ASSERT(m_State == STATE_RUNNING);
	if (m_State == STATE_RUNNING)
	{
		m_State = STATE_PAUSE;
	}
}

void CSpriteAnimator::Resume()
{
	ASSERT(m_State == STATE_PAUSE);
	if (m_State == STATE_PAUSE)
	{
		m_State = STATE_RUNNING;
	}
}


void CSpriteAnimator::Animate(float delta_time)
{
	if (m_State == STATE_RUNNING || m_State == STATE_PAUSE)
	{
		if (++m_Counter == m_CounterMax)
		{
			ActionsMap::iterator it = m_AllActions.find(m_CurAction);
			ASSERT(it != m_AllActions.end());
			if (it != m_AllActions.end())
			{
				int frame_count = it->second.size();
				ASSERT(frame_count > 0);
				m_CurFrame = (m_CurFrame + 1) % frame_count;
				m_Counter = 0;
			}
		}
	}
}

sRect CSpriteAnimator::GetCurFrameRect()
{
	if (m_State == STATE_RUNNING || m_State == STATE_PAUSE)
	{
		ActionsMap::iterator it = m_AllActions.find(m_CurAction);
		ASSERT(it != m_AllActions.end());
		if (it != m_AllActions.end())
		{
			return it->second.at(m_CurFrame);
		}
	}
	ASSERT(false);
	return {0, 0, 0, 0};
}

//////////////////////////////////////////////////////////////////////
//
//	functions called by self
//
//////////////////////////////////////////////////////////////////////
void CSpriteAnimator::Reset()
{
	m_State = STATE_NONE;
	m_CurAction = "";
	m_CurFrame = 0;
	m_Counter = 0;
	m_CounterMax = 0;
	m_AllActions.clear();
}

