#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include "Input.h"

Input& Input::Get()
{
	static Input input;
	return input;
}

bool Input::GetKey(const int virtualKey) const
{
	ASSERT(0 <= virtualKey && virtualKey < VIRTUAL_KEY_COUNT, "지원하지 않는 키입니다.");
	return mbPressedKeys[virtualKey];
}

bool Input::GetKeyDown(const int virtualKey) const
{
	ASSERT(0 <= virtualKey && virtualKey < VIRTUAL_KEY_COUNT, "지원하지 않는 키입니다.");
	return mbChangedKeysState[virtualKey] && mbPressedKeys[virtualKey];
}

bool Input::GetKeyUp(const int virtualKey) const
{
	ASSERT(0 <= virtualKey && virtualKey < VIRTUAL_KEY_COUNT, "지원하지 않는 키입니다.");
	return mbChangedKeysState[virtualKey] && !mbPressedKeys[virtualKey];
}

const POINT& Input::GetMousePosition() const
{
	return mMousePosition;
}

bool Input::GetMouseButton(const int button) const
{
	ASSERT(0 <= button && button < MOUSE_BUTTON_CUONT, "지원하지 않는 버튼입니다.");
	return mbPressedMouseButtons[button];
}

bool Input::GetMouseButtonDown(const int button) const
{
	ASSERT(0 <= button && button < MOUSE_BUTTON_CUONT, "지원하지 않는 버튼입니다.");
	return mbChangedMouseButtonsState[button] && mbPressedMouseButtons[button];
}

bool Input::GetMouseButtonUp(const int button) const
{
	ASSERT(0 <= button && button < MOUSE_BUTTON_CUONT, "지원하지 않는 버튼입니다.");
	return mbChangedMouseButtonsState[button] && !mbPressedMouseButtons[button];
}

int Input::GetMouseScrollWheel() const
{
	return mMouseScrollWheel;
}

bool Input::IsCursorVisible() const
{
	return mbCursorVisible;
}

void Input::SetVisibleCursor(const bool bVisible)
{
	if (mbCursorVisible != bVisible)
	{
		mbCursorVisible = bVisible;
		ShowCursor(mbCursorVisible);
	}
}

void Input::_Renew()
{
	memset(mbChangedKeysState, false, sizeof(bool) * VIRTUAL_KEY_COUNT);
	memset(mbChangedMouseButtonsState, false, sizeof(bool) * MOUSE_BUTTON_CUONT);
	mMouseScrollWheel = 0;
}

void Input::_SetKey(const UINT_PTR key, const bool bPressed)
{
	mbChangedKeysState[key] = (mbPressedKeys[key] != bPressed);
	mbPressedKeys[key] = bPressed;
}

void Input::_SetMousePosition(const POINT& mousePosition)
{
	mMousePosition = mousePosition;
}

void Input::_SetMouseButton(const int button, const bool bPressed)
{
	ASSERT(0 <= button && button < MOUSE_BUTTON_CUONT, "지원하지 않는 버튼입니다.");
	mbChangedMouseButtonsState[button] = (mbPressedMouseButtons[button] != bPressed);
	mbPressedMouseButtons[button] = bPressed;
}

void Input::_SetMouseScrollWheel(const int scrollWheel)
{
	mMouseScrollWheel += scrollWheel;
}