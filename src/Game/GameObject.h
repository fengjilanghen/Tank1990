#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "global_def.h"
#include "Animator.h"

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
	CGameObject();
	virtual ~CGameObject(){}
	
	virtual bool Init(bool bUseAnimator, IRenderObject *pro, const sPoint& pos = { 0, 0 }, const sSize& sz = { 0, 0 });
	virtual void Release();

	virtual void Update(float dt);
	virtual void Draw();

	inline const sSize& GetSize() const { return m_Size; }
	inline const sPoint& GetPos() const { return m_Position; }
	inline void SetSize(const sSize& sz) { m_Size = sz; }
	inline void SetPosition(const sPoint& pos) { m_Position = pos; }
	inline void SetReleaseFlag(bool bRelease){ m_bReleaseFlag = bRelease; }
	inline bool GetReleaseFlag(){ return m_bReleaseFlag; }
protected:
	IRenderObject*		m_pRenderObject;
	sSize				m_Size;
	sPoint				m_Position;
	bool				m_bReleaseFlag;
	CAnimator			m_Animator;
	bool				m_bUseAnimator;
};


#endif //_GAME_OBJECT_H_