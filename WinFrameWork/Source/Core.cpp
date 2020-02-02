#include "Core.h"
#include "Input.h"
#include "CoreKey.h"
#include "Defined.h"

Scene MainScene;

Core::~Core()
{
}

void Core::Run(HINSTANCE hInstance)
{
	ASSERT(hInstance != nullptr, "The hInstance must not be null");

	const char* applicationName = "WinFrmeWork";

	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wcex.lpszMenuName = applicationName;
	wcex.lpszClassName = applicationName;
	wcex.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	if (RegisterClassEx(&wcex) == false)
	{
		ASSERT(false, "Failed to call RegisterClassEx()");
	}

	const HWND hWnd = CreateWindow(applicationName, applicationName, WS_OVERLAPPEDWINDOW,
		0, 0, 800, 600, nullptr, nullptr, hInstance, nullptr);

	ASSERT(hWnd != nullptr, "Failed to call CreateWindow()");
	ShowWindow(hWnd, SW_SHOW);

	MainScene.Initialize();

	MSG msg = {};

	do
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			MainScene.UpdateLogic();
		}
	}
	while (msg.message != WM_QUIT);
}

LRESULT CALLBACK Core::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static PAINTSTRUCT paint = {};

	switch (msg)
	{
		case WM_PAINT:
		{
			const HDC hdc = BeginPaint(hWnd, &paint);
			MainScene.Draw(hdc);
			EndPaint(hWnd, &paint);

			return 0;
		}

		case WM_KEYDOWN:
		case WM_KEYUP:
			Input::Get()._UpdateKeyState({}, wParam, WM_KEYUP - msg);
			return 0;

		case WM_MOUSEMOVE:
			Input::Get()._UpdateMousePosition({}, { static_cast<short>(LOWORD(lParam)), static_cast<short>(HIWORD(lParam)) });
			return 0;

		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
			Input::Get()._UpdateMouseButtonState({}, 0, WM_LBUTTONUP - msg);
			return 0;

		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
			Input::Get()._UpdateMouseButtonState({}, 1, WM_RBUTTONUP - msg);
			return 0;

		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
			Input::Get()._UpdateMouseButtonState({}, 2, WM_MBUTTONUP - msg);
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
