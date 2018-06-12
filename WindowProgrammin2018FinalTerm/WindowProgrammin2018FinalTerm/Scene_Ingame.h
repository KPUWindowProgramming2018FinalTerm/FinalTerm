#pragma once
#include "Scene.h"

class CObject_Player;
class OBJECT_Coin;

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

	void KeyState();
	void CharacterState();
private:
	CObject** ppObjects = NULL;
	OBJECT_Coin* CoinObject = NULL;
	int nObjects;

	CImage C_Tile[3];		//타일 이미지
	CImage C_Numbers[10];

	BOOL keydownList[14] = { 0 };	// 0 1 2 3 p2 이동 4 5 6 p2 스킬 공격 대시 7 8 9 10 p1 이동 11 12 13 p1 스킬 공격 대시
	BOOL keydown;					// 어떤 키라도 눌렸는지 확인
	BOOL isp1LockDown = FALSE;		// 공격 등 이동할 수 없는 상태
	BOOL isp2LockDown = FALSE;		// 공격 등 이동할 수 없는 상태
	BOOL coinLockDown = FALSE;		// 애니메이션용
	
	bool p1key = false;				// p1 이동키라면
	bool p2key = false;				// p2 이동키라면

	int Tileindex[100][100] = { 0 };
};