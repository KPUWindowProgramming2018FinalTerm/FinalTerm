#include <windows.h> // ������ ��� ����
#include <tchar.h>
#include <stdlib.h>
#include <time.h>
#include <atlimage.h>
#include "USERINTERFACE.h"
#include "Ingame.h"

//������ â�� ũ���Դϴ�.
int windowX = ::GetSystemMetrics(SM_CXSCREEN); //����� x����
int windowY = ::GetSystemMetrics(SM_CYSCREEN); //����� y����

RECT clientRECT;
//������ ������ ��ũ�� â �Դϴ�.
#define screenX 1920
#define screenY 1080

HINSTANCE g_hInst;
LPCTSTR lpszClass = _T("Window Class Name");

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

USER_INTERFACE UI;
HDC hDC;
PlayerData player1, player2;
BOOL keydown;

BOOL IngameKeydownManager()
{
	keydown = FALSE;
	if (GetAsyncKeyState(VK_UP) & 0x8001)
	{
		player2.y -= 15;
		player2.CharacterStatus = 3;
		player2.isWalk = TRUE;
		player2.WalkingTimerTick = 0;
		player2.WalkingImageTick++;
		keydown = TRUE;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8001)
	{
		player2.x -= 15;
		player2.CharacterStatus = 2;
		player2.isWalk = TRUE;
		player2.WalkingTimerTick = 0;
		player2.WalkingImageTick++;
		keydown = TRUE;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	{
		player2.y += 15;
		player2.CharacterStatus = 5;
		player2.isWalk = TRUE;
		player2.WalkingTimerTick = 0;
		player2.WalkingImageTick++;
		keydown = TRUE;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
	{
		player2.x += 15;
		player2.CharacterStatus = 4;
		player2.isWalk = TRUE;
		player2.WalkingTimerTick = 0;
		player2.WalkingImageTick++;
		keydown = TRUE;
	}

	if (GetAsyncKeyState(0x46) & 0x8000) // f
	{
		player1.x -= 15;
		player1.CharacterStatus = 2;
		player1.isWalk = TRUE;
		player1.WalkingTimerTick = 0;
		player1.WalkingImageTick++;
		keydown = TRUE;
	}
	if (GetAsyncKeyState(0x54) & 0x8000) // t
	{
		player1.y -= 15;
		player1.CharacterStatus = 3;
		player1.isWalk = TRUE;
		player1.WalkingTimerTick = 0;
		player1.WalkingImageTick++;
		keydown = TRUE;
	}
	if (GetAsyncKeyState(0x48) & 0x8000) // h
	{
		player1.x += 15;
		player1.CharacterStatus = 4;
		player1.isWalk = TRUE;
		player1.WalkingTimerTick = 0;
		player1.WalkingImageTick++;
		keydown = TRUE;
	}
	if (GetAsyncKeyState(0x47) & 0x8000) // g
	{
		player1.y += 15;
		player1.CharacterStatus = 5;
		player1.isWalk = TRUE;
		player1.WalkingTimerTick = 0;
		player1.WalkingImageTick++;
		keydown = TRUE;
	}

	if (keydown)
		return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) //����
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
	//��üȭ�� 
	ShowWindow(hWnd, SW_MAXIMIZE);
	//ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
		if (UI.returnScene() == INGAME)
		{
			if (IngameKeydownManager())
				WndProc(hWnd, WM_PAINT, NULL, NULL);
		}
	}
	return Message.wParam;
}

CImage sample; // �̹����� �����ϴ� Ŭ����.

CImage C_TITLE;
CImage C_MainLobby_BG, C_MainLobby_START[2], C_MainLobby_TIP[2], C_MainLobby_EXIT[2];
CImage C_TIP;

//
CImage C_Tile[4];
CImage C_Numbers[10];
//



LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	static WCHAR text[100];
	WCHAR LoadText[100];
	switch (iMessage)
	{
	case WM_CREATE:
		GetClientRect(hWnd, &clientRECT);


		sample.Load(L"Sample\\Laharl_alphaTest.png"); //�̹��� ����. ���� DC�� Bitmap�� ����Ǿ��ִ� ����.
		//Ÿ��Ʋ �̹����� �ε��սô�.
		C_TITLE.Load(L"Graphic\\UI\\Title.jpg");

		//���� �κ� �̹����� �ε� �սô�.
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
	case WM_PAINT: //Paint �޼��� �ҷ��� ��
		hDC = BeginPaint(hWnd, &ps);

		//Rectangle(hDC, clientRECT.left, clientRECT.top, clientRECT.right, clientRECT.bottom);

		//sample.Draw(hDC, clientRECT);																//Cimage�� �� ���׸����� Draw���ָ� �˾Ƽ� �׷��ش�


		switch (UI.returnScene())
		{
		case TITLE:
			C_TITLE.Draw(hDC, clientRECT);
			break;
		case MAIN_LOBBY:
			C_MainLobby_BG.Draw(hDC, clientRECT);
			C_MainLobby_TIP[0].Draw(hDC, UI.GetRect(TIP));
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
			//----------------------------------�ΰ��� �ʱ�ȭ
			RECT p1, p2;
			static HDC TotalMemDC, TileMemDC, PlayerMemDC;
			static HBITMAP TotalMemBitmap, TileMemBitmap, PlayerMemBitmap;
			static BOOL Tileset = FALSE;

			int Tileindex[100][100];
			p1.top = 0; p1.left = 0; p1.right = clientRECT.right / 2; p1.bottom = clientRECT.bottom;
			p2.top = 0; p2.left = clientRECT.right / 2; p2.right = clientRECT.right; p2.bottom = clientRECT.bottom;
			//--

			//--
			TotalMemDC = CreateCompatibleDC(hDC);
			TotalMemBitmap = CreateCompatibleBitmap(hDC, clientRECT.right, clientRECT.bottom);
			SelectObject(TotalMemDC, (HBITMAP)TotalMemBitmap);

			PlayerMemDC = CreateCompatibleDC(hDC);
			PlayerMemBitmap = CreateCompatibleBitmap(hDC, 6400, 6400);
			SelectObject(PlayerMemDC, (HBITMAP)PlayerMemBitmap);

			if (Tileset == FALSE) // �ʱ�ȭ�ϴ� �κ�
			{
				PlayerImageLoad(&player1, 1); //1 -> ������ ĳ���� (ĳ���� ����â ���� �� ����)
				PlayerImageLoad(&player2, 2); //2 -> ������ ĳ���� (ĳ���� ����â ���� �� ����)
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
						C_Tile[Tileindex[j][i]].BitBlt(TileMemDC, 64 * j, 64 * i, 64, 64, 0, 0, SRCCOPY); //Ÿ���� ���μ���ũ�Ⱑ 64����Ʈ
						Tileset = TRUE;
					}
				}
			}

			//------------------------------------�� ��� TileMemDC -> PlayerMemDC
			BitBlt(PlayerMemDC, player1.x - p1.right / 2, player1.y - p1.bottom / 2, p1.right, p1.bottom, TileMemDC, player1.x - p1.right / 2, player1.y - p1.bottom / 2, SRCCOPY);
			BitBlt(PlayerMemDC, player2.x - p1.right / 2, player2.y - p1.bottom / 2, p1.right, p2.bottom, TileMemDC, player2.x - p1.right / 2, player2.y - p2.bottom / 2, SRCCOPY);
			//------------------------------------ĳ���� ��� PlayerMemDC
			switch (player1.CharacterStatus) // 0~1 = Idle  // 2~5 = Walk // 6~7 = Attack // 8 = Win // 9 = Lose
			{
			case 0:
				player1.Idle.Draw(PlayerMemDC, player1.x - player1.Idle.GetWidth() / 2, player1.y - 5 - player1.Idle.GetHeight() / 2, player1.Idle.GetWidth(), player1.Idle.GetHeight());
				break;
			case 1:
				player1.Idle_B.Draw(PlayerMemDC, player1.x - player1.Idle_B.GetWidth() / 2, player1.y - 5 - player1.Idle_B.GetHeight() / 2, player1.Idle_B.GetWidth(), player1.Idle_B.GetHeight());
				break;
			case 2:
			case 5:
				player1.Walk[player1.WalkingImageTick % 6].Draw(PlayerMemDC, player1.x - player1.Walk[player1.WalkingImageTick % 6].GetWidth() / 2, player1.y - 5 - player1.Walk[player1.WalkingImageTick % 6].GetHeight() / 2, player1.Walk[player1.WalkingImageTick % 6].GetWidth(), player1.Walk[player1.WalkingImageTick % 6].GetHeight());
				break;
			case 3:
			case 4:
				player1.Walk_B[player1.WalkingImageTick % 6].Draw(PlayerMemDC, player1.x - player1.Walk[player1.WalkingImageTick % 6].GetWidth() / 2, player1.y - 5 - player1.Walk[player1.WalkingImageTick % 6].GetHeight() / 2, player1.Walk[player1.WalkingImageTick % 6].GetWidth(), player1.Walk[player1.WalkingImageTick % 6].GetHeight());
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
				player2.Idle.Draw(PlayerMemDC, player2.x - player2.Idle.GetWidth() / 2, player2.y - 5 - player2.Idle.GetHeight() / 2, player2.Idle.GetWidth(), player2.Idle.GetHeight());
				break;
			case 1:
				player2.Idle_B.Draw(PlayerMemDC, player2.x - player2.Idle_B.GetWidth() / 2, player2.y - 5 - player2.Idle_B.GetHeight() / 2, player2.Idle_B.GetWidth(), player2.Idle_B.GetHeight());
				break;
			case 2:
			case 5:
				player2.Walk[player2.WalkingImageTick % 6].Draw(PlayerMemDC, player2.x - player2.Walk[player2.WalkingImageTick % 6].GetWidth() / 2, player2.y - 5 - player2.Walk[player2.WalkingImageTick % 6].GetHeight() / 2, player2.Walk[player2.WalkingImageTick % 6].GetWidth(), player2.Walk[player2.WalkingImageTick % 6].GetHeight());
				break;
			case 3:
			case 4:
				player2.Walk_B[player2.WalkingImageTick % 6].Draw(PlayerMemDC, player2.x - player2.Walk[player2.WalkingImageTick % 6].GetWidth() / 2, player2.y - 5 - player2.Walk[player2.WalkingImageTick % 6].GetHeight() / 2, player2.Walk[player2.WalkingImageTick % 6].GetWidth(), player2.Walk[player2.WalkingImageTick % 6].GetHeight());
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

			Ellipse(PlayerMemDC, player1.x - 5, player1.y - 5, player1.x + 5, player1.y + 5);
			Ellipse(PlayerMemDC, player2.x - 5, player2.y - 5, player2.x + 5, player2.y + 5);
			//------------------------------------ĳ���� total�� ���� PlayerMemDC -> TileMemDC
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
			if (MessageBox(hWnd, _T("�����Դϴ�. �ʱ���ġ�� ���ư��ðڽ��ϱ�?\n���� NO�� ������ ������ ����˴ϴ�."), _T("����"), MB_YESNO)) {
				UI.ALLReset();
			}
			else {
				PostQuitMessage(0);
			}
			break;
		}

		//TextOut �ؽ�Ʈ ��� �Լ�

		EndPaint(hWnd, &ps);
		break;

	case WM_KEYDOWN:
		InvalidateRect(hWnd, NULL, false);
		switch (UI.returnScene())
		{
		case TITLE:
			//�ƹ�Ű�� �Է��ϸ� �Ѿ
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
			//�ƹ�Ű�� �Է��ϸ� �Ѿ
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

			InvalidateRect(hWnd, NULL, false);
			break;
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
				if (player1.WalkingTimerTick >= 3)
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
				if (player2.WalkingTimerTick >= 3)
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
	case WM_DESTROY: //Destroy �޼��� �ҷ��� ��
		PostQuitMessage(0); //â ����
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
			//Ŭ���ص� �Ѿ
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
return(DefWindowProc(hWnd, iMessage, wParam, lParam)); //ó������ ���� �޼����� ���⼭ ó��
}