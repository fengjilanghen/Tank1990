#ifndef _LEVLE1_H_
#define _LEVLE1_H_

#include "GameLevel.h"
#include "Tank.h"
#include "Sprite.h"
#include <string>
#include <vector>

class CSprite;

class CLevel1 :public CGameLevel
{
public:
	typedef std::vector<int>		ColumnVec;
	typedef std::vector<ColumnVec>	TileVec;

private:
	CTank				m_GreenTank;
	CTank				m_RedTank;
	CSprite				m_TileSheet;
	int					m_nRows;
	int					m_nColumns;
	int					m_nTileWidth;
	int					m_nTileHeight;
	TileVec				m_Tiles;
	sRect				m_HawkPos;

public:
	CLevel1();
	bool Load() override;
	void Unload() override;
	void Render() override;
	void Update() override;
	void KeyEvent(int key, bool pressed) override;

private:
	bool getMapInfoHeader(const std::string &line);
	void renderMap();
	bool checkHawk(int count);
};


#endif //_LEVLE1_H_