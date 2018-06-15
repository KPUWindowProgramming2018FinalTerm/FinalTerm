#pragma once
#include "Scene.h"

class Scene_Charsel : public CScene
{
public:
	Scene_Charsel();
	~Scene_Charsel();
	Scene_Charsel(SceneTag tag, CFramework * pFramework);

	void OnDestroy();
	bool OnCreate() override;
	void BuildObjects() override;
	void Update(float fTimeElapsed) override;	// m_pCurrScene->Update();
	void Render(HDC hdc) override;				// FrameAdvanced
	
												// m_pCurrScene->Render(m_hdc);
	void KeyState();


private:
	int windowX = ::GetSystemMetrics(SM_CXSCREEN);  //모니터 x길이
	int windowY = ::GetSystemMetrics(SM_CYSCREEN);  //모니터 y길이


	//배경이양
	CImage I_BG;
	//왼쪽에 표시될 캐릭터 입니다
	CImage I_charL[4];
	//오른쪽에 표시될 캐릭터 입니다.
	CImage I_charR[4];

	//레디가 완료되었을때 표시할 이미지입니다.
	CImage I_Ready;

	CImage I_list;

	CImage num[10];

	//선택된 캐릭터입니다.
	int choice1,choice2;
	//레디가 되었는지 체크합니다.
	bool ready1 = false, ready2 = false;

	int timer;
	int count;

	bool Finish = false;

	bool P2_L, P2_R;
	WCHAR LoadText[100];

};
