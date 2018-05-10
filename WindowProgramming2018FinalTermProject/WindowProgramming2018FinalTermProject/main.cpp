#include <windows.h> // ������ ��� ����
#include <tchar.h>
#include <stdlib.h>
#include <time.h>

//������ â�� ũ���Դϴ�. �޴��� ����Ͽ� Y���� 20�ȼ� �������׽��ϴ�.
#define windowX 1920
#define windowY 1100

//������ ������ ��ũ�� â �Դϴ�.
#define screenX 1920
#define screenY 1080

HINSTANCE g_hInst;
LPCTSTR lpszClass = _T("Window Class Name");

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

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
	case WM_PAINT: //Paint �޼��� �ҷ��� ��
		hDC = BeginPaint(hWnd, &ps);

		//TextOut �ؽ�Ʈ ��� �Լ�

		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		MessageBox(hWnd, L"���� ����", L"����������", NULL);
		break;

	case WM_DESTROY: //Destroy �޼��� �ҷ��� ��
		PostQuitMessage(0); //â ����
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam)); //ó������ ���� �޼����� ���⼭ ó��
}