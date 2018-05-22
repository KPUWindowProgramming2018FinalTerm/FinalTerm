#include "USERINTERFACE.h"

SceneNAME USER_INTERFACE::returnScene() // 현재 씬 네임을 반환
{
	return Scene;
}

void USER_INTERFACE::ALLReset()
{

}

void USER_INTERFACE::nextScene() //다음 씬을 불러온다
{
	switch (USER_INTERFACE::Scene){
	case TITLE:
		USER_INTERFACE::Scene = MAIN_LOBBY;
		break;
	case MAIN_LOBBY:
		USER_INTERFACE::Scene = SELECT_MODE;
		break;
	case SELECT_MODE:
		USER_INTERFACE::Scene = SELECT_CHAR;
		break;
	case SELECT_CHAR:
		USER_INTERFACE::Scene = INGAME;
		break;
	case INGAME:
		USER_INTERFACE::Scene = SCOREBOARD;
		break;
	case SCOREBOARD:
		USER_INTERFACE::Scene = TITLE;
		break;
	}
}

//UI가 클릭 되었는지 체크합니다.
bool USER_INTERFACE::checkInside(int x, int y, RECT rect) {
	if (rect.top<y&&rect.bottom>y&&rect.left<x&&rect.right>y) {
		return true;
	}
	else {
		return false;
	}
}
