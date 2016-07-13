#include "Tile.h"
#include "SpriteFactory.h"


CTile::CTile()
: m_pSprite(NULL)
, m_src({ 0, 0, 0, 0 })
, m_Name()
{

}

bool CTile::Init(const std::string& name, const sRect& src, const std::string& img)
{
	m_Name = name;
	m_src = src;
	m_pSprite = CSpriteFactory::GetInstancePtr()->Create(img);
	return m_pSprite;
}

void CTile::Draw(const sRect& dest)
{
	if (!m_pSprite)
	{
		return;
	}
	m_pSprite->Draw(GetRect(), dest);
}