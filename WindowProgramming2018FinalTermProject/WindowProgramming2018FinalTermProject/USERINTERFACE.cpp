#include "USERINTERFACE.h"

//�⺻���¿��� ���� ���� ��ȯ�մϴ�.
void USER_INTERFACE::nextScene() {
	switch (USER_INTERFACE::now){
	case TITLE:
		USER_INTERFACE::now = MAIN_LOBBY;
		break;
	case MAIN_LOBBY:
		USER_INTERFACE::now = SELECT_MODE;
		break;
	case SELECT_MODE:
		USER_INTERFACE::now = SELECT_CHAR;
	case SELECT_CHAR:
		USER_INTERFACE::now = INGAME;
		break;
	case INGAME:
		USER_INTERFACE::now = SCOREBOARD;
		break;
	case SCOREBOARD:
		USER_INTERFACE::now = TITLE;
		break;
	}
}


