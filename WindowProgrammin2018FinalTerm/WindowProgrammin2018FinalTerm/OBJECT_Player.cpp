#include "stdafx.h"
#include "Object_Player.h"
#include "Framework.h"

CObject_Player::CObject_Player()
{

}

CObject_Player::~CObject_Player()
{
}
//CObject_Player::CObject_Player(int characterNum, HDC PlayerDC)
//{
//	OnCreate(characterNum, PlayerDC);
//}

void CObject_Player::OnCreate(int characterNum)
{
	WCHAR LoadText[100];

	x = characterNum * 400;
	y = characterNum * 400;

	for (int i = 1; i <= 4; i++)
	{
		wsprintf(LoadText, L"Graphic\\Char%d\\ATTACK\\%d.png", characterNum, i);
		this->Image.Attack[i - 1].Load(LoadText);
		wsprintf(LoadText, L"Graphic\\Char%d\\ATTACK_B\\%d.png", characterNum, i);
		this->Image.Attack_B[i - 1].Load(LoadText);
	}
	for (int i = 1; i <= 6; i++)
	{
		wsprintf(LoadText, L"Graphic\\Char%d\\WALK\\%d.png", characterNum, i);
		this->Image.Walk[i - 1].Load(LoadText);
		wsprintf(LoadText, L"Graphic\\Char%d\\WALK_B\\%d.png", characterNum, i);
		this->Image.Walk_B[i - 1].Load(LoadText);
	}
	for (int i = 1; i <= 2; i++)
	{
		wsprintf(LoadText, L"Graphic\\Char%d\\ATTACKED\\%d.png", characterNum, i);
		this->Image.Attacked[i - 1].Load(LoadText);
		wsprintf(LoadText, L"Graphic\\Char%d\\ATTACKED_B\\%d.png", characterNum, i);
		this->Image.Attacked_B[i - 1].Load(LoadText);
	}

	wsprintf(LoadText, L"Graphic\\Char%d\\IDLE\\1.png", characterNum);
	this->Image.Idle.Load(LoadText);
	wsprintf(LoadText, L"Graphic\\Char%d\\IDLE_B\\1.png", characterNum);
	this->Image.Idle_B.Load(LoadText);
	wsprintf(LoadText, L"Graphic\\Char%d\\WIN\\1.png", characterNum);
	this->Image.Win.Load(LoadText);
	wsprintf(LoadText, L"Graphic\\Char%d\\LOSE\\1.png", characterNum);
	this->Image.Lose.Load(LoadText);
}

void CObject_Player::Update(float fTimeElapsed)
{
	
}

void CObject_Player::Render(HDC* hdc)
{
	switch (this->CharacterStatus) // 0~1 = Idle  // 2~5 = Walk // 6~7 = Attack // 8~9 Attacked // 10 = Win // 11 = Lose
	{
	case 0:
		this->Image.Idle.Draw(*hdc, this->x - this->Image.Idle.GetWidth() / 2, this->y - 5 - this->Image.Idle.GetHeight() / 2,
			this->Image.Idle.GetWidth(), this->Image.Idle.GetHeight());
		break;
	case 1:
		this->Image.Idle_B.Draw(*hdc, this->x - this->Image.Idle_B.GetWidth() / 2, this->y - 5 - this->Image.Idle_B.GetHeight() / 2,
			this->Image.Idle_B.GetWidth(), this->Image.Idle_B.GetHeight());
		break;
	case 2:
	case 5:
		this->Image.Walk[this->WalkingImageTick % 6].Draw(*hdc, this->x - this->Image.Walk[this->WalkingImageTick % 6].GetWidth() / 2,
			this->y - 5 - this->Image.Walk[this->WalkingImageTick % 6].GetHeight() / 2, this->Image.Walk[this->WalkingImageTick % 6].GetWidth(),
			this->Image.Walk[this->WalkingImageTick % 6].GetHeight());
		break;
	case 3:
	case 4:
		this->Image.Walk_B[this->WalkingImageTick % 6].Draw(*hdc, this->x - this->Image.Walk[this->WalkingImageTick % 6].GetWidth() / 2,
			this->y - 5 - this->Image.Walk[this->WalkingImageTick % 6].GetHeight() / 2, this->Image.Walk[this->WalkingImageTick % 6].GetWidth(),
			this->Image.Walk[this->WalkingImageTick % 6].GetHeight());
		break;
	case 6:

		break;
	case 7:

		break;
	case 8:

		break;
	case 9:

		break;
	case 10:
		this->Image.Win.Draw(*hdc, this->x - this->Image.Idle_B.GetWidth() / 2, this->y - 5 - this->Image.Idle_B.GetHeight() / 2,
			this->Image.Idle_B.GetWidth(), this->Image.Idle_B.GetHeight());
		break;
	case 11:
		this->Image.Lose.Draw(*hdc, this->x - this->Image.Idle_B.GetWidth() / 2, this->y - 5 - this->Image.Idle_B.GetHeight() / 2,
			this->Image.Idle_B.GetWidth(), this->Image.Idle_B.GetHeight());
		break;
	}
}
