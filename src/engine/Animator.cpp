#include "Animator.h"
#include "../Log/CLog.h"

#include <fstream>

#define ASSERT(express) 

using namespace std;

Animator::Animator()
: m_ImgName("")
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
void Animator::LoadConfig(const char* fname)
{
	ifstream xf(fname);
	if (!xf)
	{
		g_Log.write("Animator::LoadConfig failed, file name is '%s'", fname);
		return;
	}

	//xf.read
	m_State = STATE_PREPARED;
}


void Animator::BeginSet(const char* name, int counter_max)
{
	ASSERT(m_State == STATE_NONE);
	m_ImgName		= m_ImgName;
	m_CounterMax	= (counter_max <= 0 ? 1 : counter_max);
	m_State			= STATE_BEGINSET;
}

void Animator::EndSet()
{
	m_State = STATE_PREPARED;
}

void Animator::AddAction(const char* action, const FramesVec& frames)
{
	ASSERT(m_State == STATE_BEGINSET);
	ASSERT(frames.size() > 0)
	ASSERT(m_AllActions.find(action) == m_AllActions.end());
	m_AllActions[action].assign(frames.begin(), frames.end());
}

void Animator::AddAction(const char* action, sRect* frames, int num_frames)
{
	ASSERT(m_State == STATE_BEGINSET);
	ASSERT(m_AllActions.find(action) == m_AllActions.end());
	ASSERT(num_frames > 0);
	m_AllActions[action].assign(frames, frames + num_frames);
}

void Animator::Start(const char* action)
{
	ASSERT(m_State == STATE_STOP && find(action) != m_AllActions.end());
	m_CurAction = action;
	m_CurFrame	= 0;
	m_Counter	= 0;
	m_State = STATE_RUNNING;
}

void Animator::Stop()
{
	m_State = STATE_STOP;
}

void Animator::Pause()
{
	m_State = STATE_PAUSE;
}

void Animator::Resume()
{
	m_State = STATE_RUNNING;
}


void Animator::Reset()
{
	m_State			= STATE_NONE;
	m_ImgName		= "";
	m_CurAction		= "";
	m_CurFrame		= 0;
	m_Counter		= 0;
	m_CounterMax	= 0;
	m_AllActions.clear();
}


void Animator::Animate(int delta_time)
{
	if (m_State == STATE_RUNNING || m_State == STATE_PAUSE)
	{
		if (++m_Counter == m_CounterMax)
		{
			int frame_count = m_AllActions[m_CurAction].size();
			ASSERT(frame_count > 0);
			m_CurFrame = (m_CurFrame + 1) % frame_count;
			m_Counter = 0;
		}
	}
}

void Animator::Draw(int x, int y)
{
}


//////////////////////////////////////////////////////////////////////
//
//	functions called by self
//
//////////////////////////////////////////////////////////////////////


