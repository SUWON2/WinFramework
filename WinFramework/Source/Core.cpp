#include "Core.h"
#include "Input.h"
#include "Defined.h"

static constexpr int SCREEN_WIDTH = 800;
static constexpr int SCREEN_HEIGHT = 600;
static constexpr int SCREEN_POSITION_X = 0;
static constexpr int SCREEN_POSITION_Y = 0;

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

	RECT windowRectangle = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	AdjustWindowRect(&windowRectangle, WS_OVERLAPPEDWINDOW, FALSE);

	const HWND hWnd = CreateWindow(applicationName, applicationName, WS_OVERLAPPEDWINDOW,
		windowRectangle.left + SCREEN_POSITION_X, SCREEN_POSITION_Y, windowRectangle.right - windowRectangle.left, windowRectangle.bottom - windowRectangle.top
		, nullptr, nullptr, hInstance, nullptr);

	ASSERT(hWnd != nullptr, "Failed to call CreateWindow()");
	ShowWindow(hWnd, SW_SHOW);

	MainScene.Initialize(hWnd);

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
			Sleep(16); // HACK: CPU 사용률 낮추기 위한 임시로 처리합니다.

			MainScene.UpdateLogic();

			Input::Get()._Renew();
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

		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
			if (wParam == VK_MENU)
			{
				Input::Get()._SetKey(wParam, WM_SYSKEYUP - msg);
				return 0;
			}
			break;

		case WM_KEYDOWN:
		case WM_KEYUP:
			Input::Get()._SetKey(wParam, WM_KEYUP - msg);
			return 0;

		case WM_MOUSEMOVE:
			Input::Get()._SetMousePosition({ static_cast<short>(LOWORD(lParam)), static_cast<short>(HIWORD(lParam)) });
			return 0;

		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
			Input::Get()._SetMouseButton(Input::eMouseButton::Left, WM_LBUTTONUP - msg);
			return 0;

		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
			Input::Get()._SetMouseButton(Input::eMouseButton::Right, WM_RBUTTONUP - msg);
			return 0;

		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
			Input::Get()._SetMouseButton(Input::eMouseButton::Middle, WM_MBUTTONUP - msg);
			return 0;

		case WM_MOUSEWHEEL:
			Input::Get()._SetMouseScrollWheel(static_cast<short>(HIWORD(wParam)));
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
