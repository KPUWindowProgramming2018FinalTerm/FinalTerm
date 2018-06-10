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


