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
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpszCmdParam, int nCmdShow) //����
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
	}
	return Message.wParam;
}

CImage sample; // �̹����� �����ϴ� Ŭ����.

CImage C_TITLE;
CImage C_MainLobby_BG, C_MainLobby_START[2], C_MainLobby_TIP[2], C_MainLobby_EXIT[2];
CImage C_TIP;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	static WCHAR text[100];
	


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
			RECT p1, p2;

			
			Rectangle(hDC, clientRECT.left, clientRECT.top, clientRECT.right, clientRECT.bottom);

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
		InvalidateRect(hWnd, NULL, true);
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
			IngameGetKey(wParam);
			break;

		case SCOREBOARD:
			UI.nextScene();
			break;
		}
		break;
	case WM_CHAR:
		InvalidateRect(hWnd, NULL, true);
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
			IngameGetChar(wParam);
			break;

		case SCOREBOARD:

			break;
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