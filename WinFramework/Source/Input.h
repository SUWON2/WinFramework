#pragma once

#include "Defined.h"

class Input final
{
public:
	enum class eMouseButton
	{
		Left,
		Right,
		Middle,
		Count // must put this at the bottom.
	};

public:
	Input(const Input&) = delete;

	Input& operator=(const Input&) = delete;

	static Input& Get();

	bool GetKey(int virtualKey) const;

	bool GetKeyDown(int virtualKey) const;

	bool GetKeyUp(int virtualKey) const;

	const POINT& GetMousePosition() const;

	bool GetMouseButton(eMouseButton button) const;

	bool GetMouseButtonDown(eMouseButton button) const;

	bool GetMouseButtonUp(eMouseButton button) const;

	int GetMouseScrollWheel() const;

	bool IsCursorVisible() const;

	void SetVisibleCursor(bool bVisible);

public:
	void _Renew();

	void _SetKey(UINT_PTR key, bool bPressed);

	void _SetMousePosition(const POINT& mousePosition);

	void _SetMouseButton(eMouseButton button, bool bPressed);

	void _SetMouseScrollWheel(int scrollWheel);

private:
	Input() = default;

	~Input() = default;

private:
	static constexpr int VIRTUAL_KEY_COUNT = 190;

	bool mbPressedKeys[VIRTUAL_KEY_COUNT] = {};

	bool mbChangedKeysState[VIRTUAL_KEY_COUNT] = {};

	POINT mMousePosition = {};

	bool mbPressedMouseButtons[(int)eMouseButton::Count] = {};

	bool mbChangedMouseButtonsState[(int)eMouseButton::Count] = {};

	bool mbCursorVisible = true;

	int mMouseScrollWheel = {};
};