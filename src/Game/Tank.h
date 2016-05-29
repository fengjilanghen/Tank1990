#ifndef _TANK_H_
#define _TANK_H_

#include "Sprite.h"

struct sSize
{
	int cx;
	int cy;
};

struct sPoint
{
	int x;
	int y;
};


struct sVelocity
{
	int xs;
	int ys;
};

class CTank
{
public:
	enum
	{
		LEFT=0,
		RIGHT,
		UP,
		DOWN,
		ORIEN_COUNT,
	};

protected:
	CSprite				m_AniSprite;
	int					m_Orientation;
	sSize				m_Size;
	sPoint				m_Position;
	sVelocity			m_Speed;
	int					m_nLast;
	bool				m_bAuto;

public:
	CTank();
	bool Init(bool bAuto, const char* fname, const sSize& sz, const sVelocity& speed, int orient = UP);
	void Release();

	void Move(int orientation);
	void Update(float delta_time);
	void Draw();

	inline void SetAuto(bool bAuto) { m_bAuto = bAuto; }
	inline bool IsAuto() { return m_bAuto; }
	inline void SetSize(const sSize& sz) { m_Size = sz; }
	inline void SetPosition(const sPoint& pos) { m_Position = pos; }
	inline void SetSpeed(const sVelocity& vel) { m_Speed = vel; }


protected:
	CSpriteAnimator* GetAnimator();
	void StupidAuto();
	
};

#endif //_TANK_H_