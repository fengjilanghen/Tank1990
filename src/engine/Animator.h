#ifndef _ANIMATOR_H_
#define _ANIMATOR_H_

#include "global_def.h"
#include "IRenderObject.h"
#include "Sprite.h"
#include "ActionSet.h"
#include <vector>
#include <unordered_map>
#include <string>

class CAnimator
{
public:
	enum
	{
		STATE_NONE = 0,
		STATE_PREPARED,
		STATE_RUNNING,
		STATE_PAUSE,
		STATE_COUNT,
	};

public:
	CAnimator();

	bool Init(CActionSet* pas);
	void Release();

	void Update(float delta_time);
	void Draw(const sRect& dest);

	// 动画控制函数
	void Start(const std::string&  action);
	void Stop();
	void Pause();
	void Resume();

	inline bool IsRunning(){ return m_State == STATE_RUNNING; }
	inline bool IsPaused(){ return m_State == STATE_PAUSE; }

private:
	int						m_State;		//动画状态
	std::string				m_CurAction;	//当前动作
	int						m_CurFrame;		//当前帧
	int						m_Counter;		//当前动画帧已持续的游戏帧数
	CActionSet*				m_pActionSet;
};


#endif //_ANIMATOR_H_