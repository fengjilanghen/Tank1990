#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "global_def.h"
#include "Graphics.h"
#include "XmlParser.h"
#include "SpriteAnimator.h"
#include "SpriteSheet.h"
#include <string>


class CSprite
{
public:
	enum eSprite_Type
	{
		ST_NONE = 0,
		ST_NORMAL,
		ST_ANIMATOR,
		ST_SHEET,
		ST_COUNT,
	};

	union uSpriteAttach
	{
		CSpriteAnimator*		pAnimator;
		CSpriteSheet*			pSheet;
	};

public:
	CSprite();
	virtual ~CSprite();
	virtual bool Init(eSprite_Type type, const std::string& fname, float opacity = 1.0f);
	virtual void Release();
	
	inline void SetOpacity(float opacity) { m_fOpacity = min(max(opacity, 0.f), 1.f); }
	inline bool IsLoaded() { return m_bLoaded; }
	inline uSpriteAttach* GetAttachPtr(){ return &m_Attach; }

	void Update(float delta_time);
	void Draw(const sRect& dest, int index = 0);

protected:
	bool InitAnimator(const std::string& fname);
	bool InitSheet(const std::string& fname);
	bool SetBitmap(const std::string& bname);
	void getAttribValue(std::string &o_value, const AttribsPtrUMap& i_apm, const std::string& i_key);

protected:
	std::string		m_ImgName;
	ID2D1Bitmap*	m_pBitmap;
	float			m_fOpacity;

	eSprite_Type	m_Type;
	uSpriteAttach	m_Attach;

	bool			m_bLoaded;
	
};


#endif //_SPRITE_H_