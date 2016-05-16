#include "Graphics.h"
#include "Log/CLog.h"

Graphics g_Graphics;

Graphics::Graphics()
	: m_pD2DFactory(NULL)
	, m_pRenderTarget(NULL)
	, m_pWICFactory(NULL)
	, m_pDWriteFactory(NULL)
	, m_pTextFormat(NULL)
{

}

Graphics::~Graphics()
{
	SafeRelease(&m_pD2DFactory);
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pWICFactory);
	SafeRelease(&m_pDWriteFactory);
	SafeRelease(&m_pTextFormat);
}

bool Graphics::Init(HWND windowHandle)
{
	const WCHAR	msc_fontName[]	= L"Verdana";
	const float msc_fontSize	= 50;
	HRESULT		hr;
	ID2D1GeometrySink *pSink = NULL;
	
	hr= D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
	if (FAILED(hr))
	{
		g_Log.write("Graphics::Init D2D1CreateFactory failed...");
		return false;
	}

	{
		RECT rc;
		GetClientRect(windowHandle, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top
			);
		hr = m_pD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(windowHandle, size),
			&m_pRenderTarget
			);

		if (FAILED(hr))
		{
			g_Log.write("Graphics::Init CreateHwndRenderTarget failed...");
			return false;
		}

	}

	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(m_pDWriteFactory),
		reinterpret_cast<IUnknown **>(&m_pDWriteFactory)
		);

	if (FAILED(hr))
	{
		g_Log.write("Graphics::Init DWriteCreateFactory failed...");
		return false;
	}
	
	hr = m_pDWriteFactory->CreateTextFormat(
		msc_fontName,
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		msc_fontSize,
		L"", //locale
		&m_pTextFormat
		);
	
	if (FAILED(hr))
	{
		g_Log.write("Graphics::Init CreateTextFormat failed...");
		return false;
	}

	m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	SafeRelease(&pSink);
}

void Graphics::DrawCircle(float x, float y, float radiusX, float radiusY)
{
	D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F(x, y), radiusX, radiusY);
	ID2D1SolidColorBrush* brush;
	m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(1.f, 0.f, 0.f), &brush);
	m_pRenderTarget->DrawEllipse(&ellipse, brush);
}