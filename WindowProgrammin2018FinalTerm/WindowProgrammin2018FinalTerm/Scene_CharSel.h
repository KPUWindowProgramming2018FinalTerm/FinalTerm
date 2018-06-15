#pragma once
#include "Scene.h"

class Scene_Charsel : public CScene
{
public:
	Scene_Charsel();
	~Scene_Charsel();

	bool OnCreate() override;
	void BuildObjects() override;
	void Update(float fTimeElapsed) override;	// m_pCurrScene->Update();
	void Render(HDC hdc) override;				// FrameAdvanced
	
												// m_pCurrScene->Render(m_hdc);
	void KeyState();


private:
	int windowX = ::GetSystemMetrics(SM_CXSCREEN);  //����� x����
	int windowY = ::GetSystemMetrics(SM_CYSCREEN);  //����� y����


	//����̾�
	CImage I_BG;
	//���ʿ� ǥ�õ� ĳ���� �Դϴ�
	CImage I_charL[4];
	//�����ʿ� ǥ�õ� ĳ���� �Դϴ�.
	CImage I_charR[4];

	//���� �Ϸ�Ǿ����� ǥ���� �̹����Դϴ�.
	CImage I_Ready;

	CImage I_list;

	CImage num[10];

	//���õ� ĳ�����Դϴ�.
	int choice1=1,choice2=1;
	//���� �Ǿ����� üũ�մϴ�.
	bool ready1 = false, ready2 = false;

	int timer;
	int count;

	bool Finish = false;

	bool P2_L, P2_R;
	WCHAR LoadText[100];

};
