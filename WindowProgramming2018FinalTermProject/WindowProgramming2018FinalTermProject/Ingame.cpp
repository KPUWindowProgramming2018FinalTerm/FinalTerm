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