#pragma once

#include "Defined.h"

class Input final
{
public:
	Input(const Input&) = delete;

	Input& operator=(const Input&) = delete;

	static Input& Get();

	bool GetKey(const int virtualKey) const;

	bool GetKeyDown(const int virtualKey) const;

	bool GetKeyUp(const int virtualKey) const;

	const POINT& GetMousePosition() const;

	// button - 0: 왼쪽 버튼, 1: 오른쪽 버튼, 2: 중간 버튼
	bool GetMouseButton(const int button) const;

	// button - 0: 왼쪽 버튼, 1: 오른쪽 버튼, 2: 중간 버튼
	bool GetMouseButtonDown(const int button) const;

	// button - 0: 왼쪽 버튼, 1: 오른쪽 버튼, 2: 중간 버튼
	bool GetMouseButtonUp(const int button) const;

	int GetMouseScrollWheel() const;

	bool IsCursorVisible() const;

	void SetVisibleCursor(const bool bVisible);

public:
	void _Renew();

	void _SetKey(const UINT_PTR key, const bool bPressed);

	void _SetMousePosition(const POINT& mousePosition);

	void _SetMouseButton(const int button, const bool bPressed);

	void _SetMouseScrollWheel(const int scrollWheel);

private:
	Input() = default;

	~Input() = default;

private:
	static constexpr int VIRTUAL_KEY_COUNT = 190;

	bool mbPressedKeys[VIRTUAL_KEY_COUNT] = {};

	bool mbChangedKeysState[VIRTUAL_KEY_COUNT] = {};

	POINT mMousePosition = {};

	// 0: 왼쪽, 1: 오른쪽, 2: 중간 버튼
	static constexpr int MOUSE_BUTTON_CUONT = 3;

	bool mbPressedMouseButtons[MOUSE_BUTTON_CUONT] = {};

	bool mbChangedMouseButtonsState[MOUSE_BUTTON_CUONT] = {};

	bool mbCursorVisible = true;

	int mMouseScrollWheel = {};
};