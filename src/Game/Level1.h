#ifndef _LEVLE1_H_
#define _LEVLE1_H_

#include "IGameLevel.h"
#include "tank.h"
#include "MoveObject.h"
#include "GameObject.h"
#include "TankFactory.h"
#include "MoveObjFactory.h"
#include "TileFactory.h"
#include <string>
#include <vector>


class CLevel1 :public IGameLevel
{
public:
	typedef std::vector<CGameObject*>		ColumnVec;
	typedef std::vector<ColumnVec>			MapVec;

	typedef std::vector<CTank*>				TankVtr;
	typedef std::vector<CMoveObject*>		MoveObjectVtr;

	typedef std::vector<CGameObject*>		TileVtr;

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

private:
	CTankFactory		m_TankFac;
	CMoveObjFactory		m_BulletFac;
	CTileFactory		m_TileFac;

	TankVtr				m_Tanks;
	CTank*				m_MyTank;
	MoveObjectVtr		m_Bullets;
	//TileVtr				m_CollidableTiles;
	
	int					m_nRows;
	int					m_nColumns;
	int					m_nTileWidth;
	int					m_nTileHeight;
	int					m_nMaxTankCount;
	MapVec				m_Map;

};


#endif //_LEVLE1_H_