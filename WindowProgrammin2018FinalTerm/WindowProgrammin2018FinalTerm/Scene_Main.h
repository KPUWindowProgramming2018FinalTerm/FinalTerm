#pragma once
#include "Scene.h"

class CMainScene : public CScene
{
public:
	CMainScene();
	~CMainScene();

	bool OnCreate() override;
	void BuildObjects() override;
	void Render(HDC hdc) override;				// FrameAdvanced
	void Update(float fTimeElapsed) override;	// m_pCurrScene->Update();
												// m_pCurrScene->Render(m_hdc);
private:
	CObject** ppObjects;
	int nObjects;
};