#include "ActionSet.h"
#include "SpriteFactory.h"

CActionSet::CActionSet()
: m_ASName()
, m_CounterMax(1)
{
	m_AllActions.clear();
}

bool CActionSet::Init(const std::string& asname, const std::string& img, int counter_max)
{
	m_ASName = asname;
	m_pSprite = CSpriteFactory::GetInstancePtr()->Create(img);
	m_CounterMax = (counter_max <= 0 ? 1 : counter_max);
	return m_pSprite;
}

void CActionSet::Draw(const sRect& src, const sRect& dest)
{
	if (m_pSprite)
	{
		m_pSprite->Draw(src, dest);
	}
}


void CActionSet::AddAction(const std::string& action, const FramesVec& frames)
{
	if (action.empty()
		|| frames.size() == 0)
	{
		ASSERT(false);
		return;
	}

	m_AllActions[action].assign(frames.begin(), frames.end());
	
}
void CActionSet::AddAction(const std::string& action, const sRect* frames, int num_frames)
{
	if (action.empty()
		|| num_frames <= 0
		|| frames == NULL)
	{
		ASSERT(false);
		return;
	}

	m_AllActions[action].assign(frames, frames + num_frames);
}

int CActionSet::GetFrameCount(const std::string& action)const
{
	ActionsUMap::const_iterator it = m_AllActions.find(action);
	if (it != m_AllActions.end())
	{
		return it->second.size();
	}
	return -1;
}

const sRect& CActionSet::GetRect(const std::string& action, int frame) const
{
	ActionsUMap::const_iterator it = m_AllActions.find(action);
	if (it != m_AllActions.end())
	{
		return it->second.at(frame);
	}
	ASSERT(false);
	return{ 0, 0, 0, 0 };
}