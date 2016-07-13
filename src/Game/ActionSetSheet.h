#ifndef _ACTIONSET_SHEET_H_
#define _ACTIONSET_SHEET_H_

#include "global_def.h"
#include "ActionSet.h"
#include "Sprite.h"
#include <string>
#include <unordered_map>

class CActionSetSheet
{
public:
	typedef std::unordered_map<std::string, CActionSet>		ActionSetUMap;
public:
	CActionSetSheet();
	~CActionSetSheet();

	bool Load(const std::string& fname);
	void Unload();
	CActionSet* GetPage(const std::string& name);

private:

	CActionSet* AddActionSet(const std::string& name);

private:
	ActionSetUMap			m_ActionSets;
};


#endif //_ACTIONSET_SHEET_H_