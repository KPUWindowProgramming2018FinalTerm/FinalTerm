#include "stdafx.h"
#include "Scene_Ingame.h"
#include "OBJECT_Player.h"
#include "Framework.h"


CIngameScene::CIngameScene()
{

}
CIngameScene::~CIngameScene()
{

}
CIngameScene::CIngameScene(SceneTag tag, CFramework * pFramework) : CScene(tag, pFramework)
{

}
bool CIngameScene::OnCreate()
{	
	C_Tile[0].Load(L"Graphic\\Tile\\Tile1.jpg");
	C_Tile[1].Load(L"Graphic\\Tile\\Tile2.png");
	C_Tile[2].Load(L"Graphic\\Tile\\Tile3.png");


	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			Tileindex[j][i] = 0;
			if (j > 20 && j < 40)
				Tileindex[j][i] = 1;
			if (j > 15 && j < 17 && i % 3 == 0)
				Tileindex[j][i] = 2;
		}
	}

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			C_Tile[Tileindex[j][i]].BitBlt(*m_pFramework->GetTileDC(), 64 * j, 64 * i, 64, 64, 0, 0, SRCCOPY); //타일의 가로세로크기가 64바이트
		}
	}
	BuildObjects();

	return true;
}


void CIngameScene::BuildObjects()
{
	nObjects = 0;
	/*CObject** ppObjects;
	int nObjects; 여기다 값넣기*/

	/*nObjects = 2;
	ppObjects[0] = m_pFramework->GetPlayer(1);
	ppObjects[1] = m_pFramework->GetPlayer(2);*/
}

void CIngameScene::Update(float fTimeElapsed)
{
	{ //동시 입력 인식
		keydown = FALSE;
		for (int i = 0; i < 14; i++)
		{
			keydownList[i] = FALSE;
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			keydownList[1] = TRUE;

			keydown = TRUE;
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			keydownList[0] = TRUE;

			keydown = TRUE;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			keydownList[3] = TRUE;

			keydown = TRUE;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			keydownList[2] = TRUE;

			keydown = TRUE;
		}

		if (GetAsyncKeyState(0x46) & 0x8000) // f
		{
			keydownList[7] = TRUE;

			keydown = TRUE;
		}
		if (GetAsyncKeyState(0x54) & 0x8000) // t
		{
			keydownList[8] = TRUE;

			keydown = TRUE;
		}
		if (GetAsyncKeyState(0x48) & 0x8000) // h
		{
			keydownList[9] = TRUE;

			keydown = TRUE;
		}
		if (GetAsyncKeyState(0x47) & 0x8000) // g
		{
			keydownList[10] = TRUE;

			keydown = TRUE;
		}
	}
	{
		if (keydown)
		{
			p1key = false;
			p2key = false;
			// 0 1 2 3 p1 이동 4 5 6 p1 공격 스킬 대시 7 8 9 10 p2 이동 11 12 13 p2 공격 스킬 대시
			if (keydownList[1])
			{
				if (Tileindex[m_pFramework->GetPlayer(2)->x / 64][(m_pFramework->GetPlayer(2)->y + 60) / 64] == 1)
				{
					m_pFramework->GetPlayer(2)->y -= 25;
				}
				else if (Tileindex[m_pFramework->GetPlayer(2)->x / 64][(m_pFramework->GetPlayer(2)->y + 60 - 20) / 64] == 2)
				{

				}
				else
				{
					m_pFramework->GetPlayer(2)->y -= 10;
				}
				p2key = true;
				m_pFramework->GetPlayer(2)->CharacterStatus = 3;

			}
			if (keydownList[0])
			{
				if (Tileindex[m_pFramework->GetPlayer(2)->x / 64][(m_pFramework->GetPlayer(2)->y + 60) / 64] == 1)
				{
					m_pFramework->GetPlayer(2)->x -= 25;
				}
				else if (Tileindex[(m_pFramework->GetPlayer(2)->x - 30) / 64][m_pFramework->GetPlayer(2)->y + 60 / 64] == 2)
				{

				}
				else
				{
					m_pFramework->GetPlayer(2)->x -= 10;
				}
				p2key = true;
				m_pFramework->GetPlayer(2)->CharacterStatus = 2;

			}
			if (keydownList[3])
			{
				if (Tileindex[m_pFramework->GetPlayer(2)->x / 64][(m_pFramework->GetPlayer(2)->y + 60) / 64] == 1)
				{
					m_pFramework->GetPlayer(2)->y += 25;
				}
				else if (Tileindex[m_pFramework->GetPlayer(2)->x / 64][(m_pFramework->GetPlayer(2)->y + 60 + 30) / 64] == 2)
				{

				}
				else
				{
					m_pFramework->GetPlayer(2)->y += 10;
				}
				p2key = true;
				m_pFramework->GetPlayer(2)->CharacterStatus = 5;

			}
			if (keydownList[2])
			{
				if (Tileindex[m_pFramework->GetPlayer(2)->x / 64][(m_pFramework->GetPlayer(2)->y + 60) / 64] == 1)
				{
					m_pFramework->GetPlayer(2)->x += 25;
				}
				else if (Tileindex[(m_pFramework->GetPlayer(2)->x + 30) / 64][(m_pFramework->GetPlayer(2)->y + 60) / 64] == 2)
				{

				}
				else
				{
					m_pFramework->GetPlayer(2)->x += 10;
				}
				p2key = true;
				m_pFramework->GetPlayer(2)->CharacterStatus = 4;

			}

			if (keydownList[4])
			{

			}
			if (keydownList[5])
			{

			}
			if (keydownList[6])
			{

			}
			if (keydownList[8])
			{
				if (Tileindex[m_pFramework->GetPlayer(1)->x / 64][(m_pFramework->GetPlayer(1)->y + 60) / 64] == 1)
				{
					m_pFramework->GetPlayer(1)->y -= 25;
				}
				else if (Tileindex[m_pFramework->GetPlayer(1)->x / 64][(m_pFramework->GetPlayer(1)->y + 60 - 30) / 64] == 2)
				{

				}
				else
				{
					m_pFramework->GetPlayer(1)->y -= 10;
				}
				p1key = true;
				m_pFramework->GetPlayer(1)->CharacterStatus = 3;
			}
			if (keydownList[7])
			{
				if (Tileindex[m_pFramework->GetPlayer(1)->x / 64][(m_pFramework->GetPlayer(1)->y + 60) / 64] == 1)
				{
					m_pFramework->GetPlayer(1)->x -= 25;
				}
				else if (Tileindex[(m_pFramework->GetPlayer(1)->x - 30) / 64][(m_pFramework->GetPlayer(1)->y + 60) / 64] == 2)
				{

				}
				else
				{
					m_pFramework->GetPlayer(1)->x -= 10;
				}
				p1key = true;
				m_pFramework->GetPlayer(1)->CharacterStatus = 2;
			}
			if (keydownList[10])
			{
				if (Tileindex[m_pFramework->GetPlayer(1)->x / 64][(m_pFramework->GetPlayer(1)->y + 60) / 64] == 1)
				{
					m_pFramework->GetPlayer(1)->y += 25;
				}
				else if (Tileindex[m_pFramework->GetPlayer(1)->x / 64][(m_pFramework->GetPlayer(1)->y + 60 + 30) / 64] == 2)
				{

				}
				else
				{
					m_pFramework->GetPlayer(1)->y += 10;
				}
				p1key = true;
				m_pFramework->GetPlayer(1)->CharacterStatus = 5;
			}
			if (keydownList[9])
			{
				if (Tileindex[m_pFramework->GetPlayer(1)->x / 64][(m_pFramework->GetPlayer(1)->y + 60) / 64] == 1)
				{
					m_pFramework->GetPlayer(1)->x += 25;
				}
				else if (Tileindex[(m_pFramework->GetPlayer(1)->x + 30) / 64][(m_pFramework->GetPlayer(1)->y + 60) / 64] == 2)
				{

				}
				else
				{
					m_pFramework->GetPlayer(1)->x += 10;
				}
				p1key = true;
				m_pFramework->GetPlayer(1)->CharacterStatus = 4;
			}

			if (keydownList[11])
			{

			}
			if (keydownList[12])
			{

			}
			if (keydownList[13])
			{

			}

			if (p1key)
			{	
				m_pFramework->GetPlayer(1)->isWalk = TRUE;
				m_pFramework->GetPlayer(1)->WalkingTimerTick = 0;
				m_pFramework->GetPlayer(1)->WalkingImageTick++;
			}
			if (p2key)
			{
				m_pFramework->GetPlayer(2)->isWalk = TRUE;
				m_pFramework->GetPlayer(2)->WalkingTimerTick = 0;
				m_pFramework->GetPlayer(2)->WalkingImageTick++;
			}
		}
	}

	for (int i = 0; i < nObjects; ++i)
		ppObjects[i]->Update(fTimeElapsed);
}

void CIngameScene::Render(HDC hdc)
{
	BitBlt(*m_pFramework->GetPlayerDC(), m_pFramework->GetPlayer(1)->x - m_pFramework->p1.right / 2, m_pFramework->GetPlayer(1)->y - m_pFramework->p1.bottom / 2, m_pFramework->p1.right, m_pFramework->p1.bottom,
		*m_pFramework->GetTileDC(), m_pFramework->GetPlayer(1)->x - m_pFramework->p1.right / 2, m_pFramework->GetPlayer(1)->y - m_pFramework->p1.bottom / 2, SRCCOPY);
	BitBlt(*m_pFramework->GetPlayerDC(), m_pFramework->GetPlayer(2)->x - m_pFramework->p1.right / 2, m_pFramework->GetPlayer(2)->y - m_pFramework->p1.bottom / 2, m_pFramework->p1.right, m_pFramework->p2.bottom,
		*m_pFramework->GetTileDC(), m_pFramework->GetPlayer(2)->x - m_pFramework->p1.right / 2, m_pFramework->GetPlayer(2)->y - m_pFramework->p2.bottom / 2, SRCCOPY);

	m_pFramework->GetPlayer(1)->Render(m_pFramework->GetPlayerDC());
	m_pFramework->GetPlayer(2)->Render(m_pFramework->GetPlayerDC());

	Ellipse(*m_pFramework->GetPlayerDC(), m_pFramework->GetPlayer(1)->x - 5, m_pFramework->GetPlayer(1)->y - 5, m_pFramework->GetPlayer(1)->x + 5, m_pFramework->GetPlayer(1)->y + 5);
	Ellipse(*m_pFramework->GetPlayerDC(), m_pFramework->GetPlayer(2)->x - 5, m_pFramework->GetPlayer(2)->y - 5, m_pFramework->GetPlayer(2)->x + 5, m_pFramework->GetPlayer(2)->y + 5);

	BitBlt(m_pFramework->GetTotalDC(), m_pFramework->p1.left, m_pFramework->p1.top, m_pFramework->p1.right, m_pFramework->p1.bottom, *m_pFramework->GetPlayerDC(), m_pFramework->GetPlayer(1)->x - m_pFramework->p1.right / 2, m_pFramework->GetPlayer(1)->y - m_pFramework->p1.bottom / 2, SRCCOPY);
	BitBlt(m_pFramework->GetTotalDC(), m_pFramework->p2.left, m_pFramework->p2.top, m_pFramework->p1.right, m_pFramework->p2.bottom, *m_pFramework->GetPlayerDC(), m_pFramework->GetPlayer(2)->x - m_pFramework->p1.right / 2, m_pFramework->GetPlayer(2)->y - m_pFramework->p2.bottom / 2, SRCCOPY);
	
	
	for (int i = 0; i < nObjects; ++i)
		ppObjects[i]->Render(*m_pFramework->GetPlayerDC());
}


