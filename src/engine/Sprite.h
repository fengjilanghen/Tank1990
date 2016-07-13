#ifndef _SPRITE_H_
#define _SPRITE_H_
#include "global_def.h"
#include "Graphics.h"
#include <string>


class CSprite
{
public:
	CSprite();
	~CSprite();

	bool Init(const std::string& bname, float opacity = 1.0f);
	void Release();

	void Draw(const sRect& dest); 
	void Draw(const sRect& src, const sRect& dest);

	inline void SetOpacity(float opacity) { m_fOpacity = min(max(opacity, 0.f), 1.f); }

protected:
	std::string		m_ImgName;
	ID2D1Bitmap*	m_pBitmap;
	float			m_fOpacity;	
};


#endif //_SPRITE_H_