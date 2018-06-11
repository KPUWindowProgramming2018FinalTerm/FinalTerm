#pragma once
#include "Scene.h"

class CObject_Player;

class CIngameScene : public CScene
{
public:
	CIngameScene();
	~CIngameScene();
	CIngameScene(SceneTag tag, CFramework * pFramework);

	bool OnCreate() override;
	void BuildObjects() override;
	void Render(HDC hdc) override;				// FrameAdvanced
	void Update(float fTimeElapsed) override;	// m_pCurrScene->Update();
												// m_pCurrScene->Render(m_hdc);
private:
	CObject** ppObjects = NULL;
	int nObjects;

	CImage C_Tile[3];		//Ÿ�� �̹���
	CImage C_Numbers[10];

	BOOL keydownList[14] = { 0 };	// 0 1 2 3 p2 �̵� 4 5 6 p2 ��ų ���� ��� 7 8 9 10 p1 �̵� 11 12 13 p1 ��ų ���� ���
	BOOL keydown;					// � Ű�� ���ȴ��� Ȯ��
	BOOL isp1LockDown = FALSE;		// ���� �� �̵��� �� ���� ����
	BOOL isp2LockDown = FALSE;		// ���� �� �̵��� �� ���� ����
	
	bool p1key = false;				// p1 �̵�Ű���
	bool p2key = false;				// p2 �̵�Ű���

	int Tileindex[100][100] = { 0 };
};