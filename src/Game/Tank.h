#ifndef _TANK_H_
#define _TANK_H_
#include "GameObject.h"
#include "Sprite.h"


class CTank : public CGameObject
{
public:
	typedef CGameObject super;
protected:
	int					m_nLast;
	bool				m_bAuto;

public:
	CTank();
	~CTank();

	bool Init(bool bAuto, const char* fname, const sPoint& pos = { 0, 0 }, const sSize& sz = { 0, 0 }, int speed = 0, int orient = DOWN);
	void Release();

	void Move(int orientation);
	void Update(float delta_time);
	void Draw();

	inline void SetAuto(bool bAuto) { m_bAuto = bAuto; }
	inline bool IsAuto() { return m_bAuto; }


protected:
	void StupidAuto();
	
};

#endif //_TANK_H_