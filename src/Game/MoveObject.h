#ifndef _MOVEOBJECT_H_
#define _MOVEOBJECT_H_
#include "GameObject.h"
#include "Sprite.h"


class CMoveObject : public CGameObject
{
public:
	typedef CGameObject super;
protected:
	sPoint				m_Velocity;
	int					m_Orientation;
	int					m_Speed;
	int					m_nLast;
	bool				m_bAuto;

public:
	CMoveObject();
	~CMoveObject();

	bool Init(bool bAuto, bool bUseAnimator, IRenderObject* pro, const sPoint& pos = { 0, 0 }, const sSize& sz = { 0, 0 }, int speed = 0, int orient = DOWN);
	void Release();
	void Update(float dt) override;
	void Draw() override;

	void Move(int orient);

	inline int GetSpeed() const { return m_Speed; }
	inline void SetSpeed(int speed) { m_Speed = speed; }
	inline void SetAuto(bool bAuto) { m_bAuto = bAuto; }
	inline bool IsAuto() const { return m_bAuto; }


protected:
	void SetOrientation(int orient);
	void StupidAuto();
	
};

#endif //_MOVEOBJECT_H_