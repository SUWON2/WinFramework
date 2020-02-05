#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

class Scene final
{
public:
	Scene() = default;

	Scene(const Scene&) = delete;

	Scene& operator=(const Scene&) = delete;

	~Scene() = default;

	void Initialize();

	void UpdateLogic();

	void Draw(HDC hdc);
};