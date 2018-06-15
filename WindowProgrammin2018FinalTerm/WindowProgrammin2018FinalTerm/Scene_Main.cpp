#include "stdafx.h"
#include "Scene_Main.h"
#include "Object.h"

CMainScene::CMainScene()
{

}


CMainScene::~CMainScene()
{
}

void CMainScene::OnDestroy() {
	MainTitle.Destroy();
	Manual[0].Destroy();
	Manual[1].Destroy();
}

bool CMainScene::OnCreate()
{
	//기본적으론 false
	CheckKey = false;
	SceneNum = 0;
	finish = false;

	MainTitle.Load(L"Graphic\\UI\\MAINTITLE.png");
	Manual[0].Load(L"Graphic\\UI\\manual1.png");
	Manual[1].Load(L"Graphic\\UI\\manual2.png");

	return false;
}

void CMainScene::BuildObjects()
{


}

void CMainScene::Render(HDC hdc)
{
	switch (SceneNum)
	{
	case 0:
		MainTitle.Draw(hdc, 0, 0, windowX, windowY);
		break;
	case 1:
		Manual[0].Draw(hdc, 0, 0, windowX, windowY);
		break;
	case 2:
		Manual[1].Draw(hdc, 0, 0, windowX, windowY);
		break;
	default:
		MainTitle.Draw(hdc, 0, 0, windowX, windowY);
		break;
	}	
}

void CMainScene::Update(float fTimeElapsed)
{
	KeyState();
}

void CMainScene::KeyState() {
	if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
		if (!CheckKey) {
			switch (SceneNum) {
			case 0:
				SceneNum = 1;
				break;
			case 1:
				SceneNum = 2;
				break;
			case 2:
				SceneNum = 3;
				break;
			case 3:
				finish = true;
				break;

			}


		}
		CheckKey = true;
	}
	else {
		CheckKey = false;
	}
}
