/**********************************************************
*
* 是一个基类，create需要子类自己创建
*
**********************************************************/
#ifndef _OBJECT_FACTORY_H
#define _OBJECT_FACTORY_H

#include "global_def.h"
#include "MoveObject.h"
#include "ObjectManager.hpp"
#include "ActionSetSheet.h"
#include <forward_list>
#include <queue>
#include <string>

template<typename OBJECT, typename SHEET>
class CObjectFactory
{
public:
	CObjectFactory()
		: m_Sheet()
		, m_ObjManager()
	{

	}

	bool Init(const std::string& fname)
	{
		return m_TankSheet.Load(fname);
	}
	

	void Tick(float dt)
	{
		m_ObjManager.Tick(dt);
	}


protected:
	CObjectManager<OBJECT>				m_ObjManager;
	SHEET								m_Sheet;
};

#endif  //_OBJECT_FACTORY_H