#ifndef _TANK_FACTORY_H_
#define _TANK_FACTORY_H_

#include "Tank.h"
#include "ObjectFactory.hpp"
#include "ActionSetSheet.h"

class CTankFactory :public CObjectFactory<CTank, CActionSetSheet>
{
public:
	CTank *Create(const std::string& obj_name, bool bAuto, bool bUseAnimator, const sPoint& pos, const sSize& sz, int speed, int orient)
	{
		CActionSet* pAS = m_Sheet.GetPage(obj_name);
		if (!pAS)
		{
			return NULL;
		}

		CTank *p = m_ObjManager.GetNewObject();
		if (p && p->Init(bAuto, bUseAnimator, pAS, pos, sz, speed, orient))
		{
			return p;
		}
		if (p) p->SetReleaseFlag(true);
		return NULL;
	}
};

#endif //_TANK_FACTORY_H_