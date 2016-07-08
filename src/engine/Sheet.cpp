#include "Sheet.h"
#include "Convert.h"
#include "SpriteFactory.h"
#include "XmlParser/XmlParser.h"
#include "Game/GameLevel.h"

CSheet::CSheet()
	:m_pSprite(NULL)
{
	m_umPages.clear();
}


bool CSheet::Init(const std::string& fname)
{
	PXMLELEMENT pRoot = XmlParser::ParseFile(fname.c_str());
	ASSERT_RETURN_FALSE(pRoot && pRoot->tag == "sheet");

	std::string str;
	getAttribValue(str, pRoot->attribs, "img");
	ASSERT_RETURN_FALSE(!str.empty());
	m_pSprite = CSpriteFactory::GetInstancePtr()->CreateSprite(str);	
	ASSERT_RETURN_FALSE(!m_pSprite || !m_pSprite->Init(str))

	int size = pRoot->children.size();
	for (int i = 0; i < size; ++i)
	{
		ASSERT_RETURN_FALSE(pRoot->tag != "frame");
		AttribsPtrUMap& attribs = pRoot->children[i]->attribs;

		int		type = -1;
		sRect	rect;

		getAttribValue(str, attribs, "type");
		ASSERT_RETURN_FALSE(!str.empty());
		type = std::stoi(str);

		getAttribValue(str, attribs, "x");
		ASSERT_RETURN_FALSE(!str.empty());
		rect.left = std::stoi(str);

		getAttribValue(str, attribs, "y");
		ASSERT_RETURN_FALSE(!str.empty());
		rect.top = std::stoi(str);

		getAttribValue(str, attribs, "w");
		ASSERT_RETURN_FALSE(!str.empty());
		rect.right = rect.left + std::stoi(str);

		getAttribValue(str, attribs, "h");
		ASSERT_RETURN_FALSE(!str.empty());
		rect.bottom = rect.top + std::stoi(str);

		ASSERT_RETURN_FALSE(AddSheetPage(type, rect));
	}
	return true;
}


void CSheet::Release()
{
	m_umPages.clear();
}

bool CSheet::AddSheetPage(int index, const sRect& rect)
{
	if (rect.right <= rect.left || rect.bottom <= rect.top)
	{
		ASSERT(false);
		return false;
	}

	m_umPages[index] = rect;
	return true;
}


sRect CSheet::GetSheetPage(int index)
{
	PageUMap::iterator it = m_umPages.find(index);
	if (it != m_umPages.end())
	{
		return it->second;
	}
	return{ -1, -1, -1, -1 };
}

void CSheet::getAttribValue(std::string &o_value, const AttribsPtrUMap& i_apm, const std::string& i_key)
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