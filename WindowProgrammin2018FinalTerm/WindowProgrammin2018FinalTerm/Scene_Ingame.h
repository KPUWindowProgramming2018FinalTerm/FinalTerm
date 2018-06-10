#pragma once
#include "Scene.h"

class CObject_Player;

class CIngameScene : public CScene
{
public:
	CIngameScene();
	~CIngameScene();
	CIngameScene(SceneTag tag, CFramework * pFramework);

	bool OnCreate() override;
	void BuildObjects() override;
	void Render(HDC hdc) override;				// FrameAdvanced
	void Update(float fTimeElapsed) override;	// m_pCurrScene->Update();
												// m_pCurrScene->Render(m_hdc);
private:
	CObject** ppObjects = NULL;
	int nObjects;

	CImage C_Tile[3];
	CImage C_Numbers[10];

	BOOL keydown;
	BOOL keydownList[14] = { 0 };
	bool p1key = false;
	bool p2key = false;

	int Tileindex[100][100] = { 0 };
};