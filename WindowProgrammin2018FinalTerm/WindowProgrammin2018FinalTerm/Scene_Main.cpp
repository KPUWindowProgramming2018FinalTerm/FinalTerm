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
	CheckKey = false;

	MainTitle.Load(L"Graphic\\UI\\MAINTITLE.png");


	return false;
}

void CMainScene::BuildObjects()
{


}

void CMainScene::Render(HDC hdc)
{

	
}

void CMainScene::Update(float fTimeElapsed)
{



}
