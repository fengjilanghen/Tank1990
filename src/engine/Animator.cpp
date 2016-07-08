#include "Animator.h"
#include "XmlParser/XmlParser.h"
#include "SpriteFactory.h"
#include "CLog.h"


CAnimator::CAnimator()
	:m_State(STATE_NONE)
	, m_CurAction("")
	, m_CurFrame(0)
	, m_Counter(0)
	, m_CounterMax(0)
	, m_pSprite(NULL)
{
	m_AllActions.clear();
}

//////////////////////////////////////////////////////////////////////
//
//	functions called by others
//
//////////////////////////////////////////////////////////////////////
bool CAnimator::Init(const std::string& fname)
{
	PXMLELEMENT pRoot = XmlParser::ParseFile(fname.c_str());
	ASSERT_RETURN_FALSE(pRoot && pRoot->tag == "Animator");

	// 解析Animator的属性
	AttribsPtrUMap::iterator it;

	std::string str;
	int counter_max = 1;

	getAttribValue(str, pRoot->attribs, "img");
	ASSERT_RETURN_FALSE(!str.empty());
	m_pSprite = CSpriteFactory::GetInstancePtr()->CreateSprite(str);
	ASSERT_RETURN_FALSE(!m_pSprite || !m_pSprite->Init(str))

	getAttribValue(str, pRoot->attribs, "counter_max");
	if (str.empty()) return false;
	counter_max = std::atoi(str.c_str());

	SetCounterMax(counter_max);


	for (ChildrenPtrVec::iterator it = pRoot->children.begin(); it != pRoot->children.end(); ++it)
	{
		//解析各Action的属性
		AttribsPtrUMap::const_iterator ait;
		const AttribsPtrUMap& apm = (*it)->attribs;

		std::string name;
		int total = 0;

		getAttribValue(name, apm, "name");
		ASSERT_RETURN_FALSE(!name.empty());

		getAttribValue(str, apm, "total");
		ASSERT_RETURN_FALSE(!str.empty());
		total = std::atoi(str.c_str());
		ASSERT(total > 0);

		// 解析frame
		CAnimator::FramesVec frames;
		for (int i = 0; i < total; ++i)
		{
			PXMLELEMENT frame = (*it)->children.at(i);
			if (!frame) return false;

			const AttribsPtrUMap& frame_apm = frame->attribs;
			sRect rect;

			getAttribValue(str, frame_apm, "x");
			ASSERT_RETURN_FALSE(!str.empty());
			rect.left = std::atoi(str.c_str());

			getAttribValue(str, frame_apm, "y");
			ASSERT_RETURN_FALSE(!str.empty());
			rect.top = std::atoi(str.c_str());

			getAttribValue(str, frame_apm, "w");
			ASSERT_RETURN_FALSE(!str.empty());
			rect.right = rect.left + std::atoi(str.c_str());


			getAttribValue(str, frame_apm, "h");
			ASSERT_RETURN_FALSE(!str.empty());
			rect.bottom = rect.top + std::atoi(str.c_str());

			frames.push_back(rect);
		}

		AddAction(name, frames);
	}
	m_State = STATE_PREPARED;
	return true;
}

void CAnimator::Release()
{
	m_State = STATE_NONE;
	m_CurAction = "";
	m_CurFrame = 0;
	m_Counter = 0;
	m_CounterMax = 0;
	m_AllActions.clear();
	m_pSprite = NULL;
}

void CAnimator::Update(float delta_time)
{
	if (m_State == STATE_RUNNING || m_State == STATE_PAUSE)
	{
		if (++m_Counter == m_CounterMax)
		{
			ActionsUMap::iterator it = m_AllActions.find(m_CurAction);
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

void CAnimator::Draw()
{

}

void CAnimator::Start(const std::string&  action)
{
	if (m_State != STATE_PREPARED || m_AllActions.find(action) == m_AllActions.end())
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

//////////////////////////////////////////////////////////////////////
//
//	functions called by self
//
//////////////////////////////////////////////////////////////////////

void CAnimator::AddAction(const std::string& action, const FramesVec& frames)
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

void CAnimator::AddAction(const std::string& action, const sRect* frames, int num_frames)
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

const sRect& CAnimator::GetCurFrameRect()
{
	ActionsUMap::iterator it = m_AllActions.find(m_CurAction);
	if (it != m_AllActions.end())
	{
		return it->second.at(m_CurFrame);
	}
	ASSERT(false);
	return{ 0, 0, 0, 0 };
}


void CAnimator::getAttribValue(std::string &o_value, const AttribsPtrUMap& i_apm, const std::string& i_key)
{
	o_value.clear();
	AttribsPtrUMap::const_iterator ait = i_apm.find(i_key);
	ASSERT(ait != i_apm.end());

	if (ait != i_apm.end())
	{
		o_value = ait->second;
		ASSERT(!o_value.empty())
	}
}

