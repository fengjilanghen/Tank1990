#ifndef _SPRITE_FACTORY_
#define _SPRITE_FACTORY_
#include "Sprite.h"
#include <unordered_map>
#include <string>

class CSpriteFactory
{
public:
	static CSpriteFactory* GetInstancePtr();
	CSprite *CreateSprite(const std::string& img);
private:
	CSpriteFactory();
	CSpriteFactory(const CSpriteFactory&) = delete;
	CSpriteFactory* operator=(const CSpriteFactory&) = delete;

	//void update(float delta_time);

private:
	typedef std::unordered_map<std::string, CSprite> SpriteUMap;
	SpriteUMap	m_Sprites;
};


#endif  //_SPRITE_FACTORY_