#pragma once

#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

template<class Interface>
inline void
SafeRelease(
Interface **ppInterfaceToRelease
)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
}


class Graphics
{
private:
	ID2D1Factory*			m_pD2DFactory;
	ID2D1HwndRenderTarget*	m_pRenderTarget;
	IWICImagingFactory*		m_pWICFactory;
	IDWriteFactory*			m_pDWriteFactory;
	IDWriteTextFormat*		m_pTextFormat;

public:
	Graphics();
	~Graphics();

	bool Init(HWND windowHandle);
	void BeginDraw() { m_pRenderTarget->BeginDraw(); }
	void EndDraw() { m_pRenderTarget->EndDraw(); }
	void ClearScreen(float r, float g, float b) { m_pRenderTarget->Clear(D2D1::ColorF(r, g, b)); }
	void DrawCircle(float x, float y, float radiusX, float radiusY);
};


extern Graphics g_Graphics;