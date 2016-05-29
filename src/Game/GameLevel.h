#ifndef _GAME_LEVEL_H_
#define _GAME_LEVEL_H_

enum eTileType
{
	TT_FLOOR		= 0,
	TT_WALL			= 1,
	TT_IRONWALL		= 2,
	TT_RIVER		= 3,
	TT_WOOD			= 4,
	TT_HAWDK		= 5,
	TT_BORN_A		= 6,	//己方出生地
	TT_BORN_B		= 7,	//敌方出生地
	TT_COUNT,
};

class CGameLevel
{
public:
	virtual bool Load() = 0;
	virtual void Unload() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0; 
	virtual void KeyEvent(int key, bool pressed) = 0;
};

#endif //_GAME_LEVEL_H_