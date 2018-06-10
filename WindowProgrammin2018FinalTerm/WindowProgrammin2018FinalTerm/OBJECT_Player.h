#pragma once
#include "Object.h"

struct PlayerImage
{
	CImage Attack[4];
	CImage Attack_B[4];
	CImage Attacked[2];
	CImage Attacked_B[2];
	CImage Idle;
	CImage Idle_B;
	CImage Walk[6];
	CImage Walk_B[6];
	CImage Win;
	CImage Lose;
};

class CObject_Player : public CObject
{

public:
	PlayerImage Image;

	int x=0;
	int y=0;

	CObject_Player();
	//CObject_Player(int characterNum, HDC PlayerDC);
	void OnCreate(int characterNum);
	~CObject_Player();

	void Update(float fTimeElapsed);
	void Render(HDC* hdc);
private:
	BOOL isWalk = FALSE;
	
	int WalkingTimerTick = 0; //타이머돌려서 10되면 Idle로
	int WalkingImageTick = 0;

	int AttackTimerTick = 0; //
	int AttackImageTick = 0;

	int CharacterStatus = 0; // 0~1 = Idle  // 2~5 = Walk // 6~7 = Attack // 8 = Win // 9 = Lose



};

