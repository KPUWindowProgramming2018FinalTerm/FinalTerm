#include "stdafx.h"
#include "Scene_CharSel.h"

Scene_Charsel::Scene_Charsel()
{


}

Scene_Charsel::~Scene_Charsel()
{
}

//생성될때 뭔가 하려나 부다
bool Scene_Charsel::OnCreate()
{
	//이미지를 로드합니다.
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
	

	//타이머 초기화
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



//키 상태를 입력받음.
void Scene_Charsel::KeyState() {
	
	//P1 레디
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
	

	//P2 레디
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

// 1/60으로 업데이트됨
void Scene_Charsel::Update(float fTimeElapsed)
{
	KeyState();
	//종료되지 않아야지 계속 실행한다.
	if (!Finish) {
		//매 프레임 체크
		if (count == 0) {
			count = 60;
			timer--;
		}
		else {
			count--;
		}

		//타이머가 0이되면 강제로 레디 시킴
		if (timer == 0) {
			ready1 = true;
			ready2 = true;
		}

		//둘다 참이면 피니쉬
		if (ready1&&ready2) {
			Finish = true;
		}



	}
}

void Scene_Charsel::Render(HDC hdc)
{

	//그려주는 순서
	//배경
	//선택 일러스트
	//캐릭터 미니 일러스트
	//타이머
	//유저 선택
	//준비

	I_BG.Draw(hdc, 0, 0, windowX, windowY);

	//이미지 크기가 다 다르니깐 그냥 스위치 케이스 하자...
	//왼쪽 이미지
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
	case 4: //랜덤일때야
		I_charL[3].Draw(hdc, 0, 0, windowX, windowY);
		break;
	}

	//오른쪽 이미지
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

	//만약 레디 했다면
	if (ready1) {
		I_Ready.Draw(hdc, 50, 800, 633, 205);
	}
	if (ready2) {
		I_Ready.Draw(hdc, 1250, 800, 633, 205);
	}
	
	num[timer / 10].Draw(hdc, windowX / 2 - 200, 10, 200, 200); 
	num[timer % 10].Draw(hdc, windowX / 2 , 10, 200, 200);


}


