#ifndef _TILE_H_
#define _TILE_H_
#include "global_def.h"
#include "IRenderObject.h"
#include "Sprite.h"
#include <string>

class CTile:public IRenderObject
{
public:
	CTile();
	bool Init(const std::string& name, const sRect& src, const std::string& img);
	void Release(){}
	virtual void Draw(const sRect& dest) override;

	inline const sRect& GetRect() const { return m_src; }
	inline const std::string& GetName() const { return m_Name; }

protected:
	void Draw(const sRect& src, const sRect& dest) override{}

private:
	CSprite*			m_pSprite;
	sRect				m_src;
	std::string			m_Name;
};

#endif //_TILE_H_