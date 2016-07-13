#ifndef _ACTIONSET_H_
#define _ACTIONSET_H_

#include "global_def.h"
#include "IRenderObject.h"
#include <vector>
#include <unordered_map>
#include <string>

class CActionSet : public IRenderObject
{
public:
	typedef std::vector<sRect>									FramesVec;
	typedef std::unordered_map<std::string, FramesVec>			ActionsUMap;

public:
	CActionSet();

	bool Init(const std::string& asname, const std::string& img, int counter_max);
	void Draw(const sRect& src, const sRect& dest) override;

	void AddAction(const std::string& action, const FramesVec& frames);
	void AddAction(const std::string& action, const sRect* frames, int num_frames);

	int GetFrameCount(const std::string& action) const;
	const sRect& GetRect(const std::string& action, int frame) const;

	inline std::string GetASDName()const { return m_ASName; }
	inline int GetCounterMax() const{ return m_CounterMax; }
	inline bool HasAction(const std::string& action) const { return m_AllActions.find(action) != m_AllActions.end(); }


protected:
	void Draw(const sRect& dest) override{}

private:
	CSprite*				m_pSprite;
	int						m_CounterMax;	//每个动画帧持续的游戏帧数
	std::string				m_ASName;
	ActionsUMap				m_AllActions;
};


#endif //_ACTIONSET_H_