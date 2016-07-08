#include "Convert.h"
#include "Sprite.h"

CSprite::CSprite()
	:m_ImgName("")
	, m_pBitmap(NULL)
	, m_fOpacity(1.0f)
{
}

bool CSprite::Init(const std::string& bname, float opacity = 1.0f)
{
	if (bname != m_ImgName)
	{
		return false;
	}
	
	m_ImgName = bname;
	std::wstring wbname = utf8_decode(bname);
	HRESULT hr = g_Graphics.LoadBitmapFromFile(wbname.c_str(), &m_pBitmap);
	
	SetOpacity(opacity);
	return SUCCEEDED(hr);
}

void CSprite::Release()
{
	if (m_pBitmap)
	{
		SAFE_DELETE(m_pBitmap);
	}
}

void CSprite::Draw(const sRect& dest)
{
	D2D1_SIZE_F& sz = m_pBitmap->GetSize();
	Draw({ 0, 0, sz.width, sz.height }, dest);
}


void CSprite::Draw(const sRect& src, const sRect& dest)
{
	ID2D1HwndRenderTarget* prt = g_Graphics.GetRenderTarget();
	if (!prt) return;


	D2D1_RECT_F destx = D2D1::RectF(dest.left, dest.top, dest.right, dest.bottom),
				srcx = D2D1::RectF(src.left, src.top, src.right, src.bottom);

	prt->DrawBitmap(m_pBitmap, destx, m_fOpacity, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, srcx);
}