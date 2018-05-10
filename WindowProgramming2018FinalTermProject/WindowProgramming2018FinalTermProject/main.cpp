#include <windows.h> // 윈도우 헤더 파일
#include <tchar.h>
#include <stdlib.h>
#include <time.h>

//윈도우 창의 크기입니다. 메뉴를 고려하여 Y축을 20픽셀 증가시켰습니다.
#define windowX 1920
#define windowY 1100

//게임이 나오는 스크린 창 입니다.
#define screenX 1920
#define screenY 1080

HINSTANCE g_hInst;
LPCTSTR lpszClass = _T("Window Class Name");

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

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

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	int x = 0, y = 0;
	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_PAINT: //Paint 메세지 불렸을 때
		hDC = BeginPaint(hWnd, &ps);

		//TextOut 텍스트 출력 함수

		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		MessageBox(hWnd, L"혁뀨 혁뀨", L"구래피이익", NULL);
		break;

	case WM_DESTROY: //Destroy 메세지 불렸을 때
		PostQuitMessage(0); //창 종료
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam)); //처리되지 않은 메세지는 여기서 처리
}