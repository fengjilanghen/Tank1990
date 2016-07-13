#include "SpriteFactory.h"

CSpriteFactory::CSpriteFactory()
{
	m_Sprites.clear();
}

CSpriteFactory::~CSpriteFactory()
{
	Release();
}
////////////////////////////////////////////////////////////////////////
//
// called by others
//
////////////////////////////////////////////////////////////////////////
void CSpriteFactory::Release()
{
	for (SpriteUMap::iterator it = m_Sprites.begin(); it != m_Sprites.end(); ++it)
	{
		delete it->second;
		it->second = NULL;
	}
	m_Sprites.clear();
}

CSprite *CSpriteFactory::Create(const std::string& img)
{
	SpriteUMap::iterator it = m_Sprites.find(img);
	if (it != m_Sprites.end())
	{
		return it->second;
	}
	m_Sprites[img] = new CSprite();
	if (m_Sprites[img] && m_Sprites[img]->Init(img))
	{
		return m_Sprites[img];
	}
	
	m_Sprites.erase(img);
	ASSERT(false);
	return NULL;
}