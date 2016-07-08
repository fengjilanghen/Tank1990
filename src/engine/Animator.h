#ifndef _ANIMATOR_H_
#define _ANIMATOR_H_

#include "global_def.h"
#include "IRenderObject.h"
#include "Sprite.h"
#include <vector>
#include <unordered_map>
#include <string>

class CAnimator : public IRenderObject
{
public:
	typedef std::vector<sRect>									FramesVec;
	typedef std::unordered_map<std::string, FramesVec>			ActionsUMap;

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
	bool Init(const std::string& fname);
	void Release();

	virtual void Update(float delta_time) override;
	virtual void Draw() override;

	// 动画控制函数
	void Start(const std::string&  action);
	void Stop();
	void Pause();
	void Resume();

	inline bool IsRunning(){ return m_State == STATE_RUNNING; }
	inline bool IsPaused(){ return m_State == STATE_PAUSE; }

protected:
	void getAttribValue(std::string &o_value, const AttribsPtrUMap& i_apm, const std::string& i_key);
	const sRect& GetCurFrameRect();

	// 手动添加动作
	inline void SetCounterMax(int counter_max){ m_CounterMax = (counter_max <= 0 ? 1 : counter_max); }
	void AddAction(const std::string& action, const FramesVec& frames);
	void AddAction(const std::string& action, const sRect* frames, int num_frames);

private:
	CSprite*		m_pSprite;
	int				m_State;		//动画状态
	std::string		m_CurAction;	//当前动作
	int				m_CurFrame;		//当前帧
	int				m_Counter;		//当前动画帧已持续的游戏帧数
	int				m_CounterMax;	//每个动画帧持续的游戏帧数

	ActionsUMap		m_AllActions;
};


#endif //_ANIMATOR_H_