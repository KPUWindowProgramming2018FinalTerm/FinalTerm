#include "stdafx.h"
#include "Scene_CharSel.h"

Scene_Charsel::Scene_Charsel()
{
	this->x = 0;
	this->y = 0;
}

Scene_Charsel::~Scene_Charsel()
{
}

bool Scene_Charsel::OnCreate()
{
	this->x = 0;
	this->y = 0;
	return false;
}

void Scene_Charsel::BuildObjects()
{

}

void Scene_Charsel::Update(float fTimeElapsed)
{
	if (GetAsyncKeyState(VK_DOWN))
	{
		this->y += 5;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		this->x += 5;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		this->x -= 5;
	}
	if (GetAsyncKeyState(VK_UP))
	{
		this->y -= 5;
	}
}

void Scene_Charsel::Render(HDC hdc)
{
	Ellipse(hdc, x, y, 50+x, 50+y);
}


