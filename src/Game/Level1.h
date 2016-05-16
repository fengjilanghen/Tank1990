#ifndef _LEVLE1_H_
#define _LEVLE1_H_

#include "GameLevel.h"

class CLevel1 :public CGameLevel
{
private:
	float y;
	float yspeed;

public:
	bool Load() override;
	void Unload() override;
	void Render() override;
	void Update() override;
};


#endif //_LEVLE1_H_