#pragma once

//=====================================
// Ingame �Լ� ���
//=====================================

typedef struct _PlayerData
{
	int x;
	int y;
}PlayerData;

void IngameGetKey(HDC hDC, WPARAM wParam);
void IngameGetKey(WPARAM wParam);

void IngameGetChar(HDC hDC, WPARAM wParam);
void IngameGetChar(WPARAM wParam);