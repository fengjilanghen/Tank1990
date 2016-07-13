#ifndef _GAMEOBJECT_FACTORY_H_
#define _GAMEOBJECT_FACTORY_H_

#include "GameObject.h"
#include "ObjectFactory.hpp"
#include "TileSheet.h"

class CTileFactory :public CObjectFactory<CGameObject, CTileSheet>
{
public:
	CGameObject *Create(const std::string& obj_name, bool bUseAnimator, const sPoint& pos, const sSize& sz)
	{
		CTile* pTile = m_Sheet.GetPage(obj_name);
		if (!pTile)
		{
			return NULL;
		}

		CGameObject *p = m_ObjManager.GetNewObject();
		if (p && p->Init(bUseAnimator, pTile, pos, sz))
		{
			return p;
		}
		if (p) p->SetReleaseFlag(true);
		return NULL;
	}
};

#endif //_GAMEOBJECT_FACTORY_H_