#ifndef _ANIMATOR_H_
#define _ANIMATOR_H_

#include <vector>
#include <unordered_map>
#include <string>

struct sRect
{
	int left;
	int top;
	int right;
	int bottom;
};

class Animator
{
public:
	typedef std::vector<sRect>		FramesVec;
	typedef std::unordered_map<std::string, std::vector<sRect>>	ActionsMap;
	
	enum
	{
		STATE_NONE = 0, 
		STATE_BEGINSET,
		STATE_PREPARED,
		STATE_RUNNING,
		STATE_PAUSE,
		STATE_STOP,
		STATE_COUNT,
	};

public:
	Animator();

	// 从文件直接加载动作
	void LoadConfig(const char* fname);

	// 手动添加动作
	void BeginSet(const char* img, int counter_max);	//counter_max至少为1
	void EndSet();
	void Animator::AddAction(const char* action, const FramesVec& frames);
	void Animator::AddAction(const char* action, sRect* frames, int num_frames);

	// 动画控制函数
	void Start(const char* action);
	void Stop();
	void Pause();
	void Resume();

	void Reset();

	void Animate(int delta_time);
	void Draw(int x, int y);



private:
	int				m_State;		//动画状态
	std::string 	m_ImgName;		//对象动作所在图片
	std::string		m_CurAction;	//当前动作
	int				m_CurFrame;		//当前帧
	int				m_Counter;		//当前动画帧已持续的游戏帧数
	int				m_CounterMax;	//每个动画帧持续的游戏帧数

	ActionsMap		m_AllActions;
};


#endif //_ANIMATOR_H_