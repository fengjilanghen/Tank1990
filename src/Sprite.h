#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Graphics.h"
#include <string>

class CSprite
{
public:
	static const D2D1_POINT_2F DEFAULT_ANCHOR;
public:
	CSprite();
	~CSprite();
	void Init(const char* bname, const D2D1_POINT_2F &anchor = DEFAULT_ANCHOR);
	void Release();

	inline void SetBitmap(const char* bname);
	inline void SetAnchor(const D2D1_POINT_2F	&anchor) { m_Anchor = anchor; }

	void Draw(float x, float y, float opacity = 1.0f);
	void Draw(const D2D1_POINT_2F &dest, const D2D1_RECT_F &src, float opacity = 1.0f);
	void Draw(const D2D1_RECT_F &dest, const D2D1_RECT_F &src, float opacity = 1.0f);


protected:
	std::string		m_BitmapName;
	ID2D1Bitmap*	m_pBitmap;
	D2D1_POINT_2F	m_Anchor;
};


#endif //_SPRITE_H_