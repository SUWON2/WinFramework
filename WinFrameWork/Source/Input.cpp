#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include "Input.h"

Input& Input::Get()
{
	static Input input;
	return input;
}

bool Input::GetKey(const short virtualKey) const
{
	ASSERT(0 <= virtualKey && virtualKey < VIRTUAL_KEY_COUNT, "지원하지 않는 키입니다.");
	return mIsPressedKeys[virtualKey];
}

bool Input::GetKeyDown(const short virtualKey)
{
	ASSERT(0 <= virtualKey && virtualKey < VIRTUAL_KEY_COUNT, "지원하지 않는 키입니다.");
	return mIsKeyStateChanged[virtualKey] && mIsPressedKeys[virtualKey];
}

bool Input::GetKeyUp(const short virtualKey)
{
	ASSERT(0 <= virtualKey && virtualKey < VIRTUAL_KEY_COUNT, "지원하지 않는 키입니다.");
	return mIsKeyStateChanged[virtualKey] && !mIsPressedKeys[virtualKey];
}

const POINT& Input::GetMousePosition() const
{
	return mMousePosition;
}

bool Input::GetMouseButton(const int button) const
{
	ASSERT(0 <= button && button < MOUSE_BUTTON_CUONT, "지원하지 않는 버튼입니다.");
	return mIsPressedMouseButton[button];
}

bool Input::GetMouseButtonDown(const int button)
{
	ASSERT(0 <= button && button < MOUSE_BUTTON_CUONT, "지원하지 않는 버튼입니다.");
	return mIsMouseButtonStateChanged[button] && mIsPressedMouseButton[button];
}

bool Input::GetMouseButtonUp(const int button)
{
	ASSERT(0 <= button && button < MOUSE_BUTTON_CUONT, "지원하지 않는 버튼입니다.");
	return mIsMouseButtonStateChanged[button] && !mIsPressedMouseButton[button];
}

int Input::GetMouseScrollWheel() const
{
	return mMouseScrollWheel;
}

bool Input::IsCursorVisible() const
{
	return mIsCursorVisible;
}

void Input::SetVisibleCursor(const bool isVisible)
{
	if (mIsCursorVisible != isVisible)
	{
		mIsCursorVisible = isVisible;
		ShowCursor(mIsCursorVisible);
	}
}

void Input::_Renew(CoreKey)
{
	memset(mIsKeyStateChanged, false, sizeof(bool) * VIRTUAL_KEY_COUNT);
	memset(mIsMouseButtonStateChanged, false, sizeof(bool) * MOUSE_BUTTON_CUONT);
	mMouseScrollWheel = 0;
}

void Input::_SetKey(CoreKey, const UINT_PTR key, const bool bPressed)
{
	mIsKeyStateChanged[key] = (mIsPressedKeys[key] != bPressed);
	mIsPressedKeys[key] = bPressed;
}

void Input::_SetMousePosition(CoreKey, const POINT& mousePosition)
{
	mMousePosition = mousePosition;
}

void Input::_SetMouseButton(CoreKey, const int button, const bool bPressed)
{
	ASSERT(0 <= button && button < MOUSE_BUTTON_CUONT, "지원하지 않는 버튼입니다.");
	mIsMouseButtonStateChanged[button] = (mIsPressedMouseButton[button] != bPressed);
	mIsPressedMouseButton[button] = bPressed;
}

void Input::_SetMouseScrollWheel(CoreKey, const int scrollWheel)
{
	mMouseScrollWheel += scrollWheel;
}