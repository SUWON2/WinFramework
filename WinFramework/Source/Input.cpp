#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include "Input.h"

Input& Input::Get()
{
	static Input input;
	return input;
}

bool Input::GetKey(int virtualKey) const
{
	ASSERT(0 <= virtualKey && virtualKey < VIRTUAL_KEY_COUNT, "지원하지 않는 키입니다.");
	return mbPressedKeys[virtualKey];
}

bool Input::GetKeyDown(int virtualKey) const
{
	ASSERT(0 <= virtualKey && virtualKey < VIRTUAL_KEY_COUNT, "지원하지 않는 키입니다.");
	return mbChangedKeysState[virtualKey] && mbPressedKeys[virtualKey];
}

bool Input::GetKeyUp(int virtualKey) const
{
	ASSERT(0 <= virtualKey && virtualKey < VIRTUAL_KEY_COUNT, "지원하지 않는 키입니다.");
	return mbChangedKeysState[virtualKey] && !mbPressedKeys[virtualKey];
}

const POINT& Input::GetMousePosition() const
{
	return mMousePosition;
}

bool Input::GetMouseButton(eMouseButton button) const
{
	return mbPressedMouseButtons[(int)button];
}

bool Input::GetMouseButtonDown(eMouseButton button) const
{
	int buttonByInt = (int)button;
	return mbChangedMouseButtonsState[buttonByInt] && mbPressedMouseButtons[buttonByInt];
}

bool Input::GetMouseButtonUp(eMouseButton button) const
{
	int buttonByInt = (int)button;
	return mbChangedMouseButtonsState[buttonByInt] && !mbPressedMouseButtons[buttonByInt];
}

int Input::GetMouseScrollWheel() const
{
	return mMouseScrollWheel;
}

bool Input::IsCursorVisible() const
{
	return mbCursorVisible;
}

void Input::SetVisibleCursor(bool bVisible)
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
	memset(mbChangedMouseButtonsState, false, sizeof(bool) * (int)eMouseButton::Count);
	mMouseScrollWheel = 0;
}

void Input::_SetKey(UINT_PTR key, bool bPressed)
{
	mbChangedKeysState[key] = (mbPressedKeys[key] != bPressed);
	mbPressedKeys[key] = bPressed;
}

void Input::_SetMousePosition(const POINT& mousePosition)
{
	mMousePosition = mousePosition;
}

void Input::_SetMouseButton(eMouseButton button, bool bPressed)
{
	int buttonByInt = (int)button;
	mbChangedMouseButtonsState[buttonByInt] = (mbPressedMouseButtons[buttonByInt] != bPressed);
	mbPressedMouseButtons[buttonByInt] = bPressed;
}

void Input::_SetMouseScrollWheel(int scrollWheel)
{
	mMouseScrollWheel += scrollWheel;
}