#ifndef _GAME_LEVEL_H_
#define _GAME_LEVEL_H_

class CGameLevel
{
public:
	virtual bool Load() = 0;
	virtual void Unload() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;
};

#endif //_GAME_LEVEL_H_