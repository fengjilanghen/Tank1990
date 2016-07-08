#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

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

class CGameObject
{
public:
	enum
	{
		LEFT = 0,
		RIGHT,
		UP,
		DOWN,
		ORIEN_COUNT,
	};
public:
	CGameObject()
		: m_Position({0, 0})
		, m_Size({ 0, 0 })
		, m_Speed(0)
		, m_Orientation(DOWN)
		, m_pAniSprite(nullptr){}
	virtual ~CGameObject(){}
	
	virtual bool Init(const sPoint& pos = { 0, 0 }, const sSize& sz = { 0, 0 }, int speed = 0, int orient = DOWN);
	virtual void Release();
	virtual void Move(int orientation);
	virtual void Update(float delta_time);
	virtual void Draw();


	virtual CAnimator* GetAnimator()
	{
		CSprite::uSpriteAttach* pAttach = (CSprite::uSpriteAttach*)(m_pAniSprite->GetAttachPtr());
		if (!pAttach)
		{
			return nullptr;
		}

		return (CSpriteAnimator*)(pAttach->pAnimator);
	}

	inline const sSize& GetSize() const { return m_Size; }
	inline const sPoint& GetPos() const { return m_Position; }
	inline int GetSpeed() const { return m_Speed; }
	inline void SetSize(const sSize& sz) { m_Size = sz; }
	inline void SetPosition(const sPoint& pos) { m_Position = pos; }
	inline void SetSpeed(int vel) { m_Speed = vel; }
protected:
	CSprite*			m_pAniSprite;
	sSize				m_Size;
	sPoint				m_Position;
	int					m_Speed;
	int					m_Orientation;
};


#endif //_GAME_OBJECT_H_