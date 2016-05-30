#include "Graphics.h"
#include "Log/CLog.h"
#include "Game/GameController.h"
#include "Game/Level1.h"
#include "Convert.h"



int g_WindowWidth			= 800;
int g_WindowHeight			= 600;
bool g_WindowShouldClose	= false;
WCHAR g_WindowTitle[]		= L"Tank 1990";


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_CLOSE)
	{
		g_WindowShouldClose = true;
		return 0;
	}
	else if (message == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}
	else if (message == WM_KEYDOWN)
	{
		CGameController::KeyEvent(wParam, true);
	}
	else if (message == WM_KEYUP)
	{
		CGameController::KeyEvent(wParam, false);
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance,	HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WCHAR	class_name[] = L"TANK1990CLASS"; 
	HWND		windowHandle;

	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	if (SUCCEEDED(CoInitialize(NULL)))
	{
		WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = sizeof(LONG_PTR);
		wcex.hInstance = hInstance;
		wcex.hbrBackground = NULL;
		wcex.lpszMenuName = NULL;
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.lpszClassName = class_name;

		if (!RegisterClassEx(&wcex))
		{
			g_Log.write("RegisterClassEx failed...");
			return 1;
		}

		RECT windowRect = {0, 0, g_WindowWidth, g_WindowHeight};
		AdjustWindowRectEx(&windowRect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);
		windowHandle = CreateWindow(
				class_name,
				g_WindowTitle,
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				windowRect.right - windowRect.left,
				windowRect.bottom - windowRect.top,
				NULL,
				NULL,
				hInstance,
				NULL
			);

		if (!windowHandle)
		{
			g_Log.write("CreateWindow failed...");
			return 1;
		}

		ShowWindow(windowHandle, SW_SHOWNORMAL);
		UpdateWindow(windowHandle);
		CoUninitialize();
	}
	
	//---------------------------------------------------
	// ≥ı ºªØ
	//---------------------------------------------------

	g_Graphics.Init(windowHandle);
	CGameController::LoadInitialLevel(new CLevel1);

	MSG msg;
	msg.message = WM_NULL;
	int fps = 30;
	int last_time = GetTickCount();
	while (!g_WindowShouldClose)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				g_WindowShouldClose = true;
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		CGameController::Update(fps / 1000.0f);
		g_Graphics.BeginDraw();
		g_Graphics.ClearScreen(0, 0, 0);
		CGameController::Render();
		g_Graphics.EndDraw();
		while (static_cast<float>(GetTickCount() - last_time) < 1000.0f / fps);
		last_time = GetTickCount();
	}

	return 0;
}

std::string utf8_encode(const std::wstring &wstr)
{
	if (wstr.empty()) return std::string();
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
	return strTo;
}

// Convert an UTF8 string to a wide Unicode String
std::wstring utf8_decode(const std::string &str)
{
	if (str.empty()) return std::wstring();
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}