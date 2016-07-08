#ifndef _SHEET_H_
#define _SHEET_H_

#include "global_def.h"
#include "Sprite.h"
#include "IRenderObject.h"
#include <unordered_map>
#include <string>

class CSheet : public IRenderObject
{
public:
	typedef std::unordered_map<int, sRect>	PageUMap;

public:
	CSheet();

	bool Init(const std::string& fname);
	void Release();

	virtual void Update(float delta_time) override;
	virtual void Draw() override;

protected:
	bool AddSheetPage(int index, const sRect& rect);
	sRect GetSheetPage(int index); 
	void getAttribValue(std::string &o_value, const AttribsPtrUMap& i_apm, const std::string& i_key);
	
private:
	CSprite*		m_pSprite;
	PageUMap		m_umPages;
};


#endif //_SHEET_H_
