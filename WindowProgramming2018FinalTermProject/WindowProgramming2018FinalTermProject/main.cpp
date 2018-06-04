#include <windows.h> // 윈도우 헤더 파일
#include <tchar.h>
#include <stdlib.h>
#include <time.h>
#include <atlimage.h>
#include "USERINTERFACE.h"
#include "Ingame.h"

//윈도우 창의 크기입니다.
int windowX = ::GetSystemMetrics(SM_CXSCREEN); //모니터 x길이
int windowY = ::GetSystemMetrics(SM_CYSCREEN); //모니터 y길이

RECT clientRECT;
//게임이 나오는 스크린 창 입니다.
#define screenX 1920
#define screenY 1080

HINSTANCE g_hInst;
LPCTSTR lpszClass = _T("Window Class Name");

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

USER_INTERFACE UI;
HDC hDC;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpszCmdParam, int nCmdShow) //메인
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);
	hWnd = CreateWindow(lpszClass, L"window program", WS_OVERLAPPEDWINDOW, 0, 0, windowX, windowY, NULL, (HMENU)NULL, hInstance, NULL);
	//전체화면 
	ShowWindow(hWnd, SW_MAXIMIZE);
	//ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

CImage sample; // 이미지를 관리하는 클래스.

CImage C_TITLE;
CImage C_MainLobby_BG, C_MainLobby_START[2], C_MainLobby_TIP[2], C_MainLobby_EXIT[2];
CImage C_TIP;

//
CImage C_Tile[4];
CImage C_Numbers[10];
//

PlayerData player1, player2;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	static WCHAR text[100];
	WCHAR LoadText[100];
	switch (iMessage)
	{
	case WM_CREATE:
		GetClientRect(hWnd, &clientRECT);
		
		
		sample.Load(L"Sample\\Laharl_alphaTest.png"); //이미지 연결. 전용 DC와 Bitmap이 연결되어있는 상태.
		//타이틀 이미지를 로드합시다.
		C_TITLE.Load(L"Graphic\\UI\\Title.jpg");
		
		//메인 로비 이미지를 로드 합시다.
		C_MainLobby_BG.Load(L"Graphic\\UI\\MainLobby_BG.jpg");
		C_MainLobby_START[0].Load(L"Graphic\\UI\\START.png");
		C_MainLobby_START[1].Load(L"Graphic\\UI\\START2.png");

		C_MainLobby_TIP[0].Load(L"Graphic\\UI\\TIP.png");
		C_MainLobby_TIP[1].Load(L"Graphic\\UI\\TIP2.png");

		C_Tile[0].Load(L"Graphic\\Tile\\Tile1.jpg");

		for (int i = 0; i < 10; i++)
		{
			wsprintf(LoadText, L"Graphic\\Numbers\\%d.png", i);
			C_Numbers[i].Load(LoadText);
		}

		C_MainLobby_EXIT[0].Load(L"Graphic\\UI\\EXIT.png");
		C_MainLobby_EXIT[1].Load(L"Graphic\\UI\\EXIT2.png");

		C_TIP.Load(L"Graphic\\UI\\HINT.jpg");
		break;
	case WM_PAINT: //Paint 메세지 불렸을 때
		hDC = BeginPaint(hWnd, &ps);

		//Rectangle(hDC, clientRECT.left, clientRECT.top, clientRECT.right, clientRECT.bottom);

		//sample.Draw(hDC, clientRECT);																//Cimage를 잘 못그릴때는 Draw해주면 알아서 그려준다


		switch (UI.returnScene())
		{
		case TITLE:
			C_TITLE.Draw(hDC, clientRECT);
			break;
		case MAIN_LOBBY:
			C_MainLobby_BG.Draw(hDC, clientRECT);
			C_MainLobby_TIP[0].Draw(hDC,UI.GetRect(TIP));
			C_MainLobby_START[0].Draw(hDC, UI.GetRect(START));
			C_MainLobby_EXIT[0].Draw(hDC, UI.GetRect(EXIT));

			switch (UI.ReturnChoice()) {
			case TIP:
				C_MainLobby_TIP[1].Draw(hDC, UI.GetRect(TIP));
				break;
			case START:
				C_MainLobby_START[1].Draw(hDC, UI.GetRect(START));
				break;
			case EXIT:
				C_MainLobby_EXIT[1].Draw(hDC, UI.GetRect(EXIT));
				break;
			}

			break;
		case CONTROL_TIP:
			C_TIP.Draw(hDC, clientRECT);
			break;
		case SELECT_MODE:
			wsprintf(text, L"%d", UI.returnScene());
			TextOut(hDC, clientRECT.right / 2, clientRECT.bottom / 2, text, 1);
			break;
		case SELECT_CHAR:
			wsprintf(text, L"%d", UI.returnScene());
			TextOut(hDC, clientRECT.right / 2, clientRECT.bottom / 2, text, 1);
			break;
		case INGAME:
		{	
			//----------------------------------인게임 초기화
			RECT p1, p2;
			static HDC TotalMemDC,TileMemDC,PlayerMemDC;
			static HBITMAP TotalMemBitmap,TileMemBitmap,PlayerMemBitmap;
			static BOOL Tileset = FALSE;

			int Tileindex[100][100];
			p1.top = 0; p1.left = 0; p1.right = clientRECT.right / 2; p1.bottom = clientRECT.bottom;
			p2.top = 0; p2.left = clientRECT.right / 2; p2.right = clientRECT.right; p2.bottom = clientRECT.bottom;
			//--
			
			//--
			TotalMemDC = CreateCompatibleDC(hDC);
			TotalMemBitmap = CreateCompatibleBitmap(hDC,clientRECT.right,clientRECT.bottom);
			SelectObject(TotalMemDC, (HBITMAP)TotalMemBitmap);

			PlayerMemDC = CreateCompatibleDC(hDC);
			PlayerMemBitmap = CreateCompatibleBitmap(hDC, 6400, 6400);
			SelectObject(PlayerMemDC, (HBITMAP)PlayerMemBitmap);

			if (Tileset == FALSE) // 초기화하는 부분
			{
				PlayerImageLoad(&player1, 1); //1 -> 선택한 캐릭터 (캐릭터 선택창 만든 후 변경)
				PlayerImageLoad(&player2, 2); //2 -> 선택한 캐릭터 (캐릭터 선택창 만든 후 변경)
				SetTimer(hWnd, 1, 10, NULL);
				for (int i = 0; i < 100; i++)
				{
					for (int j = 0; j < 100; j++)
					{
						Tileindex[j][i] = 0;
					}
				}
				player1.x = 500; player1.y = 500;
				player2.x = 700; player2.y = 700;

				TileMemDC = CreateCompatibleDC(TotalMemDC);
				TileMemBitmap = CreateCompatibleBitmap(hDC, 6400, 6400);
				SelectObject(TileMemDC, (HBITMAP)TileMemBitmap);

				for (int i = 0; i < 100; i++)
				{
					for (int j = 0; j < 100; j++)
					{
						C_Tile[Tileindex[j][i]].BitBlt(TileMemDC, 64 * j, 64 * i, 64, 64, 0, 0, SRCCOPY); //타일의 가로세로크기가 64바이트
						Tileset = TRUE;
					}
				}
			}
			
			//------------------------------------맵 출력 TileMemDC -> PlayerMemDC
			BitBlt(PlayerMemDC, player1.x - p1.right / 2, player1.y - p1.bottom / 2, p1.right, p1.bottom,TileMemDC,player1.x-p1.right/2,player1.y-p1.bottom/2,SRCCOPY);
			BitBlt(PlayerMemDC, player2.x - p1.right / 2, player2.y - p1.bottom / 2, p1.right, p2.bottom, TileMemDC, player2.x - p1.right / 2, player2.y - p2.bottom / 2, SRCCOPY);
			//------------------------------------캐릭터 출력 PlayerMemDC
			switch (player1.CharacterStatus) // 0~1 = Idle  // 2~5 = Walk // 6~7 = Attack // 8 = Win // 9 = Lose
			{
			case 0:
				player1.Idle.TransparentBlt(PlayerMemDC, player1.x -player1.Idle.GetWidth()/2, player1.y - 5 - player1.Idle.GetHeight() / 2, player1.Idle.GetWidth(), player1.Idle.GetHeight(),RGB(78,98,61));
				break;
			case 1:
				player1.Idle_B.TransparentBlt(PlayerMemDC, player1.x - player1.Idle_B.GetWidth() / 2, player1.y - 5 - player1.Idle_B.GetHeight() / 2, player1.Idle_B.GetWidth(), player1.Idle_B.GetHeight(), RGB(78, 98, 61));
				break;
			case 2:
			case 5:
				player1.Walk[player1.WalkingImageTick%6].Draw(PlayerMemDC, player1.x - player1.Walk[player1.WalkingImageTick%6].GetWidth() / 2, player1.y - 5 - player1.Walk[player1.WalkingImageTick%6].GetHeight() / 2, player1.Walk[player1.WalkingImageTick%6].GetWidth(), player1.Walk[player1.WalkingImageTick%6].GetHeight());
				break;
			case 3:
			case 4:
				player1.Walk_B[player1.WalkingImageTick % 6].TransparentBlt(PlayerMemDC, player1.x - player1.Walk[player1.WalkingImageTick % 6].GetWidth() / 2, player1.y - 5 - player1.Walk[player1.WalkingImageTick % 6].GetHeight() / 2, player1.Walk[player1.WalkingImageTick % 6].GetWidth(), player1.Walk[player1.WalkingImageTick % 6].GetHeight(), RGB(78, 98, 61));
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				break;
			case 9:
				break;
			}
			switch (player2.CharacterStatus) // 0~1 = Idle  // 2~5 = Walk // 6~7 = Attack // 8 = Win // 9 = Lose
			{
			case 0:
				player2.Idle.TransparentBlt(PlayerMemDC, player2.x - player2.Idle.GetWidth() / 2, player2.y - 5 - player2.Idle.GetHeight() / 2, player2.Idle.GetWidth(), player2.Idle.GetHeight(), RGB(78, 98, 61));
				break;
			case 1:
				player2.Idle_B.TransparentBlt(PlayerMemDC, player2.x - player2.Idle_B.GetWidth() / 2, player2.y - 5 - player2.Idle_B.GetHeight() / 2, player2.Idle_B.GetWidth(), player2.Idle_B.GetHeight(), RGB(78, 98, 61));
				break;
			case 2:
			case 5:
				player2.Walk[player2.WalkingImageTick % 6].TransparentBlt(PlayerMemDC, player2.x - player2.Walk[player2.WalkingImageTick%6].GetWidth() / 2, player2.y - 5 - player2.Walk[player2.WalkingImageTick%6].GetHeight() / 2, player2.Walk[player2.WalkingImageTick%6].GetWidth(), player2.Walk[player2.WalkingImageTick%6].GetHeight(), RGB(78, 98, 61));
				break;
			case 3:
			case 4:
				player2.Walk_B[player2.WalkingImageTick % 6].TransparentBlt(PlayerMemDC, player2.x - player2.Walk[player2.WalkingImageTick % 6].GetWidth() / 2, player2.y - 5 - player2.Walk[player2.WalkingImageTick % 6].GetHeight() / 2, player2.Walk[player2.WalkingImageTick % 6].GetWidth(), player2.Walk[player2.WalkingImageTick % 6].GetHeight(), RGB(78, 98, 61));
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				break;
			case 9:
				break;
			}

			Ellipse(PlayerMemDC, player1.x - 5, player1.y - 5, player1.x +5, player1.y +5);
			Ellipse(PlayerMemDC, player2.x - 5, player2.y - 5, player2.x + 5, player2.y + 5);
			//------------------------------------캐릭터 total로 복사 PlayerMemDC -> TileMemDC
			BitBlt(TotalMemDC, p1.left, p1.top, p1.right, p1.bottom, PlayerMemDC, player1.x - p1.right / 2, player1.y - p1.bottom / 2, SRCCOPY);
			BitBlt(TotalMemDC, p2.left, p2.top, p1.right, p2.bottom, PlayerMemDC, player2.x - p1.right / 2, player2.y - p2.bottom / 2, SRCCOPY);
			//------------------------------------
			//Rectangle(hDC, clientRECT.left, clientRECT.top, clientRECT.right, clientRECT.bottom);

			BitBlt(hDC, 0, 0, clientRECT.right, clientRECT.bottom, TotalMemDC, 0, 0, SRCCOPY);

			DeleteObject(TotalMemDC); DeleteObject(PlayerMemDC); //DeleteObject(TileMemDC);
			DeleteObject(TotalMemBitmap); DeleteObject(PlayerMemBitmap); //DeleteObject(TileMemBitmap);
			
		}
			break;
		case SCOREBOARD:

			break;
		default:
			if (MessageBox(hWnd, _T("오류입니다. 초기위치로 돌아가시겠습니까?\n만약 NO를 누르면 게임이 종료됩니다."), _T("오류"), MB_YESNO)) {
				UI.ALLReset();
			}
			else {
				PostQuitMessage(0);
			}
			break;
		}

		//TextOut 텍스트 출력 함수

		EndPaint(hWnd, &ps);
		break;

	case WM_KEYDOWN:
		InvalidateRect(hWnd, NULL, false);
		switch (UI.returnScene())
		{
		case TITLE:
			//아무키나 입력하면 넘어감
			UI.nextScene();
			break;

		case MAIN_LOBBY:
			UI.nextScene();
			break;

		case CONTROL_TIP:
			UI.CallTip();
			break;

		case SELECT_MODE:
			UI.nextScene();
			break;

		case SELECT_CHAR:
			UI.nextScene();
			break;

		case INGAME:
			switch (wParam)
			{
			case VK_LEFT:
				player2.x -= 15;
				player2.CharacterStatus = 2;
				player2.isWalk = TRUE;
				player2.WalkingTimerTick = 0;
				player2.WalkingImageTick++;
				break;		  
			case VK_UP:		  
				player2.y -= 15;
				player2.CharacterStatus = 3;
				player2.isWalk = TRUE;
				player2.WalkingTimerTick = 0;
				player2.WalkingImageTick++;
				break;		  
			case VK_RIGHT:	  
				player2.x += 15;
				player2.CharacterStatus = 4;
				player2.isWalk = TRUE;
				player2.WalkingTimerTick = 0;
				player2.WalkingImageTick++;
				break;		  
			case VK_DOWN:	  
				player2.y += 15;
				player2.CharacterStatus = 5;
				player2.isWalk = TRUE;
				player2.WalkingTimerTick = 0;
				player2.WalkingImageTick++;
				break;
			}
			break;

		case SCOREBOARD:
			UI.nextScene();
			break;
		}
		break;
	case WM_CHAR:
		InvalidateRect(hWnd, NULL, false);
		switch (UI.returnScene())
		{
		case TITLE:
			//아무키나 입력하면 넘어감
			UI.nextScene();
			break;

		case MAIN_LOBBY:

			break;

		case CONTROL_TIP:

			break;

		case SELECT_MODE:

			break;

		case SELECT_CHAR:

			break;

		case INGAME:
		
			switch (wParam)
			{
			case 'f':
				player1.x -= 15;
				player1.CharacterStatus = 2;
				player1.isWalk = TRUE;
				player1.WalkingTimerTick = 0;
				player1.WalkingImageTick++;
				break;
			case 't':
				player1.y -= 15;
				player1.CharacterStatus = 3;
				player1.isWalk = TRUE;
				player1.WalkingTimerTick = 0;
				player1.WalkingImageTick++;
				break;
			case 'h':
				player1.x += 15;
				player1.CharacterStatus = 4;
				player1.isWalk = TRUE;
				player1.WalkingTimerTick = 0;
				player1.WalkingImageTick++;
				break;
			case 'g':
				player1.y += 15;
				player1.CharacterStatus = 5;
				player1.isWalk = TRUE;
				player1.WalkingTimerTick = 0;
				player1.WalkingImageTick++;
				break;
			
			}
		case SCOREBOARD:

			break;
		}
		break;
	case WM_TIMER:
		if (wParam == 1) // InGame Movement Manager
		{
			if (player1.isWalk)
			{
				player1.WalkingTimerTick++;
				if (player1.WalkingTimerTick >= 7)
				{
					player1.WalkingTimerTick = 0;
					player1.isWalk = FALSE;
					switch (player1.CharacterStatus)
					{
					case 2:
					case 5:
					case 6:
						player1.CharacterStatus = 0;
						break;
					case 3:
					case 4:
					case 7:
						player1.CharacterStatus = 1;
						break;
					}
				}
				InvalidateRect(hWnd, NULL, false);
			}
			if (player2.isWalk)
			{
				player2.WalkingTimerTick++;
				if (player2.WalkingTimerTick >= 7)
				{
					player2.WalkingTimerTick = 0;
					player2.isWalk = FALSE;
					switch (player2.CharacterStatus)
					{
					case 2:
					case 5:
					case 6:
						player2.CharacterStatus = 0;
						break;
					case 3:
					case 4:
					case 7:
						player2.CharacterStatus = 1;
						break;
					}
				}
				InvalidateRect(hWnd, NULL, false);
			}

			
		}
		break;
	case WM_DESTROY: //Destroy 메세지 불렸을 때
		PostQuitMessage(0); //창 종료
		return 0;
	
	case WM_MOUSEMOVE:
		switch (UI.returnScene())
		{
		
		case MAIN_LOBBY:

			break;

		case CONTROL_TIP:

			break;

		case SELECT_MODE:

			break;

		case SELECT_CHAR:

			break;

		case INGAME:

			break;

		case SCOREBOARD:

			break;
		}
		break;
	case WM_LBUTTONDOWN:
		switch (UI.returnScene())
		{
			
		case TITLE:
			//클릭해도 넘어감
			UI.nextScene();
			break;

		case MAIN_LOBBY:

			break;

		case CONTROL_TIP:

			break;

		case SELECT_MODE:

			break;

		case SELECT_CHAR:

			break;

		case INGAME:

			break;

		case SCOREBOARD:

			break;
		}

		break;
	case WM_RBUTTONDOWN:

		break;
	
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam)); //처리되지 않은 메세지는 여기서 처리
}