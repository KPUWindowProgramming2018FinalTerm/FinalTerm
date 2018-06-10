#include "stdafx.h"
// 
// 타이틀 씬 등을 include할 공간
#include "Scene_Main.h"
#include "Scene_Ingame.h"
// 
#include "OBJECT_Player.h"
#include "Framework.h"

using namespace std;// 왠만하면 하지 말자. 컴파일 시간이 엄청 느려진다. 성능상의 문제는 없다.
					// 컴파일 할 때 std 네임스페이스가 포함된 모든 헤더파일을 돌기 때문에 생기는 문제이다.

template<typename T>
T GetUserDataPtr(HWND hWnd)
{
	return reinterpret_cast<T>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
}
void SetUserDataPtr(HWND hWnd, LPVOID ptr)
{
	LONG_PTR result = ::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(ptr));
}

CFramework::CFramework()
{
	m_ticker = new CGameTimer();
	m_ticker->Start();
}

CFramework::~CFramework()
{
	OnDestroy();
	m_ticker->Stop();
}

bool CFramework::OnCreate(HINSTANCE hInstance, HWND hWnd, const RECT & rc) //생성자에서 해야할 일을 하는데 전역 클래스 변수이므로 생성자를 쓰면 안되기 때문
{
	srand((unsigned int)time(NULL));
	m_hInstance = hInstance;
	m_hWnd = hWnd;
	m_rcClient = rc;
	// 클라이언트 좌표 초기화
	m_rcClient.right -= m_rcClient.left;
	m_rcClient.bottom -= m_rcClient.top;
	m_rcClient.left = 0;
	m_rcClient.top = 0;

	//

	// 버퍼 생성
	CreatebackBuffer();
	
	//플레이어 생성
	BuildPlayer();
	p1.top = 0; p1.left = 0; p1.right = m_rcClient.right / 2; p1.bottom = m_rcClient.bottom;
	p2.top = 0; p2.left = m_rcClient.right / 2; p2.right = m_rcClient.right; p2.bottom = m_rcClient.bottom;
	// 클래스와 윈도우 프로시저 연결
	::SetUserDataPtr(m_hWnd, this);

	// ...

	// 캡션 변경
	lstrcpy(m_CaptionTitle, TITLESTRING);

#if defined(SHOW_CAPTIONFPS)
	lstrcat(m_CaptionTitle, TEXT("("));
#endif
	m_TitleLength = lstrlen(m_CaptionTitle);
	SetWindowText(m_hWnd, m_CaptionTitle);

	// 타이머 초기화
//	m_LastUpdate_time = chrono::system_clock::now(); // 선언하지 않았다.
	m_current_time = chrono::system_clock::now();
	m_fps = 0;

	// 씬 생성
	BuildScene();


	// 최초의 씬은 무엇인가?
	ChangeScene(CScene::SceneTag::Ingame);

	return (m_hWnd != NULL);
}

RECT CFramework::GetRect()
{
	return m_rcClient;
}

HDC* CFramework::GetTileDC()
{
	return &m_tileMemDC;
}

HDC* CFramework::GetPlayerDC()
{
	return &m_PlayerMemDC;
}

CObject_Player* CFramework::GetPlayer(int PlayerNum)
{
	switch (PlayerNum)
	{
	case 1:
		return player1;
		break;
	case 2:
		return player2;
		break;
	default:
		break;
	}
}

HDC CFramework::GetTotalDC()
{
	return m_totalBackDC;
}

void CFramework::CreatebackBuffer() //backBuffer 초기화
{
	if (m_totalBackDC)
	{
		::SelectObject(m_totalBackDC, NULL);
		::DeleteDC(m_totalBackDC);
	}
	if (m_totalBackBitmap) ::DeleteObject(m_totalBackBitmap);

	HDC hdc = ::GetDC(m_hWnd);
	m_totalBackDC = ::CreateCompatibleDC(hdc);	// 호환을 시켜주는 함수
	// 프레임 워크 내부에 백버퍼를 만든다. hdc에 호환된 비트맵을 사용한다.
	m_totalBackBitmap = ::CreateCompatibleBitmap(hdc, m_rcClient.right, m_rcClient.bottom);
	::SelectObject(m_totalBackDC, m_totalBackBitmap);

	m_PlayerMemDC = CreateCompatibleDC(hdc);
	m_PlayerMemBitmap = CreateCompatibleBitmap(hdc, 6400, 6400);
	::SelectObject(m_PlayerMemDC, (HBITMAP)m_PlayerMemBitmap);

	m_tileMemDC = CreateCompatibleDC(m_PlayerMemDC);
	m_tileMemBitmap = CreateCompatibleBitmap(hdc, 6400, 6400);
	::SelectObject(m_tileMemDC, (HBITMAP)m_tileMemBitmap);

	SetBKColor(RGB(255, 255, 255));

	ClearBackgroundColor();

	::ReleaseDC(m_hWnd, hdc);
}

void CFramework::BuildScene()
{
	// arrScene[SceneTag::Title] = new TitleScene();	// 이런 방식으로 씬을 만들어라.
	arrScene[CScene::SceneTag::Main_Lobby] = new CMainScene();
	arrScene[CScene::SceneTag::Ingame] = new CIngameScene(CScene::SceneTag::Ingame,this);
	arrScene[CScene::SceneTag::Ingame]->OnCreate();
}

void CFramework::BuildPlayer()
{
	while (player1 == NULL)
		player1 = new CObject_Player();
	while (player2 == NULL)
		player2 = new CObject_Player();
	printf("%d\n", player1->x);
	player1->OnCreate(1);
	printf("%d\n", player1->x);
	player2->OnCreate(2);
}

void CFramework::ReleaseScene() // 씬 완전삭제
{

}

bool CFramework::OnDestroy() // Framework 파괴 (재생성을 위함)
{
	if (m_hbrBackground) ::DeleteObject(m_hbrBackground);

	::SelectObject(m_totalBackDC, NULL);
	if (m_totalBackBitmap)  ::DeleteObject(m_totalBackBitmap);
	if (m_totalBackDC) ::DeleteDC(m_totalBackDC);
	return false;
}

bool CFramework::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		return true;
	case WM_KEYUP:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);	// ESC 키를 눌렀을 때 윈도우를 종료한다.
			break;
		}
		return true;
	}
	return false;
}

bool CFramework::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_LBUTTONUP:
		break;
	case WM_LBUTTONDOWN:
		break;

	case WM_MOUSEMOVE:
		break;

	}
	return false;
}

HRESULT CFramework::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_SIZE:	// 윈도의 크기를 조절하는 순간 여기 들어온다.
		break;
	case WM_ACTIVATE:
		if (LOWORD(wParam) == WA_INACTIVE)
		{
			//비활성화 처리
		}
		else
		{
			//활성화 처리
		}
		break;
	default:
		return ::DefWindowProc(hWnd, nMessageID, wParam, lParam);
	}
//	return E_NOTIMPL;
	return 0;
}

void CFramework::Update(float fTimeElapsed)
{
	m_pCurrScene->Update(fTimeElapsed);
}

void CFramework::SetBKColor(COLORREF color)
{
	m_clrBackBuffer = color;
	if (m_hbrBackground) ::DeleteObject(m_hbrBackground);
	m_hbrBackground = ::CreateSolidBrush(m_clrBackBuffer);	// 이 색깔로 브러쉬를 만들어라.
}

void CFramework::ClearBackgroundColor()
{
	::FillRect(m_totalBackDC, &m_rcClient, m_hbrBackground);	// 현재 백버퍼의 백그라운드에 현재 클라이언트만큼의 영역을 방금 만든 브러쉬의 색으로 색칠해라.
}

void CFramework::PreprocessingForDraw()
{
	ClearBackgroundColor();	// 그리기 연산이 시작되면 무조건 그라운드를 깨끗하게 만든다.
	::SetBkColor(m_totalBackDC, TRANSPARENT);	// 알파블렌딩 허용 가능하게 설정
	::SetStretchBltMode(m_totalBackDC, COLORONCOLOR);	//쓰는 범위가 달라서 늘어나거나 줄어들 여지가 있는 경우 덮어쓴다.

	m_pCurrScene->Render(m_totalBackDC);
}

void CFramework::OnDraw(HDC hDC)
{
	// 인자로 받는 hDC는 밖에서 만들어진 hDC이다. 이 비트맵에 m_hDC의 백버퍼에서 만들어진 그림을 뿌린다.
	::BitBlt(hDC, m_rcClient.left, m_rcClient.top, m_rcClient.right, m_rcClient.bottom, m_totalBackDC, 0, 0, SRCCOPY);
}

void CFramework::FrameAdvance()
{
	// FPS 제한
	
	//m_timeElapsed = chrono::system_clock::now() - m_current_time;
	//{
	//	if (m_timeElapsed.count() > MAX_FPS) // MAX_FPS가 0 이상이면 프로그램 즉시 종료?
	//	{
	//		m_current_time = chrono::system_clock::now();
	//		if (m_timeElapsed.count() > 0.0)
	//			m_fps = 1.0 / m_timeElapsed.count();
	//	}
	//	else return;
	//}
	m_ticker->Tick(60.0f);
	m_fps = 1.0 / m_ticker->GetTimeElapsed();
	Update(m_ticker->GetTimeElapsed()); // 그려야 될 것 업데이트(프레임단)
	PreprocessingForDraw(); // 
	// 백버퍼 연산이므로 OnDraw가 아니다. OnDraw 이전에 백버퍼에 그려주는 연산을 한다.

	InvalidateRect(m_hWnd, &m_rcClient, FALSE);	// False는 초기화를 하지 않는다는 뜻이다. 강제로 윈도우 메시지를 호출한다.

	// ↓캡션에 글자를 뭘 넣을지 연산하는 캡션 스트링 연산
	{
		_itow_s(
		m_fps+0.1f
		, m_CaptionTitle + m_TitleLength
		, TITLE_MX_LENGTH - m_TitleLength
		, 10);
	wcscat_s(
		m_CaptionTitle + m_TitleLength
		, TITLE_MX_LENGTH - m_TitleLength
		, TEXT("FPS )"));
	SetWindowText(m_hWnd, m_CaptionTitle);
	}
}

LRESULT CFramework::WndProc(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	CFramework* self = ::GetUserDataPtr<CFramework*>(hWnd);	// static 함수랑 연결하려고 선언한 포인터. 클래스를 정적함수에 등록하기 위한 꼼수
	if (!self)
		return ::DefWindowProc(hWnd, nMessageID, wParam, lParam);	// 메시지 처리를 OS에게 넘긴다.

	switch (nMessageID)
	{
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:

	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:

	case WM_MOUSEMOVE:
		self->OnProcessingMouseMessage(hWnd, nMessageID, wParam, lParam);
		break;


	case WM_KEYDOWN:
	case WM_KEYUP:
		self->OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);
		break;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = ::BeginPaint(hWnd, &ps);	// 이 디바이스 컨텍스트를 사용하겠다.
			// hdc에서 이 함수를 통해 bitmap을 붙인다.

			// CPU 단계에서 호출하는 거라 메시지 검사 부분 등이 굉장히 느리다.
			// 따라서 윈도우 메시지는 더 빠른 게임을 위해서는 쓰지 않게 된다. 하지만 알아놓기는 해야한다.
			// 픽메시지를 검사하고 트랜스메시지, 디스패치메시지에서 윈도우프로시저로 메시지를 넘겨준다.
			self->OnDraw(hdc);
	
			::EndPaint(hWnd, &ps); // 그리고 지운다.
		}
		break;
	case WM_DESTROY:
		::SetUserDataPtr(hWnd, NULL);
		::PostQuitMessage(0);
		break;

	default:
		return self->OnProcessingWindowMessage(hWnd, nMessageID, wParam, lParam);
	}
	return 0;
//	return LRESULT();
}

void CFramework::curSceneCreate()
{
	m_pCurrScene->OnCreate();
}

void CFramework::ChangeScene(CScene::SceneTag tag)
{
	m_pCurrScene = arrScene[tag];
	//m_pCurrScene->OnCreate();
}

/*
20171206 스터디 최후
winmain()
{
	윈도우 등록
	윈도우 생성

	메시지 루프
	{
		메시지 처리
		게임 루프 처리
		{
			FrameWork
				FrameAdvanced();
				{
					ProcessInput()	// 키 입력
					{
						WndProc
							WM_KEY:
							WM_MOUSE:
					}
					m_pscene->	Update();	// 로직 처리
					m_pscene->	Render()	// 그리기	// InvalidateRect()를 통해 아래 블럭 안으로 이동
					{	
						WndProc
							WM_PAINT:
							hdc = BeginDraw();
							Render(hdc);
							EndDraw(hdc);
					}
				}
		}
	}
}


private:
	CScene * m_pscene;
	Oncreate() 함수 안에서 new를 통해 위 변수를 생성
	씬 이름을 enum tag를 통해 정해주면 된다.

	** arrscene;
	2D프로그래밍때와 달리, 프레임워크가 자체적으로 씬 배열을 가지고 있다.
	[0]에서는 로비, [1]에서는 게임오버 등...
	그러면 2D때 푸쉬 팝과는 달리 ChangeScene으로 해결한다.

	이러면 장점이 씬 이동이 자유롭다.


	update와 render는 상위 클래스에서 =0; 을 만들고

	각자 scene들이 상속받아서 이걸 가지고 있어야 한다.
*/