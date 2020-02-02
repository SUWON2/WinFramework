#include "Scene.h"
#include "Input.h"

void Scene::Initialize()
{
}

void Scene::UpdateLogic()
{
}

void Scene::Draw(HDC hdc)
{
	// 가로 선을 그린다.
	MoveToEx(hdc, 0, 599 / 2, nullptr);
	LineTo(hdc, 799, 599 / 2);

	// 세로 선을 그린다.
	MoveToEx(hdc, 799 / 2, 0, nullptr);
	LineTo(hdc, 799 / 2, 599);
}
