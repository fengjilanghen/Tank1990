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
	
	// µØÍ¼ÐÅÏ¢
	if (!getline(lvlf, line))
	{
		ASSERT(false);
		return false;
	}

	if(!getMapInfoHeader(line)) return false;

	m_Map.reserve(m_nRows);

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
		m_Map.push_back(col);
		++i;
	}

	ASSERT_RETURN_FALSE(m_Map.size() == m_nRows);

	if(!checkHawk(hawk_count)) 
		return false;

	sSize sz = {m_nTileWidth * 2, m_nTileHeight* 2};



	return true;
}

void CLevel1::Unload()
{
	m_nRows = 0;
	m_nColumns = 0;
	m_nTileWidth = 0;
	m_nTileHeight = 0;
	m_Map.clear();
	m_HawkPos = { -1, -1, -1, -1 };
}


void CLevel1::Update()
{
	m_GreenTank.Update(0);
	m_RedTank.Update(0);
}

void CLevel1::Render()
{
	renderMap();
	m_GreenTank.Draw();
	m_RedTank.Draw();
}

void CLevel1::KeyEvent(int key, bool pressed)
{
	if (!pressed) return;
	switch (key)
	{
	case 'w':
	case 'W':
	{
		m_GreenTank.Move(CTank::UP);
	}break;
	case 's':
	case 'S':
	{
		m_GreenTank.Move(CTank::DOWN);
	}break;
	case 'a':
	case 'A':
	{
		m_GreenTank.Move(CTank::LEFT);
	}break;
	case 'd':
	case 'D':
	{
		m_GreenTank.Move(CTank::RIGHT);
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
	sRect rect = { m_HawkPos.left * m_nTileWidth,
				m_HawkPos.top * m_nTileHeight,
				m_HawkPos.right * m_nTileWidth,
				m_HawkPos.bottom * m_nTileHeight };
	m_Mapheet.Draw(rect, TT_HAWDK);

	for (int i = 0; i < m_nRows; ++i)
	{
		for (int j = 0; j < m_nColumns; ++j)
		{
			int type = m_Map[i][j];
			switch (type)
			{
			case TT_FLOOR:
			case TT_WALL:
			case TT_IRONWALL:
			case TT_RIVER:
			case TT_WOOD:
			case TT_BORN_A:
			case TT_BORN_B:
			{
				int left	= j*m_nTileWidth;
				int top		= i*m_nTileHeight;
				m_Mapheet.Draw({ left, top, left + m_nTileWidth, top + m_nTileHeight }, type);
			}break;
			}
		}
	}
	
}


bool CLevel1::checkHawk(int count)
{
	int rs = m_HawkPos.right - m_HawkPos.left;
	int cs = m_HawkPos.bottom - m_HawkPos.top;
	if (rs > 0 && cs > 0 && rs*cs == count)
	{
		for (int i = m_HawkPos.left; i < m_HawkPos.right; ++i)
		{
			for (int j = m_HawkPos.top; j < m_HawkPos.bottom; ++j)
			{
				ASSERT_RETURN_FALSE(m_Map.at(j).at(i) == TT_HAWDK);
			}
		}
		return true;
	}

	return false;
}