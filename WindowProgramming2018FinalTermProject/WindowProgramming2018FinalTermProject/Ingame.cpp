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
		wsprintf(LoadText, L"Graphic\\Char%d\\Attack\\%d.jpg",characterNum, i);
		player->Attack[i-1].Load(LoadText);
		wsprintf(LoadText, L"Graphic\\Char%d\\Attack_Back\\%d.jpg", characterNum, i);
		player->Attack_B[i-1].Load(LoadText);
	}
	for (int i = 1; i <= 6; i++)
	{
		wsprintf(LoadText, L"Graphic\\Char%d\\Walk\\%d.jpg", characterNum, i);
		player->Walk[i-1].Load(LoadText);
		wsprintf(LoadText, L"Graphic\\Char%d\\Walk_Back\\%d.jpg", characterNum, i);
		player->Walk_B[i-1].Load(LoadText);
	}
	wsprintf(LoadText, L"Graphic\\Char%d\\Idle\\1.jpg", characterNum);
	player->Idle.Load(LoadText);
	wsprintf(LoadText, L"Graphic\\Char%d\\Idle_Back\\1.jpg", characterNum);
	player->Idle_B.Load(LoadText);
	wsprintf(LoadText, L"Graphic\\Char%d\\Win\\1.jpg", characterNum);
	player->Win.Load(LoadText);
	wsprintf(LoadText, L"Graphic\\Char%d\\Lose\\1.jpg", characterNum);
	player->Lose.Load(LoadText);
}