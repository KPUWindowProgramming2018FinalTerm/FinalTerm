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
	SceneNAME now = TITLE;

	//������ ���¸� ��Ÿ���ϴ�.
	bool gameState = false;




public:
	//�⺻���¿��� ���� ���� ��ȯ�մϴ�.
	void nextScene();

	

};