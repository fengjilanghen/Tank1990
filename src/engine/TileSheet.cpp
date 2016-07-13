#include "TileSheet.h"
#include "Convert.h"
#include "SpriteFactory.h"
#include "XmlParser/XmlParser.h"
#include "Game/GameLevel.h"

CTileSheet::CTileSheet()
{
	m_umPages.clear();
}

////////////////////////////////////////////////////////////////////////
//
// called by others
//
////////////////////////////////////////////////////////////////////////
bool CTileSheet::Load(const std::string& fname)
{
	PXMLELEMENT pRoot = XmlParser::ParseFile(fname.c_str());
	ASSERT_RETURN_FALSE(pRoot && pRoot->tag == "sheet");

	std::string str;
	int size = pRoot->children.size();
	for (int i = 0; i < size; ++i)
	{
		ASSERT_RETURN_FALSE(pRoot->tag != "frame");
		AttribsPtrUMap& attribs = pRoot->children[i]->attribs;
		
		std::string	name;
		std::string	img;
		sRect		rect;

		getAttribValue(name, attribs, "name");
		ASSERT_RETURN_FALSE(!name.empty());

		getAttribValue(img, attribs, "img");
		ASSERT_RETURN_FALSE(!img.empty());
		
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

		ASSERT_RETURN_FALSE(AddSheetPage(name, rect, img));
	}
	return true;
}


void CTileSheet::Unload()
{
	m_umPages.clear();
}

CTile* CTileSheet::GetPage(const std::string& name)
{
	TileUMap::const_iterator it = m_umPages.find(name);
	if (it != m_umPages.end())
	{
		return &it->second;
	}
	return NULL;
}

////////////////////////////////////////////////////////////////////////
//
// called by self
//
////////////////////////////////////////////////////////////////////////
bool CTileSheet::AddSheetPage(const std::string& name, bool bCollidable, const sRect& rect, const std::string& img)
{
	ASSERT(m_umPages.find(name) == m_umPages.end());
	return m_umPages[name].Init(name, bCollidable, rect, img);
}

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