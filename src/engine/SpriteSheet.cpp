#include "SpriteSheet.h"
#include "Convert.h"
#include "Game/GameLevel.h"



CSpriteSheet::CSpriteSheet()
{
	clear();
}

bool CSpriteSheet::AddSheetPage(int index, const sRect& rect)
{
	if (rect.right <= rect.left || rect.bottom <= rect.top)
	{
		ASSERT(false);
		return false;
	}

	m_umPages[index] = rect;
	return true;
}


sRect CSpriteSheet::GetSheetPage(int index)
{
	PageUMap::iterator it = m_umPages.find(index);
	if (it != m_umPages.end())
	{
		return it->second;
	}
	return{ -1, -1, -1, -1 };
}


void CSpriteSheet::clear()
{
	m_umPages.clear();
}