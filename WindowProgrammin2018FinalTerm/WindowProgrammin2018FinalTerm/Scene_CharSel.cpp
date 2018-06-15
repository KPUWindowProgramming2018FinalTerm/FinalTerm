#include "stdafx.h"
#include "Scene_CharSel.h"
#include "Framework.h"

Scene_Charsel::Scene_Charsel()
{


}

Scene_Charsel::~Scene_Charsel()
{
}

Scene_Charsel::Scene_Charsel(SceneTag tag, CFramework * pFramework) : CScene(tag, pFramework) //프레임워크 포인터 활성화
{

}

void Scene_Charsel::OnDestroy()
{
	I_BG.Destroy();
	I_charL[0].Destroy();
	I_charL[1].Destroy();
	I_charL[2].Destroy();
	I_charL[3].Destroy();

	I_charR[0].Destroy();
	I_charR[1].Destroy();
	I_charR[2].Destroy();
	I_charR[3].Destroy();

	I_Ready.Destroy();

	I_list.Destroy();

	for (int i = 0; i < 10; i++) {
		num[i].Destroy();
	}
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

	choice1 = 1;
	choice2 = 1;

	Finish = false;

	//이미지 크기와 관련하여 작성합니다.
	//이미지 크기가 변경될 시 재작성이 필요합니다.
	{
		//10단위 이미지
		R_NUM1.top = 50;
		R_NUM1.left = 760;
		R_NUM1.bottom = 200;
		R_NUM1.right = 200;

		//1단위 이미지
		R_NUM2.top = 50;
		R_NUM2.left = 960;
		R_NUM2.bottom = 200;
		R_NUM2.right = 200;



	}





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
		if (Finish)
		{
			if (choice1 == 4)
				choice1 = rand() % 4;
			if (choice2 == 4)
				choice2 = rand() % 4;
			m_pFramework->ChangeScene(CScene::SceneTag::Ingame);
			m_pFramework->curSceneCreate();
			m_pFramework->BuildPlayer(choice1,choice2);
			Scene_Charsel::OnDestroy();
			
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

	////이미지 크기가 다 다르니깐 그냥 스위치 케이스 하자...
	////왼쪽 이미지
	//switch (choice1) {
	//case 1:
	//	I_charL[0].Draw(hdc, 0, 0, windowX, windowY);
	//	break;
	//case 2:
	//	I_charL[1].Draw(hdc, 0, 15, windowX, windowY);
	//	break;
	//case 3:
	//	I_charL[2].Draw(hdc, 0, 0, windowX, windowY);
	//	break;
	//case 4: //랜덤일때야
	//	I_charL[3].Draw(hdc, 0, 0, windowX, windowY);
	//	break;
	//}

	////오른쪽 이미지
	//switch (choice2)
	//{
	//case 1:
	//	I_charR[0].Draw(hdc, 0, 0, windowX, windowY);
	//	break;
	//case 2:
	//	I_charR[1].Draw(hdc, 0, 0, windowX, windowY);
	//	break;
	//case 3:
	//	I_charR[2].Draw(hdc, 0, 0, windowX, windowY);
	//	break;
	//case 4:
	//	I_charR[3].Draw(hdc, 0, 0, windowX, windowY);
	//	break;
	//}
	//


	//
	//I_list.Draw(hdc, 0,0, windowX, windowY);

	////만약 레디 했다면
	//if (ready1) {
	//	I_Ready.Draw(hdc, 50, 800, 633, 205);
	//}
	//if (ready2) {
	//	I_Ready.Draw(hdc, 1250, 800, 633, 205);
	//}
	
	num[timer / 10].Draw(hdc, CalcImage(R_NUM1)); 
	num[timer % 10].Draw(hdc, CalcImage(R_NUM2));


}


//이미지의 크기를 계산합니다.
RECT Scene_Charsel::CalcImage(RECT input) {
	//=======================================
	//        기능 안내
	// top과 left는 화면 비율에 맞게 계산하여 정하고
	// bottom과 right는 화면 크기에 맞게 계산하여 정한다.
	//===========================================

	RECT calc;

	//1080일때 기준으로 개발하고, 윈도우의 크기로 나눠서 위치를 맞춘다.
	calc.top = input.top*(1080/windowY);

	//1920일때 기준으로 개발하고, 윈도우의 크기로 나눠서 위치를 정합시다.
	calc.left = input.left*(1920 / windowX);

	//가로와 세로중 어떤 비율이 더 작은지 정하고 더 작은 비율로 정하여 비율 유지하여 그림 크기를 정한다.
	//세로가 더 크므로 가로 기준으로 맞춘다.
	if ((1080 / windowY) >= (1920 / windowX)) {
		calc.bottom = input.bottom*(1920 / windowX);
		calc.right=input.right*(1920 / windowX);
	}
	//가로가 더 크므로 세로 기준으로 맞춘다.
	else {
		calc.bottom = input.bottom*(1080 / windowY);
		calc.right = input.right*(1080 / windowY);
	}
	//계산된 결과를 리턴한다.
	return calc;
}

