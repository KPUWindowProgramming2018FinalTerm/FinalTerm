#include <iostream>
#include <Windows.h>
//==========================================================
//               USERINTERFACE

//유저 인터페이스의 클래스 선언과 기타 사항 정의입니다.



//==========================================================

//SCENE의 위치를 선언해놓은 열거형 입니다.
enum SceneNAME {
	TITLE = 0, MAIN_LOBBY = 1, CONTROL_TIP = 2, SELECT_MODE = 3, SELECT_CHAR = 4, INGAME = 5, SCOREBOARD = 6
};






class USER_INTERFACE {
private:
	//타이틀과 관련된 데이터 필드입니다.
	//초기 값으로는 타이틀 신을 가집니다.
	SceneNAME now = TITLE;

	//게임의 상태를 나타냅니다.
	bool gameState = false;




public:
	//기본상태에서 다음 씬을 소환합니다.
	void nextScene();

	

};