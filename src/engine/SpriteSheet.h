#ifndef _SHEET_SPRITE_H_
#define _SHEET_SPRITE_H_

#include "global_def.h"
#include "Graphics.h"
#include "XmlParser/XmlParser.h"
#include <unordered_map>
#include <string>

class CSpriteSheet
{
public:
	typedef std::unordered_map<int, sRect>	PageUMap;

public:
	CSpriteSheet();
	void clear();
	
	bool AddSheetPage(int index, const sRect& rect);
	sRect GetSheetPage(int index);
	
private:
	PageUMap		m_umPages;
};


#endif //_SHEET_SPRITE_H_
