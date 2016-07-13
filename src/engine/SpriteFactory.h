#ifndef _SPRITE_FACTORY_
#define _SPRITE_FACTORY_
#include "Sprite.h"
#include <unordered_map>
#include <string>

class CSpriteFactory
{
public:
	~CSpriteFactory();
	CSprite *Create(const std::string& img);
	void Tick(float dt){}
	void Release();

	static CSpriteFactory* GetInstancePtr()
	{
		static CSpriteFactory sf;
		return &sf;
	}

private:
	CSpriteFactory();
	CSpriteFactory(const CSpriteFactory&) = delete;
	CSpriteFactory* operator=(const CSpriteFactory&) = delete;

	//void update(float delta_time);

private:
	typedef std::unordered_map<std::string, CSprite*> SpriteUMap;
	SpriteUMap	m_Sprites;
};


#endif  //_SPRITE_FACTORY_