#include <iostream>
//==========================================================
//               USERINTERFACE

//���� �������̽��� Ŭ���� ����� ��Ÿ ���� �����Դϴ�.



//==========================================================

//SCENE�� ��ġ�� �����س��� ������ �Դϴ�.
enum SceneNAME {
	TITLE = 0, MAIN_LOBBY = 1, CONTROL_TIP = 2, SELECT_MODE = 3, SELECT_CHAR = 4, INGAME = 5, SCOREBOARD = 6
};

bool gameState = false;



class USER_INTERFACE {
private:
	//Ÿ��Ʋ�� ���õ� ������ �ʵ��Դϴ�.
	SceneNAME now = TITLE;




public:
	//�⺻���¿��� ���� ���� ��ȯ�մϴ�.
	void nextScene();

	

};