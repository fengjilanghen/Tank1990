#include "Convert.h"
#include "Sprite.h"


//////////////////////////////////////////////////////////////////////
//
//	macro defines
//
//////////////////////////////////////////////////////////////////////
#define ASSERT_EMPTY_RETURN(str) if (str.empty()) { ASSERT(false);	return false;	}
#define ASSERT_RETURN(exp) if (!(exp)) { ASSERT(false);	return false;	}


//////////////////////////////////////////////////////////////////////
//
//	extern claims
//
//////////////////////////////////////////////////////////////////////
//extern int g_WindowWidth, g_WindowHeight;

CSprite::CSprite()
	:m_ImgName("")
	, m_pBitmap(NULL)
	, m_fOpacity(1.0f)
	, m_Type(ST_NONE)
	, m_bLoaded(false)
{
	m_Attach.pAnimator = NULL;
}

CSprite::~CSprite()
{
	Release();
}

bool CSprite::Init(eSprite_Type type, const std::string& fname, float opacity/* = 1.0f*/)
{
	Release();


	switch (type)
	{
	case CSprite::ST_NORMAL:
	{
		ASSERT_RETURN(SetBitmap(fname));
	}break;
	case CSprite::ST_ANIMATOR:
	{
		ASSERT_RETURN(InitAnimator(fname));
	}break;
	case CSprite::ST_SHEET:
	{
		ASSERT_RETURN(InitSheet(fname));
	}break;
	default:
		ASSERT(false);
		break;
	}
	m_Type = type;
	m_bLoaded = true;
}

void CSprite::Release()
{
	m_ImgName = "";
	m_bLoaded = false;

	if (m_Type == ST_ANIMATOR)
	{
		SAFE_DELETE(m_Attach.pAnimator);
	}
	else if (m_Type == ST_SHEET)
	{
		SAFE_DELETE(m_Attach.pSheet);
	}

	m_Type = ST_NONE;
	m_fOpacity = 1.0f;
	m_pBitmap = NULL;
}


void CSprite::Draw(const sRect& dest, int index/* = 0*/)
{
	if (!IsLoaded()) return;

	ID2D1HwndRenderTarget* prt = g_Graphics.GetRenderTarget();
	if (!prt) return;


	D2D1_RECT_F destx, srcx;
	destx = D2D1::RectF(dest.left, dest.top, dest.right, dest.bottom);
	

	sRect rect = { -1, -1, -1, -1 };
	switch (m_Type)
	{
	case ST_NORMAL:
	{
		D2D1_SIZE_F& sz = m_pBitmap->GetSize();
		srcx = D2D1::RectF(0, 0, sz.width, sz.height);
		prt->DrawBitmap(m_pBitmap, destx, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, srcx);
		return;
	}break;
	case ST_ANIMATOR:
	{
		rect = m_Attach.pAnimator->GetCurFrameRect();
	}break;
	case ST_SHEET:
	{
		rect = m_Attach.pSheet->GetSheetPage(index);
	}break;
	default:
		ASSERT(false);
		return;
	}

	if (rect.left < 0)
	{
		ASSERT(false);
		return;
	}
	srcx = D2D1::RectF(rect.left, rect.top, rect.right, rect.bottom);
	prt->DrawBitmap(m_pBitmap, destx, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, srcx);
}
//////////////////////////////////////////////////////////////////////
//
//	functions called by self
//
//////////////////////////////////////////////////////////////////////
void CSprite::getAttribValue(std::string &o_value, const AttribsPtrUMap& i_apm, const std::string& i_key)
{
	o_value.clear();
	AttribsPtrUMap::const_iterator ait = i_apm.find(i_key);
	ASSERT(ait != i_apm.end());

	if (ait != i_apm.end())
	{
		o_value = ait->second;
		ASSERT(!o_value.empty())
	}
}

bool CSprite::SetBitmap(const std::string& bname)
{
	if (bname != m_ImgName)
	{
		SafeRelease(&m_pBitmap);
	}
	m_ImgName = bname;
	std::wstring wbname = utf8_decode(bname);
	HRESULT hr = g_Graphics.LoadBitmapFromFile(wbname.c_str(), &m_pBitmap);
	return SUCCEEDED(hr);
}


bool CSprite::InitAnimator(const std::string& fname)
{
	PXMLELEMENT pRoot = XmlParser::ParseFile(fname.c_str());
	ASSERT_RETURN(pRoot && pRoot->tag == "Animator");

	// 解析Animator的属性
	AttribsPtrUMap::iterator it;

	std::string str;
	int counter_max = 1;

	getAttribValue(str, pRoot->attribs, "img");
	ASSERT_EMPTY_RETURN(str);
	SetBitmap(str);

	getAttribValue(str, pRoot->attribs, "counter_max");
	if (str.empty()) return;
	counter_max = std::atoi(str.c_str());

	m_Attach.pAnimator = new CSpriteAnimator;
	CSpriteAnimator* pAni = m_Attach.pAnimator;
	ASSERT_RETURN(pAni);

	if (!pAni->BeginSet())
	{
		SAFE_DELETE(pAni);
		return;
	}

	pAni->SetCounterMax(counter_max);


	for (ChildrenPtrVec::iterator it = pRoot->children.begin(); it != pRoot->children.end(); ++it)
	{
		//解析各Action的属性
		AttribsPtrUMap::const_iterator ait;
		const AttribsPtrUMap& apm = (*it)->attribs;

		std::string name;
		int total = 0;

		getAttribValue(name, apm, "name");
		ASSERT_EMPTY_RETURN(name);

		getAttribValue(str, apm, "total");
		ASSERT_EMPTY_RETURN(str);
		total = std::atoi(str.c_str());
		ASSERT(total > 0);

		// 解析frame
		CSpriteAnimator::FramesVec frames;
		for (int i = 0; i < total; ++i)
		{
			PXMLELEMENT frame = (*it)->children.at(i);
			if (!frame) return;

			const AttribsPtrUMap& frame_apm = frame->attribs;
			sRect rect;

			getAttribValue(str, frame_apm, "x");
			ASSERT_EMPTY_RETURN(str);
			rect.left = std::atoi(str.c_str());

			getAttribValue(str, frame_apm, "y");
			ASSERT_EMPTY_RETURN(str);
			rect.top = std::atoi(str.c_str());

			getAttribValue(str, frame_apm, "w");
			ASSERT_EMPTY_RETURN(str);
			rect.right = rect.left + std::atoi(str.c_str());


			getAttribValue(str, frame_apm, "h");
			ASSERT_EMPTY_RETURN(str);
			rect.bottom = rect.top + std::atoi(str.c_str());

			frames.push_back(rect);
		}

		pAni->AddAction(name, frames);
	}
	pAni->EndSet();
	return true;
}

bool CSprite::InitSheet(const std::string& fname)
{
	PXMLELEMENT pRoot = XmlParser::ParseFile(fname.c_str());
	ASSERT_RETURN(pRoot && pRoot->tag == "sheet");

	std::string str;
	getAttribValue(str, pRoot->attribs, "img");
	ASSERT_EMPTY_RETURN(str);
	SetBitmap(str);

	m_Attach.pSheet = new CSpriteSheet;
	CSpriteSheet* pSheet = m_Attach.pSheet;
	ASSERT_RETURN(pSheet);

	int size = pRoot->children.size();
	for (int i = 0; i < size; ++i)
	{
		ASSERT_RETURN(pRoot->tag != "frame");
		AttribsPtrUMap& attribs = pRoot->children[i]->attribs;

		int		type = -1;
		sRect	rect;

		getAttribValue(str, attribs, "type");
		ASSERT_EMPTY_RETURN(str);
		type = std::stoi(str);

		getAttribValue(str, attribs, "x");
		ASSERT_EMPTY_RETURN(str);
		rect.left = std::stoi(str);

		getAttribValue(str, attribs, "y");
		ASSERT_EMPTY_RETURN(str);
		rect.top = std::stoi(str);

		getAttribValue(str, attribs, "w");
		ASSERT_EMPTY_RETURN(str);
		rect.right = rect.left + std::stoi(str);

		getAttribValue(str, attribs, "h");
		ASSERT_EMPTY_RETURN(str);
		rect.bottom = rect.top + std::stoi(str);

		ASSERT_RETURN(pSheet->AddSheetPage(type, rect));
	}
	return true;
}