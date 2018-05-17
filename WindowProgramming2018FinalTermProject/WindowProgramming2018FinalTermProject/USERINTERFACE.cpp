#include "USERINTERFACE.h"

//기본상태에서 다음 씬을 소환합니다.
void USER_INTERFACE::nextScene() {
	switch (USER_INTERFACE::Scene){
	case TITLE:
		USER_INTERFACE::Scene = MAIN_LOBBY;
		break;
	case MAIN_LOBBY:
		USER_INTERFACE::Scene = SELECT_MODE;
		break;
	case SELECT_MODE:
		USER_INTERFACE::Scene = SELECT_CHAR;
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

<<<<<<< HEAD



=======
>>>>>>> 04af0f603ae5780de7277712e4773f2b30d52294
