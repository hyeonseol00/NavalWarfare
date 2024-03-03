#include "DXUT.h"
#include "stdafx.h"


Stage::Stage()
{
	Init();
}


Stage::~Stage()
{
	Release();
}

void Stage::Init()
{
	state = PSETTING;

	m_bBackGround = new BackGround;
	m_pPlayer = new Player;
	m_eEnemy = new Enemy;
}

void Stage::Release()
{
	m_bBackGround->Release();
	m_pPlayer->Release();
	m_eEnemy->Release();
}

void Stage::CheatKey()
{
	if (GetAsyncKeyState(VK_F1) & 0x0001)
		m_eEnemy->bVisible = !m_eEnemy->bVisible;
}

void Stage::Update()
{
	CheatKey();

	m_bBackGround->Update();

	switch (state)
	{
	case Stage::PSETTING:
		if (m_pPlayer->SettingUpdate())
			state = ESETTING;
		break;
	case Stage::ESETTING:
		if (m_eEnemy->SettingUpdate())
			state = PTURN;
		break;
	case Stage::PTURN:
		switch (m_pPlayer->TurnUpdate(m_eEnemy->bEnemyBoard, m_eEnemy->bPBoomBoard))
		{
		case 1:
			state = ETURN;
			break;
		case 2:
			state = EENDING;
			break;
		}
		break;
	case Stage::ETURN:
		switch (m_eEnemy->TurnUpdate(m_pPlayer->bPlayerBoard, m_pPlayer->bEBoomBoard))
		{
		case 1:
			state = PTURN;
			GAAPP()->PlusScore(-1);
			GAAPP()->PlusTurnCount();
			break;
		case 2:
			state = PENDING;
			break;
		}
		break;
	case Stage::PENDING:
	case Stage::EENDING:
		if (GetAsyncKeyState(VK_RETURN) & 0x0001)
		{
			GAAPP()->ResetScore();
			OBJMAN()->Release();
			OBJMAN()->Init();
			SNDMAN()->StopBGM();
			GAAPP()->SetGameState(GaApplication::MENU);
		}
		break;
	}
}

void Stage::Render()
{
	m_bBackGround->Render();
	m_pPlayer->Render();
	m_eEnemy->Render();
	m_pPlayer->EffectRender();
	m_eEnemy->FilterRender();
	m_pPlayer->WreckRender(m_eEnemy->bPBoomBoard);
	m_eEnemy->WreckRender(m_pPlayer->bEBoomBoard);
	m_bBackGround->UIRender();

	wchar_t buf[256];
	switch (state)
	{
	case Stage::PSETTING:
		wsprintf(buf, L"플레이어 함대 배치 중");
		break;
	case Stage::ESETTING:
		wsprintf(buf, L"상대방 함대 배치 중");
		break;
	case Stage::PTURN:
		wsprintf(buf, L"%d번째 플레이어 턴 / 현재 %d점 / %dCombo! / 최고 %d점", GAAPP()->GetTurnCount(), GAAPP()->GetScore(), m_pPlayer->iCombo, GAAPP()->GetHighScore());
		break;
	case Stage::ETURN:
		wsprintf(buf, L"%d번째 상대방 턴 / 현재 %d점 / %dCombo! / 최고 %d점", GAAPP()->GetTurnCount(), GAAPP()->GetScore(), m_pPlayer->iCombo, GAAPP()->GetHighScore());
		break;
	case Stage::PENDING:
		wsprintf(buf, L"Enemy GameOver");
		break;
	case Stage::EENDING:
		wsprintf(buf, L"Player GameOver");
		break;
	}
	FONMAN()->Draw(40, buf, { 85, 20 }, 0xff000000);

	switch (state)
	{
	case Stage::PENDING:
		m_pPlayer->EndingRender();
		break;
	case Stage::EENDING:
		break;
	}
}
