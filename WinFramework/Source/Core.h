#pragma once

#include "Scene.h"

class Core final
{
public:
	Core() = default;

	Core(const Core&) = delete;

	Core& operator=(const Core&) = delete;

	~Core();

	void Run(HINSTANCE hInstance);

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};