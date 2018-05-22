#include <iostream>
#include <Windows.h>
//==========================================================
//               USERINTERFACE

//���� �������̽��� Ŭ���� ����� ��Ÿ ���� �����Դϴ�.



//==========================================================

//SCENE�� ��ġ�� �����س��� ������ �Դϴ�.
enum SceneNAME {
	TITLE = 0, MAIN_LOBBY = 1, CONTROL_TIP = 2, SELECT_MODE = 3, SELECT_CHAR = 4, INGAME = 5, SCOREBOARD = 6
};


class USER_INTERFACE {
private:
	//Ÿ��Ʋ�� ���õ� ������ �ʵ��Դϴ�.
	//�ʱ� �����δ� Ÿ��Ʋ ���� �����ϴ�.
	SceneNAME Scene = TITLE;
	bool gameState = false;


public:
	//���� ���� �����մϴ�.
	SceneNAME returnScene() {
		return Scene;
	}
	
	//���� ������ ��� �ʱ�ȭ �մϴ�.
	void ALLReset() {

	}

	//�⺻���¿��� ���� ���� ��ȯ�մϴ�.
	void nextScene();

	//UI�� Ŭ�� �Ǿ����� üũ�մϴ�.
	bool checkInside(int x, int y, RECT rect);


};