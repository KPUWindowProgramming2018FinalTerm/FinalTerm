#pragma once
#include "Object.h"

struct PlayerImage
{
	CImage Attack[4];
	CImage Attack_B[4];
	CImage Attacked[2];
	CImage Attacked_B[2];
	CImage Dash;
	CImage Dash_B;
	CImage Skill[10];
	int MaxImageNumOfSkill = 10;
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

	BOOL isWalk = FALSE;
	BOOL isAttack = FALSE;
	BOOL isAttacked = FALSE;
	BOOL isSkill = FALSE;
	BOOL isDash = FALSE;
	BOOL iHaveCoin = FALSE;

	int WalkingTimerTick = 0;
	int WalkingImageTick = 0;

	int AttackTimerTick = 0; //
	int AttackImageTick = 0;

	int DashTimerTick = 0;

	int CharacterStatus = 0; // 0~1 = Idle  // 2~5 = Walk // 6~7 = Attack // 8 = Win // 9 = Lose
	int Old_CharStat = 0; // 대시에서 쓰는 것

	CObject_Player();
	//CObject_Player(int characterNum, HDC PlayerDC);
	void OnCreate(int characterNum);
	~CObject_Player();

	void Update(float fTimeElapsed);
	void Render(HDC* hdc);
private:
	



};

