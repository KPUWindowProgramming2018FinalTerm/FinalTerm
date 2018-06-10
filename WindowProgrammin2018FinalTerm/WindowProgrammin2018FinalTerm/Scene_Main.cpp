#include "stdafx.h"
#include "Scene_Main.h"
#include "Object.h"

CMainScene::CMainScene()
{

}


CMainScene::~CMainScene()
{
}

bool CMainScene::OnCreate()
{
	return false;
}

void CMainScene::BuildObjects()
{
	/*CObject** ppObjects;
	int nObjects; 여기다 값넣기*/

}

void CMainScene::Render(HDC hdc)
{

	for (int i = 0; i < nObjects; ++i)
		ppObjects[i]->Render(hdc);
}

void CMainScene::Update(float fTimeElapsed)
{

	for (int i = 0; i < nObjects; ++i)
	ppObjects[i]->Update(fTimeElapsed);
}
