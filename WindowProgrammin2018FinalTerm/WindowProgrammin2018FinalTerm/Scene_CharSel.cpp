#include "stdafx.h"
#include "Scene_CharSel.h"

Scene_Charsel::Scene_Charsel()
{


}

Scene_Charsel::~Scene_Charsel()
{
}

//�����ɶ� ���� �Ϸ��� �δ�
bool Scene_Charsel::OnCreate()
{
	//�̹����� �ε��մϴ�.
	I_BG.Load(L"Graphic\\UI\\CharSel\\BG.png");
	I_charL[0].Load(L"Graphic\\UI\\CharSel\\1L.png");
	I_charL[1].Load(L"Graphic\\UI\\CharSel\\2L.png");
	I_charL[2].Load(L"Graphic\\UI\\CharSel\\3L.png");
	I_charL[3].Load(L"Graphic\\UI\\CharSel\\RL.png");

	I_charR[0].Load(L"Graphic\\UI\\CharSel\\1R.png");
	I_charR[1].Load(L"Graphic\\UI\\CharSel\\2R.png");
	I_charR[2].Load(L"Graphic\\UI\\CharSel\\3R.png");
	I_charR[3].Load(L"Graphic\\UI\\CharSel\\RR.png");

	I_Ready.Load(L"Graphic\\UI\\CharSel\\READY.png");

	I_list.Load(L"Graphic\\UI\\CharSel\\List.png");
	
	for (int i = 0; i < 10; i++) {
		wsprintf(LoadText, L"Graphic\\UI\\CharSel\\NUM\\%d.png", i);
		num[i].Load(LoadText);
	}
	

	//Ÿ�̸� �ʱ�ȭ
	timer = 60;
	count = 60;

	P2_L = false;
	P2_R = false;


	Finish = false;

	return false;
}

void Scene_Charsel::BuildObjects()
{
	



}



//Ű ���¸� �Է¹���.
void Scene_Charsel::KeyState() {
	
	//P1 ����
	if (GetAsyncKeyState(0x41) & 0x8000) {
		ready1 = true;
	}
	if (!ready1) {
		// f
		if (GetAsyncKeyState(0x46) & 0x8000) {
			switch (choice1) {
			case 1:
				choice1 = 4;
				break;
			case 2:
				choice1 = 1;
				break;
			case 3:
				choice1 = 2;
				break;
			case 4:
				choice1 = 3;
				break;
			}
		}
		// h
		if (GetAsyncKeyState(0x48) & 0x8000) {
			switch (choice1) {
			case 1:
				choice1 = 2;
				break;
			case 2:
				choice1 = 3;
				break;
			case 3:
				choice1 = 4;
				break;
			case 4:
				choice1 = 1;
				break;
			}
		}
	}
	

	//P2 ����
	if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000) {
		ready2 = true;
	}
	if (!ready2) {
		if (GetAsyncKeyState(VK_LEFT) & 0x8000 && !P2_L) {
			P2_L = true;
			switch (choice2) {
			case 1:
				choice2 = 4;
				break;
			case 2:
				choice2 = 1;
				break;
			case 3:
				choice2 = 2;
				break;
			case 4:
				choice2 = 3;
				break;
			}
		}
		else {
			P2_L = false;
		}



		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			switch (choice2) {
			case 1:
				choice2 = 2;
				break;
			case 2:
				choice2 = 3;
				break;
			case 3:
				choice2 = 4;
				break;
			case 4:
				choice2 = 1;
				break;
			}
		}
	}
	
}

// 1/60���� ������Ʈ��
void Scene_Charsel::Update(float fTimeElapsed)
{
	KeyState();
	//������� �ʾƾ��� ��� �����Ѵ�.
	if (!Finish) {
		//�� ������ üũ
		if (count == 0) {
			count = 60;
			timer--;
		}
		else {
			count--;
		}

		//Ÿ�̸Ӱ� 0�̵Ǹ� ������ ���� ��Ŵ
		if (timer == 0) {
			ready1 = true;
			ready2 = true;
		}

		//�Ѵ� ���̸� �ǴϽ�
		if (ready1&&ready2) {
			Finish = true;
		}



	}
}

void Scene_Charsel::Render(HDC hdc)
{

	//�׷��ִ� ����
	//���
	//���� �Ϸ���Ʈ
	//ĳ���� �̴� �Ϸ���Ʈ
	//Ÿ�̸�
	//���� ����
	//�غ�

	I_BG.Draw(hdc, 0, 0, windowX, windowY);

	//�̹��� ũ�Ⱑ �� �ٸ��ϱ� �׳� ����ġ ���̽� ����...
	//���� �̹���
	switch (choice1) {
	case 1:
		I_charL[0].Draw(hdc, 0, 0, windowX, windowY);
		break;
	case 2:
		I_charL[1].Draw(hdc, 0, 15, windowX, windowY);
		break;
	case 3:
		I_charL[2].Draw(hdc, 0, 0, windowX, windowY);
		break;
	case 4: //�����϶���
		I_charL[3].Draw(hdc, 0, 0, windowX, windowY);
		break;
	}

	//������ �̹���
	switch (choice2)
	{
	case 1:
		I_charR[0].Draw(hdc, 0, 0, windowX, windowY);
		break;
	case 2:
		I_charR[1].Draw(hdc, 0, 0, windowX, windowY);
		break;
	case 3:
		I_charR[2].Draw(hdc, 0, 0, windowX, windowY);
		break;
	case 4:
		I_charR[3].Draw(hdc, 0, 0, windowX, windowY);
		break;
	}
	


	
	I_list.Draw(hdc, 0,0, windowX, windowY);

	//���� ���� �ߴٸ�
	if (ready1) {
		I_Ready.Draw(hdc, 50, 800, 633, 205);
	}
	if (ready2) {
		I_Ready.Draw(hdc, 1250, 800, 633, 205);
	}
	
	num[timer / 10].Draw(hdc, windowX / 2 - 200, 10, 200, 200); 
	num[timer % 10].Draw(hdc, windowX / 2 , 10, 200, 200);


}


