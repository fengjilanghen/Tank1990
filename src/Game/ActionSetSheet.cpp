#include "ActionSetSheet.h"
#include "XmlParser.h"
#include "SpriteFactory.h"

CActionSetSheet::CActionSetSheet()
{
	m_ActionSets.clear();
}

CActionSetSheet::~CActionSetSheet()
{
	Unload();
}

//////////////////////////////////////////////////////////////////////
//
//	functions called by others
//
//////////////////////////////////////////////////////////////////////
bool CActionSetSheet::Load(const std::string& fname)
{
	PXMLELEMENT pRoot = XmlParser::ParseFile(fname.c_str());
	ASSERT_RETURN_FALSE(pRoot && pRoot->tag == "Sheet");


	for (ChildrenPtrVec::iterator it1 = pRoot->children.begin(); it1 != pRoot->children.end(); ++it1)
	{	
		// 解析各Animator的属性
		PXMLELEMENT pAnimator = (*it1);
		ASSERT_RETURN_FALSE(pAnimator && pAnimator->tag == "Animator");
		const AttribsPtrUMap& animator_apm = pAnimator->attribs;

		std::string str, name;
		CActionSet* pAS = NULL;

		getAttribValue(name, animator_apm, "name");
		ASSERT_RETURN_FALSE(!name.empty() && (pAS = AddActionSet(name)));

		getAttribValue(str, animator_apm, "img");
		ASSERT_RETURN_FALSE(!str.empty());


		getAttribValue(str, animator_apm, "counter_max");
		ASSERT_RETURN_FALSE(!str.empty());
		
		pAS->Init(name, img, std::atoi(str.c_str()));


		for (ChildrenPtrVec::iterator it2 = pAnimator->children.begin(); it2 != pAnimator->children.end(); ++it2)
		{
			//解析各Action的属性
			PXMLELEMENT pAction = (*it2);
			ASSERT_RETURN_FALSE(pAction && pAction->tag == "Action");
			const AttribsPtrUMap& action_apm = pAction->attribs;

			std::string name;
			int total = 0;

			getAttribValue(name, action_apm, "name");
			ASSERT_RETURN_FALSE(!name.empty());

			getAttribValue(str, action_apm, "total");
			ASSERT_RETURN_FALSE(!str.empty());
			ASSERT_RETURN_FALSE((total = std::atoi(str.c_str())) > 0);

			// 解析frame
			CActionSet::FramesVec frames;
			for (int i = 0; i < total; ++i)
			{
				PXMLELEMENT pFrame = pAction->children.at(i);
				ASSERT_RETURN_FALSE(pFrame && pFrame->tag == "Frame");

				const AttribsPtrUMap& frame_apm = pFrame->attribs;
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

			pAS->AddAction(name, frames);
		}
	}
	return true;
}

void CActionSetSheet::Unload()
{
	m_ActionSets.clear();
}


CActionSet* CActionSetSheet::GetPage(const std::string& name)
{
	ActionSetUMap::iterator it = m_ActionSets.find(name);
	if (it != m_ActionSets.end())
	{
		return &it->second;
	}
	return NULL;
}

/////////////////////////////////////////////////////////////////////
//
// called by self
//
/////////////////////////////////////////////////////////////////////
CActionSet* CActionSetSheet::AddActionSet(const std::string& name)
{
	ActionSetUMap::iterator it = m_ActionSets.find(name);
	ASSERT(m_ActionSets.end() != it);
	return &m_ActionSets[name];
}

/////////////////////////////////////////////////////////////////////
//
// 工具函数
//
/////////////////////////////////////////////////////////////////////
void getAttribValue(std::string &o_value, const AttribsPtrUMap& i_apm, const std::string& i_key)
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
