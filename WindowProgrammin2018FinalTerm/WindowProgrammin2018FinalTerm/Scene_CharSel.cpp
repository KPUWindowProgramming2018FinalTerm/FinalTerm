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

	return false;
}

void Scene_Charsel::BuildObjects()
{

}

// 1/60���� ������Ʈ��
void Scene_Charsel::Update(float fTimeElapsed)
{
	
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
		I_charL[0].Draw(hdc, 0, 0, 928, 1075);
		break;
	case 2:
		I_charL[1].Draw(hdc, 0, 15, 596, 1049);
		break;
	case 3:
		I_charL[2].Draw(hdc, 0, 0, 669, 1078);
		break;
	case 4: //�����϶���
		I_charL[3].Draw(hdc, 0, 0, 603, 1075);
		break;
	}

	//������ �̹���
	switch (choice2)
	{
	case 1:
		I_charR[0].Draw(hdc, windowX - 802, 0, 802,1075);
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	}

	
	I_list.Draw(hdc, windowX / 2 - 310, windowY - 567 - 50, 621, 567);



}


