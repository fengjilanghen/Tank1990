#include "../global_def.h"
#include "Level1.h"
#include "../Graphics.h"
#include "../XmlParser/XmlParser.h"

#include <fstream>
#include <sstream>

using namespace std;

#define FALSE_RETURN(express) if(!(express)) { ASSERT(false); return false; }


CLevel1::CLevel1()
	: m_GreenTank()
	, m_RedTank()
	, m_TileSheet()
	, m_nRows(0)
	, m_nColumns(0)
	, m_nTileWidth(0)
	, m_nTileHeight(0)
	, m_Tiles(0)
	, m_HawkPos({ -1, -1, -1, -1 })
{

}


bool CLevel1::Load()
{
	m_Tiles.clear();

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

	m_Tiles.reserve(m_nRows);

	int hawk_count	= 0;
	while (getline(lvlf, line))
	{
		stringstream ss(line);
		ColumnVec col(m_nColumns, 0);
		string token;
		int j = 0;
		while (getline(ss, token, ','))
		{
			col[j] = std::stoi(token);
			FALSE_RETURN(col[j] >= TT_FLOOR && col[j] <= TT_COUNT);

			if (col[j] == TT_HAWDK)
			{
				++hawk_count;
				if (m_HawkPos.left == -1)
				{
					m_HawkPos.left = j;
					m_HawkPos.right = m_HawkPos.left + 1;
					m_HawkPos.top = m_Tiles.size();
					m_HawkPos.bottom = m_HawkPos.top + 1;
				}
				else
				{
					if (j >= m_HawkPos.right)
						m_HawkPos.right = j + 1;

					int i = m_Tiles.size();
					if (i >= m_HawkPos.bottom)
						m_HawkPos.bottom = i + 1;
				}
			}			

			++j;
		}
		FALSE_RETURN(j == m_nColumns);
		m_Tiles.push_back(col);
	}

	FALSE_RETURN(m_Tiles.size() == m_nRows);

	if(!checkHawk(hawk_count)) 
		return false;

	sSize sz = {m_nTileWidth * 2, m_nTileHeight* 2};
	sVelocity speed = { m_nTileWidth, m_nTileHeight };
	m_GreenTank.Init(false, "pic/green_tank.xml", sz, speed);
	m_GreenTank.SetPosition({ 24, 30 });

	m_RedTank.Init(true, "pic/gold_tank.xml", sz, speed);


	return true;
}

void CLevel1::Unload()
{
	m_GreenTank.Release();
	m_TileSheet.Release();
	m_nRows = 0;
	m_nColumns = 0;
	m_nTileWidth = 0;
	m_nTileHeight = 0;
	m_Tiles.clear();
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
	
	FALSE_RETURN(getline(ss, token, ','));
	m_nColumns = std::stoi(token);
	FALSE_RETURN(m_nColumns > 0);

	FALSE_RETURN(getline(ss, token, ','));
	m_nRows = std::stoi(token);
	FALSE_RETURN(m_nRows > 0);

	FALSE_RETURN(getline(ss, token, ','));
	m_nTileWidth = std::stoi(token);
	FALSE_RETURN(m_nTileWidth > 0);

	FALSE_RETURN(getline(ss, token, ','));
	m_nTileHeight = std::stoi(token);
	FALSE_RETURN(m_nTileHeight > 0);

	FALSE_RETURN(getline(ss, token, ','));
	FALSE_RETURN(m_TileSheet.Init(CSprite::ST_SHEET, token.c_str()));

	return true;
}


void CLevel1::renderMap()
{
	sRect rect = { m_HawkPos.left * m_nTileWidth,
				m_HawkPos.top * m_nTileHeight,
				m_HawkPos.right * m_nTileWidth,
				m_HawkPos.bottom * m_nTileHeight };
	m_TileSheet.Draw(rect, TT_HAWDK);

	for (int i = 0; i < m_nRows; ++i)
	{
		for (int j = 0; j < m_nColumns; ++j)
		{
			int type = m_Tiles[i][j];
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
				m_TileSheet.Draw({ left, top, left + m_nTileWidth, top + m_nTileHeight }, type);
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
				FALSE_RETURN(m_Tiles.at(j).at(i) == TT_HAWDK);
			}
		}
		return true;
	}

	return false;
}