#include "stdafx.h"
#include "Scene_Ingame.h"
#include "OBJECT_Player.h"
#include "OBJECT_Coin.h"
#include "Framework.h"


CIngameScene::CIngameScene()
{

}
CIngameScene::~CIngameScene()
{
	if (CoinObject != NULL)
	{
		free(CoinObject);
	}

}
CIngameScene::CIngameScene(SceneTag tag, CFramework * pFramework) : CScene(tag, pFramework) //�����ӿ�ũ ������ Ȱ��ȭ
{

}
bool CIngameScene::OnCreate()
{	
	C_Tile[0].Load(L"Graphic\\Tile\\Tile1.jpg");
	C_Tile[1].Load(L"Graphic\\Tile\\Tile2.png");
	C_Tile[2].Load(L"Graphic\\Tile\\Tile3.png");

	C_IngameLine.Load(L"Graphic\\UI\\INGAME UI.png");

	WinC.Load(L"Graphic\\UI\\WIN.png");
	LoseC.Load(L"Graphic\\UI\\LOSE.png");

	WCHAR LoadText[100];
	for (int i = 0; i <= 9; i++)
	{
		wsprintf(LoadText, L"Graphic\\Numbers\\%d.png", i);
		this->C_Numbers[i].Load(LoadText);
	}

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
			C_Tile[Tileindex[j][i]].BitBlt(*m_pFramework->GetTileDC(), 64 * j, 64 * i, 64, 64, 0, 0, SRCCOPY); //Ÿ���� ���μ���ũ�Ⱑ 64����Ʈ
		}
	}
	RemainTime = 5;
	TimeTick = 0;
	TimerImage[0] = 9;
	TimerImage[1] = 9;
	BuildObjects();

	return true;
}


void CIngameScene::BuildObjects()
{
	nObjects = 0;
	CoinObject = new OBJECT_Coin(100,100);
	/*CObject** ppObjects;
	int nObjects; ����� ���ֱ�*/

	/*nObjects = 2;
	ppObjects[0] = m_pFramework->GetPlayer(1);
	ppObjects[1] = m_pFramework->GetPlayer(2);*/
}

void CIngameScene::KeyState()
{
	if (keydown != TRUE)
	{
		if (isp2LockDown != TRUE)
		{
			if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000) // ��ų
			{
				keydownList[4] = TRUE;

				keydown = TRUE;
				isp2LockDown = TRUE;
			}
			else if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000) // ����
			{
				keydownList[5] = TRUE;

				keydown = TRUE;
				isp2LockDown = TRUE;
			}
			else if (GetAsyncKeyState(VK_NUMPAD3) & 0x8000) //���
			{
				keydownList[6] = TRUE;

				keydown = TRUE;
				isp2LockDown = TRUE;
			}
			else
			{
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
			}
		}
		else
		{
			if (m_pFramework->GetPlayer(2)->isAttack)
			{
				if (m_pFramework->GetPlayer(2)->AttackTimerTick++ > 3)
				{
					m_pFramework->GetPlayer(2)->AttackTimerTick = 0;
					if (m_pFramework->GetPlayer(2)->AttackImageTick++ > 2)
					{
						m_pFramework->GetPlayer(2)->isAttack = FALSE;
						m_pFramework->GetPlayer(2)->AttackTimerTick = 0;
						m_pFramework->GetPlayer(2)->AttackImageTick = 0;
						//printf("%d", m_pFramework->GetPlayer(2)->CharacterStatus);
						if (m_pFramework->GetPlayer(2)->CharacterStatus == 6)
							m_pFramework->GetPlayer(2)->CharacterStatus = 0;
						else
							m_pFramework->GetPlayer(2)->CharacterStatus = 1;
						isp2LockDown = FALSE;

					}
				}
			}
			else if (m_pFramework->GetPlayer(2)->isSkill)
			{

			}
			else if (m_pFramework->GetPlayer(2)->isDash)
			{
				if (m_pFramework->GetPlayer(2)->DashTimerTick++ > 10)
				{
					m_pFramework->GetPlayer(2)->DashTimerTick = 0;
					m_pFramework->GetPlayer(2)->isDash = FALSE;
					m_pFramework->GetPlayer(2)->CharacterStatus = m_pFramework->GetPlayer(2)->Old_CharStat;
					isp2LockDown = FALSE;
					p2key = TRUE;
				}
				switch (m_pFramework->GetPlayer(2)->Old_CharStat)
				{
				case 2:
				case 0:
					if (m_pFramework->GetPlayer(2)->x > 50)
						m_pFramework->GetPlayer(2)->x -= 25;
					
					break;
				case 5:
					if (m_pFramework->GetPlayer(2)->y < 6350)
						m_pFramework->GetPlayer(2)->y += 25;
					
					break; // �� �� ��
				case 3:
					if (m_pFramework->GetPlayer(2)->y > 50)
						m_pFramework->GetPlayer(2)->y -= 25;
					
					break;
				case 4:
				case 1:
					if (m_pFramework->GetPlayer(2)->x < 6350)
						m_pFramework->GetPlayer(2)->x += 25;
					
					break; // �� �� ��
				}
			}
			else if (m_pFramework->GetPlayer(2)->isAttacked)
			{
				if (m_pFramework->GetPlayer(2)->AttackTimerTick++ > 20)
				{
					m_pFramework->GetPlayer(2)->AttackTimerTick = 0;
					m_pFramework->GetPlayer(2)->isAttacked = FALSE;
					m_pFramework->GetPlayer(2)->CharacterStatus = m_pFramework->GetPlayer(2)->Old_CharStat;
					isp2LockDown = FALSE;
					p2key = TRUE;
				}
				if (m_pFramework->GetPlayer(2)->AttackTimerTick < 10)
				{
					switch (m_pFramework->GetPlayer(1)->Old_CharStat)
					{
					case 2:
					case 0:
						if (m_pFramework->GetPlayer(2)->x > 50)
							m_pFramework->GetPlayer(2)->x -= 15;
						if (coinLockDown)
						CoinObject->Setx(CoinObject->x() - 5);
						break;
					case 5:
						if (m_pFramework->GetPlayer(2)->y < 6350)
							m_pFramework->GetPlayer(2)->y += 15;
						if (coinLockDown)
						CoinObject->Setx(CoinObject->y() + 5);
						break; // �� �� ��
					case 3:
						if (m_pFramework->GetPlayer(2)->y > 50)
							m_pFramework->GetPlayer(2)->y -= 15;
						if (coinLockDown)
						CoinObject->Setx(CoinObject->y() - 5);
						break;
					case 4:
					case 1:
						if (m_pFramework->GetPlayer(2)->x < 6350)
							m_pFramework->GetPlayer(2)->x += 15;
						if (coinLockDown)
						CoinObject->Setx(CoinObject->x() + 5);
						break; // �� �� ��
					}
				}
				else
				{
					coinLockDown = FALSE;
				}
			}
		}
		if (isp1LockDown != TRUE)
		{
			if (GetAsyncKeyState(0x41) & 0x8000)
			{
				keydownList[11] = TRUE;

				keydown = TRUE;
				isp1LockDown = TRUE;
			}
			else if (GetAsyncKeyState(0x53) & 0x8000)
			{
				keydownList[12] = TRUE;

				keydown = TRUE;
				isp1LockDown = TRUE;
			}
			else if (GetAsyncKeyState(0x44) & 0x8000)
			{
				keydownList[13] = TRUE;

				keydown = TRUE;
				isp1LockDown = TRUE;
			}
			else
			{
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
		}
		else
		{
			if (m_pFramework->GetPlayer(1)->isAttack)
			{
				if (m_pFramework->GetPlayer(1)->AttackTimerTick++ > 3)
				{
					m_pFramework->GetPlayer(1)->AttackTimerTick = 0;
					if (m_pFramework->GetPlayer(1)->AttackImageTick++ > 2)
					{
						m_pFramework->GetPlayer(1)->isAttack = FALSE;
						m_pFramework->GetPlayer(1)->AttackTimerTick = 0;
						m_pFramework->GetPlayer(1)->AttackImageTick = 0;
						printf("%d", m_pFramework->GetPlayer(1)->CharacterStatus);
						if (m_pFramework->GetPlayer(1)->CharacterStatus == 6)
							m_pFramework->GetPlayer(1)->CharacterStatus = 0;
						else
							m_pFramework->GetPlayer(1)->CharacterStatus = 1;
						isp1LockDown = FALSE;

					}
				}
			}
			else if (m_pFramework->GetPlayer(1)->isSkill)
			{

			}
			else if (m_pFramework->GetPlayer(1)->isDash)
			{
				if (m_pFramework->GetPlayer(1)->DashTimerTick++ > 10)
				{
					m_pFramework->GetPlayer(1)->DashTimerTick = 0;
					m_pFramework->GetPlayer(1)->isDash = FALSE;
					m_pFramework->GetPlayer(1)->CharacterStatus = m_pFramework->GetPlayer(1)->Old_CharStat;
					p1key = true;
					isp1LockDown = FALSE;
				}
				switch (m_pFramework->GetPlayer(1)->Old_CharStat)
				{
				case 2:
				case 0:
					if (m_pFramework->GetPlayer(1)->x > 50)
					m_pFramework->GetPlayer(1)->x -= 25;
					break;
				case 5:
					if (m_pFramework->GetPlayer(1)->y < 6350)
					m_pFramework->GetPlayer(1)->y += 25;
					break; // �� �� ��
				case 3:
					if (m_pFramework->GetPlayer(1)->y > 50)
					m_pFramework->GetPlayer(1)->y -= 25;
					break;
				case 4:
				case 1:
					if (m_pFramework->GetPlayer(1)->x < 6350)
					m_pFramework->GetPlayer(1)->x += 25;
					break; // �� �� ��
				}
			}
			else if (m_pFramework->GetPlayer(1)->isAttacked)
			{
				if (m_pFramework->GetPlayer(1)->AttackTimerTick++ > 20)
				{
					m_pFramework->GetPlayer(1)->AttackTimerTick = 0;
					m_pFramework->GetPlayer(1)->isAttacked = FALSE;
					m_pFramework->GetPlayer(1)->CharacterStatus = m_pFramework->GetPlayer(1)->Old_CharStat;
					isp1LockDown = FALSE;
					p1key = TRUE;
				}
				if (m_pFramework->GetPlayer(1)->AttackTimerTick < 10)
				{
					switch (m_pFramework->GetPlayer(2)->Old_CharStat)
					{
					case 2:
					case 0:
						if (m_pFramework->GetPlayer(1)->x > 50)
							m_pFramework->GetPlayer(1)->x -= 15;
						if (coinLockDown)
						CoinObject->Setx(CoinObject->x() - 5);
						break;
					case 5:
						if (m_pFramework->GetPlayer(1)->y < 6350)
							m_pFramework->GetPlayer(1)->y += 15;
						if (coinLockDown)
						CoinObject->Setx(CoinObject->y() + 5);
						break; // �� �� ��
					case 3:
						if (m_pFramework->GetPlayer(1)->y > 50)
							m_pFramework->GetPlayer(1)->y -= 15;
						if (coinLockDown)
						CoinObject->Setx(CoinObject->y() - 5);
						break;
					case 4:
					case 1:
						if (m_pFramework->GetPlayer(1)->x < 6350)
							m_pFramework->GetPlayer(1)->x += 15;
						if (coinLockDown)
						CoinObject->Setx(CoinObject->x() + 5);
						break; // �� �� ��
					}
				}
				else
				{
					coinLockDown = FALSE;
				}

			}
		}
	}
}

void CIngameScene::CharacterState()
{
	if (keydown)
	{
		// 0 1 2 3 p2 �̵� 4 5 6 p2 ��ų ���� ��� 7 8 9 10 p1 �̵� 11 12 13 p1 ��ų ���� ���
		if (keydownList[1])
		{
			if (Tileindex[m_pFramework->GetPlayer(2)->x / 64][(m_pFramework->GetPlayer(2)->y + 60) / 64] == 1)
			{
				if (m_pFramework->GetPlayer(2)->y > 50)
					m_pFramework->GetPlayer(2)->y -= 20;
				m_pFramework->GetPlayer(2)->WalkingTimerTick++;
			}
			else if (Tileindex[m_pFramework->GetPlayer(2)->x / 64][(m_pFramework->GetPlayer(2)->y + 60 - 20) / 64] == 2)
			{

			}
			else
			{
				if (m_pFramework->GetPlayer(2)->y > 50)
					m_pFramework->GetPlayer(2)->y -= 10;
			}
			p2key = true;
			m_pFramework->GetPlayer(2)->CharacterStatus = 3;

		}
		if (keydownList[0])
		{
			if (Tileindex[m_pFramework->GetPlayer(2)->x / 64][(m_pFramework->GetPlayer(2)->y + 60) / 64] == 1)
			{
				if (m_pFramework->GetPlayer(2)->x > 50)
					m_pFramework->GetPlayer(2)->x -= 20;
				m_pFramework->GetPlayer(2)->WalkingTimerTick++;
			}
			else if (Tileindex[((m_pFramework->GetPlayer(2)->x) - 30) / 64][(m_pFramework->GetPlayer(2)->y + 60 - 10) / 64] == 2)
			{

			}
			else
			{
				if (m_pFramework->GetPlayer(2)->x > 50)
				m_pFramework->GetPlayer(2)->x -= 10;
			}
			p2key = true;
			m_pFramework->GetPlayer(2)->CharacterStatus = 2;

		}
		if (keydownList[3])
		{
			if (Tileindex[m_pFramework->GetPlayer(2)->x / 64][(m_pFramework->GetPlayer(2)->y + 60) / 64] == 1)
			{
				if (m_pFramework->GetPlayer(2)->y < 6350)
				m_pFramework->GetPlayer(2)->y += 20;
				m_pFramework->GetPlayer(2)->WalkingTimerTick++;
			}
			else if (Tileindex[m_pFramework->GetPlayer(2)->x / 64][(m_pFramework->GetPlayer(2)->y + 60 + 20) / 64] == 2)
			{

			}
			else
			{
				if (m_pFramework->GetPlayer(2)->y < 6350)
				m_pFramework->GetPlayer(2)->y += 10;
			}
			p2key = true;
			m_pFramework->GetPlayer(2)->CharacterStatus = 5;

		}
		if (keydownList[2])
		{
			if (Tileindex[m_pFramework->GetPlayer(2)->x / 64][(m_pFramework->GetPlayer(2)->y + 60) / 64] == 1)
			{
				if (m_pFramework->GetPlayer(2)->x < 6350)
				m_pFramework->GetPlayer(2)->x += 20;
				m_pFramework->GetPlayer(2)->WalkingTimerTick++;
			}
			else if (Tileindex[(m_pFramework->GetPlayer(2)->x + 30) / 64][(m_pFramework->GetPlayer(2)->y + 60) / 64] == 2)
			{

			}
			else
			{
				if (m_pFramework->GetPlayer(2)->x < 6350)
				m_pFramework->GetPlayer(2)->x += 10;
			}
			p2key = true;
			m_pFramework->GetPlayer(2)->CharacterStatus = 4;

		}

		if (keydownList[4]) // p2 ��ų
		{

		}
		if (keydownList[5]) // p2 ����
		{
			switch (m_pFramework->GetPlayer(2)->CharacterStatus)
			{
			case 2:
			case 5:
			case 6:
			case 0:
				m_pFramework->GetPlayer(2)->Old_CharStat = m_pFramework->GetPlayer(2)->CharacterStatus;
				m_pFramework->GetPlayer(2)->isAttack = TRUE;
				m_pFramework->GetPlayer(2)->CharacterStatus = 6;
				if ((m_pFramework->GetPlayer(2)->x - m_pFramework->GetPlayer(1)->x < 70) &&
					(m_pFramework->GetPlayer(1)->y - m_pFramework->GetPlayer(2)->y < 50) &&
					(m_pFramework->GetPlayer(1)->y - m_pFramework->GetPlayer(2)->y > -50))
				{
					m_pFramework->GetPlayer(1)->Old_CharStat = m_pFramework->GetPlayer(1)->CharacterStatus;
					m_pFramework->GetPlayer(1)->isAttacked = TRUE;
					m_pFramework->GetPlayer(1)->CharacterStatus = 9;
					isp1LockDown = TRUE;
					if (m_pFramework->GetPlayer(1)->iHaveCoin)
					{
						m_pFramework->GetPlayer(1)->iHaveCoin = FALSE;
						CoinObject->OnCreate(m_pFramework->GetPlayer(1)->x, m_pFramework->GetPlayer(1)->y);
						coinLockDown = TRUE;
					}
				}
				break; // �� �� ��
			case 3:
			case 4:
			case 7:
			case 1:
				m_pFramework->GetPlayer(2)->Old_CharStat = m_pFramework->GetPlayer(2)->CharacterStatus;
				m_pFramework->GetPlayer(2)->isAttack = TRUE;
				m_pFramework->GetPlayer(2)->CharacterStatus = 7;
				if ((m_pFramework->GetPlayer(1)->x - m_pFramework->GetPlayer(2)->x < 70) &&
					(m_pFramework->GetPlayer(2)->y - m_pFramework->GetPlayer(1)->y < 50) &&
					(m_pFramework->GetPlayer(2)->y - m_pFramework->GetPlayer(1)->y > -50))
				{
					m_pFramework->GetPlayer(1)->Old_CharStat = m_pFramework->GetPlayer(1)->CharacterStatus;
					m_pFramework->GetPlayer(1)->isAttacked = TRUE;
					m_pFramework->GetPlayer(1)->CharacterStatus = 8;
					isp1LockDown = TRUE;
					if (m_pFramework->GetPlayer(1)->iHaveCoin)
					{
						m_pFramework->GetPlayer(1)->iHaveCoin = FALSE;
						CoinObject->OnCreate(m_pFramework->GetPlayer(1)->x, m_pFramework->GetPlayer(1)->y);
						coinLockDown = TRUE;
					}
				}
				break; // �� �� ��
			}
		}
		if (keydownList[6]) // p2 ���
		{
			m_pFramework->GetPlayer(2)->Old_CharStat = m_pFramework->GetPlayer(2)->CharacterStatus;
			switch (m_pFramework->GetPlayer(2)->CharacterStatus)
			{
			case 2:
			case 5:
			case 0:
				m_pFramework->GetPlayer(2)->isDash = TRUE;
				m_pFramework->GetPlayer(2)->CharacterStatus = 10;
				break; // �� �� ��
			case 3:
			case 4:
			case 1:
				m_pFramework->GetPlayer(2)->isDash = TRUE;
				m_pFramework->GetPlayer(2)->CharacterStatus = 11;
				break; // �� �� ��
			}
		}
		if (keydownList[8])
		{
			if (Tileindex[m_pFramework->GetPlayer(1)->x / 64][(m_pFramework->GetPlayer(1)->y + 60) / 64] == 1)
			{
				if (m_pFramework->GetPlayer(1)->y > 50)
				m_pFramework->GetPlayer(1)->y -= 20;
				m_pFramework->GetPlayer(1)->WalkingTimerTick++;
			}
			else if (Tileindex[m_pFramework->GetPlayer(1)->x / 64][(m_pFramework->GetPlayer(1)->y + 60 - 30) / 64] == 2)
			{

			}
			else
			{
				if (m_pFramework->GetPlayer(1)->y > 50)
				m_pFramework->GetPlayer(1)->y -= 10;
			}
			p1key = true;
			m_pFramework->GetPlayer(1)->CharacterStatus = 3;
		}
		if (keydownList[7])
		{
			if (Tileindex[m_pFramework->GetPlayer(1)->x / 64][(m_pFramework->GetPlayer(1)->y + 60) / 64] == 1)
			{
				if (m_pFramework->GetPlayer(1)->x > 50)
				m_pFramework->GetPlayer(1)->x -= 20;
				m_pFramework->GetPlayer(1)->WalkingTimerTick++;
			}
			else if (Tileindex[(m_pFramework->GetPlayer(1)->x - 30) / 64][(m_pFramework->GetPlayer(1)->y + 60) / 64] == 2)
			{

			}
			else
			{
				if (m_pFramework->GetPlayer(1)->x > 50)
				m_pFramework->GetPlayer(1)->x -= 10;
			}
			p1key = true;
			m_pFramework->GetPlayer(1)->CharacterStatus = 2;
		}
		if (keydownList[10])
		{
			if (Tileindex[m_pFramework->GetPlayer(1)->x / 64][(m_pFramework->GetPlayer(1)->y + 60) / 64] == 1)
			{
				if (m_pFramework->GetPlayer(1)->y < 6350)
				m_pFramework->GetPlayer(1)->y += 20;
				m_pFramework->GetPlayer(1)->WalkingTimerTick++;
			}
			else if (Tileindex[m_pFramework->GetPlayer(1)->x / 64][(m_pFramework->GetPlayer(1)->y + 60 + 20) / 64] == 2)
			{

			}
			else
			{
				if (m_pFramework->GetPlayer(1)->y < 6350)
				m_pFramework->GetPlayer(1)->y += 10;
			}
			p1key = true;
			m_pFramework->GetPlayer(1)->CharacterStatus = 5;
		}
		if (keydownList[9])
		{
			if (Tileindex[m_pFramework->GetPlayer(1)->x / 64][(m_pFramework->GetPlayer(1)->y + 60) / 64] == 1)
			{
				if (m_pFramework->GetPlayer(1)->x < 6350)
				m_pFramework->GetPlayer(1)->x += 20;
				m_pFramework->GetPlayer(1)->WalkingTimerTick++;
			}
			else if (Tileindex[(m_pFramework->GetPlayer(1)->x + 30) / 64][(m_pFramework->GetPlayer(1)->y + 60) / 64] == 2)
			{

			}
			else
			{
				if (m_pFramework->GetPlayer(1)->x < 6350)
				m_pFramework->GetPlayer(1)->x += 10;
			}
			p1key = true;
			m_pFramework->GetPlayer(1)->CharacterStatus = 4;
		}

		if (keydownList[11]) // p1 ��ų
		{

		}
		if (keydownList[12]) // p1 ����
		{
			switch (m_pFramework->GetPlayer(1)->CharacterStatus)
			{
			case 2:
			case 5:
			case 6:
			case 0:
				m_pFramework->GetPlayer(1)->Old_CharStat = m_pFramework->GetPlayer(1)->CharacterStatus;
				m_pFramework->GetPlayer(1)->isAttack = TRUE;
				m_pFramework->GetPlayer(1)->CharacterStatus = 6;
				//p2  �ǰ�ó�� ���⼭
				if ((m_pFramework->GetPlayer(1)->x - m_pFramework->GetPlayer(2)->x < 70) &&
					(m_pFramework->GetPlayer(1)->y - m_pFramework->GetPlayer(2)->y < 50) &&
					(m_pFramework->GetPlayer(1)->y - m_pFramework->GetPlayer(2)->y > -50))
				{
					m_pFramework->GetPlayer(2)->Old_CharStat = m_pFramework->GetPlayer(2)->CharacterStatus;
					m_pFramework->GetPlayer(2)->isAttacked = TRUE;
					m_pFramework->GetPlayer(2)->CharacterStatus = 9;
					isp2LockDown = TRUE;
					if (m_pFramework->GetPlayer(2)->iHaveCoin)
					{
						m_pFramework->GetPlayer(2)->iHaveCoin = FALSE;
						CoinObject->OnCreate(m_pFramework->GetPlayer(2)->x, m_pFramework->GetPlayer(2)->y);
						coinLockDown = TRUE;
					}
				}
				break; // �� �� ��
			case 3:
			case 4:
			case 7:
			case 1:
				m_pFramework->GetPlayer(1)->Old_CharStat = m_pFramework->GetPlayer(1)->CharacterStatus;
				m_pFramework->GetPlayer(1)->isAttack = TRUE;
				m_pFramework->GetPlayer(1)->CharacterStatus = 7;
				if ((m_pFramework->GetPlayer(2)->x - m_pFramework->GetPlayer(1)->x < 70) &&
					(m_pFramework->GetPlayer(2)->y - m_pFramework->GetPlayer(1)->y < 50) &&
					(m_pFramework->GetPlayer(2)->y - m_pFramework->GetPlayer(1)->y > -50))
				{
					m_pFramework->GetPlayer(2)->Old_CharStat = m_pFramework->GetPlayer(2)->CharacterStatus;
					m_pFramework->GetPlayer(2)->isAttacked = TRUE;
					m_pFramework->GetPlayer(2)->CharacterStatus = 8;
					isp2LockDown = TRUE;
					if (m_pFramework->GetPlayer(2)->iHaveCoin)
					{
						m_pFramework->GetPlayer(2)->iHaveCoin = FALSE;
						CoinObject->OnCreate(m_pFramework->GetPlayer(2)->x, m_pFramework->GetPlayer(2)->y);
						coinLockDown = TRUE;
					}
				}
				break; // �� �� ��
			}
		}
		if (keydownList[13]) // p1 ���
		{
			m_pFramework->GetPlayer(1)->Old_CharStat = m_pFramework->GetPlayer(1)->CharacterStatus;
			switch (m_pFramework->GetPlayer(1)->CharacterStatus)
			{
			case 2:
			case 5:
			case 0:
				m_pFramework->GetPlayer(1)->isDash = TRUE;
				m_pFramework->GetPlayer(1)->CharacterStatus = 10;
				break; // �� �� ��
			case 3:
			case 4:
			case 1:
				m_pFramework->GetPlayer(1)->isDash = TRUE;
				m_pFramework->GetPlayer(1)->CharacterStatus = 11;
				break; // �� �� ��
			}
		}
	}
	if (p1key)
	{
		m_pFramework->GetPlayer(1)->isWalk = TRUE;
		if (m_pFramework->GetPlayer(1)->WalkingTimerTick++ > 3)
		{
			m_pFramework->GetPlayer(1)->WalkingTimerTick = 0;
			m_pFramework->GetPlayer(1)->WalkingImageTick++;
		}

	}
	else
	{
		if (m_pFramework->GetPlayer(1)->isAttack != TRUE)
		{
			m_pFramework->GetPlayer(1)->isWalk = FALSE;
			switch (m_pFramework->GetPlayer(1)->CharacterStatus)
			{
			case 2:
			case 5:
			case 6:
				m_pFramework->GetPlayer(1)->CharacterStatus = 0;
				break;
			case 3:
			case 4:
			case 7:
				m_pFramework->GetPlayer(1)->CharacterStatus = 1;
				break;
			}
		}
	}
	if (p2key)
	{
		m_pFramework->GetPlayer(2)->isWalk = TRUE;
		if (m_pFramework->GetPlayer(2)->WalkingTimerTick++ > 3)
		{
			m_pFramework->GetPlayer(2)->WalkingTimerTick = 0;
			m_pFramework->GetPlayer(2)->WalkingImageTick++;
		}
	}
	else
	{
		if (m_pFramework->GetPlayer(2)->isAttack != TRUE)
		{
			m_pFramework->GetPlayer(2)->isWalk = FALSE;
			switch (m_pFramework->GetPlayer(2)->CharacterStatus)
			{
			case 2:
			case 5:
			case 6:
				m_pFramework->GetPlayer(2)->CharacterStatus = 0;
				break;
			case 3:
			case 4:
			case 7:
				m_pFramework->GetPlayer(2)->CharacterStatus = 1;
				break;
			}
		}
	}
}

void CIngameScene::Update(float fTimeElapsed)
{
	if (RemainTime <= 0)
	{
		if (m_pFramework->GetPlayer(1)->iHaveCoin == TRUE)
		{
			isGameEnd = TRUE;
			m_pFramework->GetPlayer(1)->CharacterStatus = 14;
			m_pFramework->GetPlayer(2)->CharacterStatus = 15;
		}
		else if (m_pFramework->GetPlayer(2)->iHaveCoin == TRUE)
		{
			isGameEnd = TRUE;
			m_pFramework->GetPlayer(1)->CharacterStatus = 15;
			m_pFramework->GetPlayer(2)->CharacterStatus = 14;
		}
	}
	if (isGameEnd == FALSE)
	{
		KeyState();
		CharacterState();
		CoinObject->Update(fTimeElapsed);

		TimeTick++;

		if (TimeTick >= 60)
		{
			TimeTick = 0;
			if (RemainTime > 0)
			{
				RemainTime--;
				TimerImage[0] = RemainTime / 10;
				TimerImage[1] = RemainTime % 10;
			}
		}
		if (CoinObject->GetbDraw() && coinLockDown == FALSE)
		{
			if (abs(CoinObject->x() - m_pFramework->GetPlayer(1)->x) < 30 && abs(CoinObject->y() - m_pFramework->GetPlayer(1)->y) < 30)
			{
				m_pFramework->GetPlayer(1)->iHaveCoin = TRUE;
				CoinObject->SetDrawFalse();
			}
			if (abs(CoinObject->x() - m_pFramework->GetPlayer(2)->x) < 30 && abs(CoinObject->y() - m_pFramework->GetPlayer(2)->y) < 30)
			{
				m_pFramework->GetPlayer(2)->iHaveCoin = TRUE;
				CoinObject->SetDrawFalse();
			}
		}
	}
	//for (int i = 0; i < nObjects; ++i)
		//ppObjects[i]->Update(fTimeElapsed);
}

void CIngameScene::Render(HDC hdc)
{
	keydown = FALSE;
	for (int i = 0; i < 14; i++)
	{
		keydownList[i] = FALSE;
	}
	p1key = false;
	p2key = false;

	BitBlt(*m_pFramework->GetPlayerDC(), m_pFramework->GetPlayer(1)->x - m_pFramework->p1.right / 2, m_pFramework->GetPlayer(1)->y - m_pFramework->p1.bottom / 2, m_pFramework->p1.right, m_pFramework->p1.bottom,
		*m_pFramework->GetTileDC(), m_pFramework->GetPlayer(1)->x - m_pFramework->p1.right / 2, m_pFramework->GetPlayer(1)->y - m_pFramework->p1.bottom / 2, SRCCOPY);
	BitBlt(*m_pFramework->GetPlayerDC(), m_pFramework->GetPlayer(2)->x - m_pFramework->p1.right / 2, m_pFramework->GetPlayer(2)->y - m_pFramework->p1.bottom / 2, m_pFramework->p1.right, m_pFramework->p2.bottom,
		*m_pFramework->GetTileDC(), m_pFramework->GetPlayer(2)->x - m_pFramework->p1.right / 2, m_pFramework->GetPlayer(2)->y - m_pFramework->p2.bottom / 2, SRCCOPY);

	if (m_pFramework->GetPlayer(1)->y > m_pFramework->GetPlayer(2)->y)
	{
		m_pFramework->GetPlayer(2)->Render(m_pFramework->GetPlayerDC());
		m_pFramework->GetPlayer(1)->Render(m_pFramework->GetPlayerDC());
	}
	else
	{
		m_pFramework->GetPlayer(1)->Render(m_pFramework->GetPlayerDC());
		m_pFramework->GetPlayer(2)->Render(m_pFramework->GetPlayerDC());
	}
	CoinObject->Render(&*m_pFramework->GetPlayerDC());
	Ellipse(*m_pFramework->GetPlayerDC(), m_pFramework->GetPlayer(1)->x - 5, m_pFramework->GetPlayer(1)->y - 5, m_pFramework->GetPlayer(1)->x + 5, m_pFramework->GetPlayer(1)->y + 5);
	Ellipse(*m_pFramework->GetPlayerDC(), m_pFramework->GetPlayer(2)->x - 5, m_pFramework->GetPlayer(2)->y - 5, m_pFramework->GetPlayer(2)->x + 5, m_pFramework->GetPlayer(2)->y + 5);

	BitBlt(hdc, m_pFramework->p1.left, m_pFramework->p1.top, m_pFramework->p1.right, m_pFramework->p1.bottom, *m_pFramework->GetPlayerDC(), m_pFramework->GetPlayer(1)->x - m_pFramework->p1.right / 2, m_pFramework->GetPlayer(1)->y - m_pFramework->p1.bottom / 2, SRCCOPY);
	BitBlt(hdc, m_pFramework->p2.left, m_pFramework->p2.top, m_pFramework->p1.right, m_pFramework->p2.bottom, *m_pFramework->GetPlayerDC(), m_pFramework->GetPlayer(2)->x - m_pFramework->p1.right / 2, m_pFramework->GetPlayer(2)->y - m_pFramework->p2.bottom / 2, SRCCOPY);
	
	if (isGameEnd)
	{
		if (m_pFramework->GetPlayer(1)->iHaveCoin == TRUE)
		{
			WinC.Draw(hdc, m_pFramework->p1.right / 2 - 100, m_pFramework->p1.bottom / 2 - 300, 200, 200);
			LoseC.Draw(hdc, m_pFramework->p2.right / 4 * 3 - 100, m_pFramework->p2.bottom / 2 - 300, 200, 200);
		}
		else
		{
			LoseC.Draw(hdc, m_pFramework->p1.right / 2 - 100, m_pFramework->p1.bottom / 2 - 300, 200, 200);
			WinC.Draw(hdc, m_pFramework->p2.right / 4 * 3 - 100, m_pFramework->p2.bottom / 2 - 300, 200, 200);
		}
	}

	C_IngameLine.Draw(hdc, 0, 0, windowX, windowY);
	C_Numbers[TimerImage[0]].Draw(hdc, windowX / 2 - 100, windowY / 15, 80, 80);
	C_Numbers[TimerImage[1]].Draw(hdc, windowX / 2 + 30, windowY / 15, 80, 80);

	
	for (int i = 0; i < nObjects; ++i)
		ppObjects[i]->Render(*m_pFramework->GetPlayerDC());
}


