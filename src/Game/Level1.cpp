#include "../global_def.h"
#include "Level1.h"
#include "../Graphics.h"
#include "../XmlParser/XmlParser.h"

#include <fstream>
#include <sstream>

using namespace std;

static const char HAWDK[] = "HAWDK";

CLevel1::CLevel1()
	: m_nRows(0)
	, m_nMaxTankCount(4)
	, m_nTotalTankCount(20)
	, m_nColumns(0)
	, m_nTileWidth(0)
	, m_nTileHeight(0)
	, m_TankFac()
	, m_BulletFac()
	, m_TileFac()
	, m_Tanks()
	, m_MyTank()
	, m_Bullets()
	//, m_CollidableTiles()
	, m_Map()
{

}

bool CLevel1::Load()
{
	m_Map.clear();

	ifstream lvlf("maps/1.csv");
	if (!lvlf)
	{
		ASSERT(false);
		return false;
	}

	string line;
	
	// ��ͼ��Ϣ
	if (!getline(lvlf, line))
	{
		ASSERT(false);
		return false;
	}

	if(!getMapInfoHeader(line)) return false;

	m_Map.resize(m_nRows);

	sSize sz = { m_nTileWidth, m_nTileHeight };
	int hawk_count	= 0;
	int i = 0;
	while (getline(lvlf, line))
	{
		stringstream ss(line);
		ColumnVec col(m_nColumns, 0);
		string token;
		int j = 0;
		while (getline(ss, token, ','))
		{
			col[j] = m_TileFac.Create(token, false, { i*m_nTileWidth, j*m_nTileHeight }, sz);
			++j;
		}
		ASSERT_RETURN_FALSE(j == m_nColumns);
		m_Map[i] = col;
		++i;
	}

	ASSERT_RETURN_FALSE(m_Map.size() == m_nRows);
	return true;
}

void CLevel1::Unload()
{
	m_nRows = 0;
	m_nColumns = 0;
	m_nTileWidth = 0;
	m_nTileHeight = 0;
	m_Map.clear();
}


void CLevel1::Update()
{

}

void CLevel1::Render()
{
	renderMap();
	m_MyTank->Draw();
	for (auto it = m_Tanks.begin(); it != m_Tanks.end(); ++it)
	{
		(*it)->Draw();
	}
	for (auto it = m_Bullets.begin(); it != m_Bullets.end(); ++it)
	{
		(*it)->Draw();
	}
}

void CLevel1::KeyEvent(int key, bool pressed)
{
	if (!pressed) return;
	switch (key)
	{
	case 'w':
	case 'W':
	{
				m_MyTank->Move(CTank::UP);
	}break;
	case 's':
	case 'S':
	{
				m_MyTank->Move(CTank::DOWN);
	}break;
	case 'a':
	case 'A':
	{
				m_MyTank->Move(CTank::LEFT);
	}break;
	case 'd':
	case 'D':
	{
				m_MyTank->Move(CTank::RIGHT);
	}break;

	}
}


//////////////////////////////////////////////////////////////////////
//
//	functions called by self
//
//////////////////////////////////////////////////////////////////////
bool CLevel1::getMapInfoHeader(const std::string &line)
{
	if (line.empty())
		return false;

	stringstream ss(line);
	string token;
	
	ASSERT_RETURN_FALSE(getline(ss, token, ','));
	m_nColumns = std::stoi(token);
	ASSERT_RETURN_FALSE(m_nColumns > 0);

	ASSERT_RETURN_FALSE(getline(ss, token, ','));
	m_nRows = std::stoi(token);
	ASSERT_RETURN_FALSE(m_nRows > 0);

	ASSERT_RETURN_FALSE(getline(ss, token, ','));
	m_nTileWidth = std::stoi(token);
	ASSERT_RETURN_FALSE(m_nTileWidth > 0);

	ASSERT_RETURN_FALSE(getline(ss, token, ','));
	m_nTileHeight = std::stoi(token);
	ASSERT_RETURN_FALSE(m_nTileHeight > 0);
	
	ASSERT_RETURN_FALSE(getline(ss, token, ','));
	m_nMaxTankCount = std::stoi(token);
	ASSERT_RETURN_FALSE(m_nMaxTankCount > 0);

	ASSERT_RETURN_FALSE(getline(ss, token, ','));
	m_nTotalTankCount = std::stoi(token);
	ASSERT_RETURN_FALSE(m_nTotalTankCount > 0);


	// tile sheet
	ASSERT_RETURN_FALSE(getline(ss, token, ','));
	ASSERT_RETURN_FALSE(m_TileFac.Init(token.c_str()));

	// tank sheet
	ASSERT_RETURN_FALSE(getline(ss, token, ','));
	ASSERT_RETURN_FALSE(m_TankFac.Init(token.c_str()));

	// bullet sheet
	ASSERT_RETURN_FALSE(getline(ss, token, ','));
	ASSERT_RETURN_FALSE(m_BulletFac.Init(token.c_str()));

	return true;
}


void CLevel1::renderMap()
{
	for (int i = 0; i < m_nRows; ++i)
	{
		for (int j = 0; j < m_nColumns; ++j)
		{			
			m_Map[i][j]->Draw();
		}
	}
	
}