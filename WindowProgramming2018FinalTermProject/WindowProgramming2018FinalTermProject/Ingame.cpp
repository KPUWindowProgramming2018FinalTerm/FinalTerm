#include <Windows.h>
#include "Ingame.h"
void IngameGetKey(HDC hDC, WPARAM wParam)
{
	switch (wParam)
	{

	}

}

void IngameGetKey(WPARAM wParam)
{
	switch (wParam)
	{
	case VK_BACK:
		PostQuitMessage(0);
		break;
	}

}

void IngameGetChar(HDC hDC, WPARAM wParam)
{
	switch (wParam)
	{

	}

}

void IngameGetChar(WPARAM wParam)
{
	switch (wParam)
	{

	}

}

void PlayerImageLoad(PlayerData* player, int characterNum)
{
	WCHAR LoadText[100];

	for (int i = 1; i <= 4; i++)
	{
		wsprintf(LoadText, L"Graphic\\Char%d\\ATTACK\\%d.png",characterNum, i);
		player->Attack[i-1].Load(LoadText);
		wsprintf(LoadText, L"Graphic\\Char%d\\ATTACK_B\\%d.png", characterNum, i);
		player->Attack_B[i-1].Load(LoadText);
	}
	for (int i = 1; i <= 6; i++)
	{
		wsprintf(LoadText, L"Graphic\\Char%d\\WALK\\%d.png", characterNum, i);
		player->Walk[i-1].Load(LoadText);
		wsprintf(LoadText, L"Graphic\\Char%d\\WALK_B\\%d.png", characterNum, i);
		player->Walk_B[i-1].Load(LoadText);
	}
	for (int i = 1; i <= 2; i++)
	{
		wsprintf(LoadText, L"Graphic\\Char%d\\ATTACKED\\%d.png", characterNum, i);
		player->Attacked[i - 1].Load(LoadText);
		wsprintf(LoadText, L"Graphic\\Char%d\\ATTACKED_B\\%d.png", characterNum, i);
		player->Attacked_B[i - 1].Load(LoadText);
	}

	wsprintf(LoadText, L"Graphic\\Char%d\\IDLE\\1.png", characterNum);
	player->Idle.Load(LoadText);
	wsprintf(LoadText, L"Graphic\\Char%d\\IDLE_B\\1.png", characterNum);
	player->Idle_B.Load(LoadText);
	wsprintf(LoadText, L"Graphic\\Char%d\\WIN\\1.png", characterNum);
	player->Win.Load(LoadText);
	wsprintf(LoadText, L"Graphic\\Char%d\\LOSE\\1.png", characterNum);
	player->Lose.Load(LoadText);
}