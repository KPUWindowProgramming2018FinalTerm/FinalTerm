#include "USERINTERFACE.h"

//�⺻���¿��� ���� ���� ��ȯ�մϴ�.
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

<<<<<<< HEAD
//UI�� Ŭ�� �Ǿ����� üũ�մϴ�.
bool USER_INTERFACE::checkInside(int x, int y, RECT rect) {
	if (rect.top<y&&rect.bottom>y&&rect.left<x&&rect.right>y) {
		return true;
	}
	else {
		return false;
	}
}

=======
>>>>>>> 98f02b041e4af96e2b53d80c9a41b7df7c8d9984

