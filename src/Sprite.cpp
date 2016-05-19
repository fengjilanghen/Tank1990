#include "Sprite.h"
#include "Convert.h"

const D2D1_POINT_2F CSprite::DEFAULT_ANCHOR = D2D1::Point2F(0, 0);

CSprite::CSprite()
	: m_BitmapName("")
	, m_Anchor(DEFAULT_ANCHOR)
	, m_pBitmap(NULL)
{

}

CSprite::~CSprite()
{
	Release();
}

void CSprite::Init(const char* bname, const D2D1_POINT_2F &anchor)
{
	SetBitmap(bname);
	SetAnchor(anchor);
}

void CSprite::Release()
{
	m_BitmapName = "";
	m_Anchor = DEFAULT_ANCHOR;
	SafeRelease(&m_pBitmap);
}

void CSprite::SetBitmap(const char* bname)
{
	if (bname != m_BitmapName)
	{
		Release();
	}
	m_BitmapName = bname;
	std::wstring wbname = utf8_decode(bname);
	g_Graphics.LoadBitmapFromFile(wbname.c_str(), &m_pBitmap);
}

void CSprite::Draw(float x, float y, float opacity/* = 1.0f*/)
{
	if (!m_pBitmap) return;
	ID2D1HwndRenderTarget* prt = g_Graphics.GetRenderTarget();
	if (!prt) return;
	
	D2D1_SIZE_F sz = m_pBitmap->GetSize();
	D2D1_RECT_F dest = D2D1::RectF(x, y, x + sz.width, y + sz.height);

	prt->DrawBitmap(m_pBitmap, dest, opacity, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
}

void CSprite::Draw(const D2D1_POINT_2F &pos, const D2D1_RECT_F &src, float opacity/* = 1.0f*/)
{
	if (!m_pBitmap) return;
	ID2D1HwndRenderTarget* prt = g_Graphics.GetRenderTarget();

	D2D1_SIZE_F sz = m_pBitmap->GetSize();
	float	x = pos.x,
			y = pos.y;
	D2D1_RECT_F dest = D2D1::RectF(x, y, x + sz.width, y + sz.height);
	prt->DrawBitmap(m_pBitmap, dest, opacity, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, src);
}

void CSprite::Draw(const D2D1_RECT_F &dest, const D2D1_RECT_F &src, float opacity/* = 1.0f*/)
{
	if (!m_pBitmap) return;
	ID2D1HwndRenderTarget* prt = g_Graphics.GetRenderTarget();

	prt->DrawBitmap(m_pBitmap, dest, opacity, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, src);
}