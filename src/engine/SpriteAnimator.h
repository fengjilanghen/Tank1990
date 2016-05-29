#ifndef _SPRITE_ANIMATOR_H_
#define _SPRITE_ANIMATOR_H_

#include "global_def.h"
#include <vector>
#include <unordered_map>
#include <string>

class CSpriteAnimator
{
public:
	typedef std::vector<sRect>									FramesVec;
	typedef std::unordered_map<std::string, std::vector<sRect>>	ActionsMap;

	enum
	{
		STATE_NONE = 0,
		STATE_PREPARED,
		STATE_RUNNING,
		STATE_PAUSE,
		STATE_COUNT,
	};

public:
	CSpriteAnimator();

	// 手动添加动作
	bool BeginSet();
	inline void EndSet(){ m_State = STATE_PREPARED; }
	inline void SetCounterMax(int counter_max){ m_CounterMax = (counter_max <= 0 ? 1 : counter_max); }
	void AddAction(const std::string& action, const FramesVec& frames);
	void AddAction(const std::string& action, const sRect* frames, int num_frames);
	
	// 动画控制函数
	void Start(const std::string&  action);
	void Stop();
	void Pause();
	void Resume();


	void Animate(float delta_time);
	sRect GetCurFrameRect();

	inline bool IsRunning(){ return m_State == STATE_RUNNING; }
	inline bool IsPaused(){ return m_State == STATE_PAUSE; }

protected:
	void Reset();

private:
	int				m_State;		//动画状态
	std::string		m_CurAction;	//当前动作
	int				m_CurFrame;		//当前帧
	int				m_Counter;		//当前动画帧已持续的游戏帧数
	int				m_CounterMax;	//每个动画帧持续的游戏帧数

	ActionsMap		m_AllActions;
};


#endif //_SPRITE_ANIMATOR_H_