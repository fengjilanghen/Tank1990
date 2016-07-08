#include "SpriteFactory.h"
////////////////////////////////////////////////////////////////////////
//
// called by others
//
////////////////////////////////////////////////////////////////////////
CSpriteFactory* CSpriteFactory::GetInstancePtr()
{
	static CSpriteFactory sf;
	return &sf;
}

CSprite *CSpriteFactory::CreateSprite(const std::string& img)
{
	SpriteUMap::iterator it = m_Sprites.find(img);
	if (it != m_Sprites.end())
	{
		return &it->second;
	}

	if (m_Sprites[img].Init(img))
	{
		return &m_Sprites[img];
	}
	
	m_Sprites.erase(img);
	ASSERT(false);
	return NULL;
}

////////////////////////////////////////////////////////////////////////
//
// called by self
//
////////////////////////////////////////////////////////////////////////
CSpriteFactory::CSpriteFactory()
{
	m_Sprites.clear();
}