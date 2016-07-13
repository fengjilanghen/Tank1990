/****************************************
*
* �����洢����ͼ��Ķ��󣬸��ݵ�ͼ�������id���ض���ָ��
*
******************************************/

#ifndef _TILE_SHEET_H_
#define _TILE_SHEET_H_

#include "global_def.h"
#include "Sprite.h"
#include "IRenderObject.h"
#include "Tile.h"
#include <unordered_map>
#include <string>

class CTileSheet
{
public:
	typedef std::unordered_map<std::string, CTile>		TileUMap;

public:
	CTileSheet();

	bool Load(const std::string& fname);
	void Unload();
	CTile* GetPage(const std::string& name);
protected:
	bool AddSheetPage(const std::string& name, const sRect& rect, const std::string& img);
	
private:
	TileUMap			m_umPages;
};


#endif //_TILE_SHEET_H_
