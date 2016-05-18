#include "Graphics.h"
#include "Log/CLog.h"
#include "Game/GameController.h"
#include "Game/Level1.h"



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

	DefWindowProc(hWnd, message, wParam, lParam);
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

		g_Graphics.BeginDraw();
		CGameController::Update();
		CGameController::Render();
		g_Graphics.EndDraw();

	}

	return 0;
}