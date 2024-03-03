#include "DXUT.h"
#include "stdafx.h"


Player::Player()
{
	Init();
}


Player::~Player()
{
	Release();
}

void Player::Init()
{
	OBJMAN()->LoadData(L"Data\\2tiership Vertical.png", ONEBLOCK, ONEBLOCK * 2, &pTex[0][0]);
	OBJMAN()->LoadData(L"Data\\2tiership Horizon.png", ONEBLOCK * 2, 68, &pTex[0][1]);
	OBJMAN()->LoadData(L"Data\\3tiership Vertical.png", ONEBLOCK, ONEBLOCK * 3, &pTex[1][0]);
	OBJMAN()->LoadData(L"Data\\3tiership Horizon.png", ONEBLOCK * 3, 87, &pTex[1][1]);
	OBJMAN()->LoadData(L"Data\\4tiership Vertical.png", ONEBLOCK, ONEBLOCK * 4, &pTex[2][0]);
	OBJMAN()->LoadData(L"Data\\4tiership Horizon.png", ONEBLOCK * 4, 110, &pTex[2][1]);

	OBJMAN()->LoadData(L"Data\\broken 2tiership Vertical.png", ONEBLOCK, ONEBLOCK * 2, &pBrokenTex[0][0]);
	OBJMAN()->LoadData(L"Data\\broken 2tiership Horizon.png", ONEBLOCK * 2, 68, &pBrokenTex[0][1]);
	OBJMAN()->LoadData(L"Data\\broken 3tiership Vertical.png", ONEBLOCK, ONEBLOCK * 3, &pBrokenTex[1][0]);
	OBJMAN()->LoadData(L"Data\\broken 3tiership Horizon.png", ONEBLOCK * 3, 87, &pBrokenTex[1][1]);
	OBJMAN()->LoadData(L"Data\\broken 4tiership Vertical.png", ONEBLOCK, ONEBLOCK * 4, &pBrokenTex[2][0]);
	OBJMAN()->LoadData(L"Data\\broken 4tiership Horizon.png", ONEBLOCK * 4, 110, &pBrokenTex[2][1]);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			rRect[i][j] = { 0, 0, ONEBLOCK + ONEBLOCK * (i + 1) * j, ONEBLOCK + ONEBLOCK * (i + 1) * !j };
			rDrawRect[i][j] = rRect[i][j];
		}
	}
	rDrawRect[0][1] = { 0, 0, 120, 68 };
	rDrawRect[1][1] = { 0, 0, 180, 87 };
	rDrawRect[2][1] = { 0, 0, 240, 110 };

	for (int i = 0; i < 5; i++)
	{
		vPos[i] = { 0, 0, 0 };
		vDrawPos[i] = { 0, 0, 0 };
		uiColor[i] = ORIGINAL;
		bVisible[i] = false;
		bSetted[i] = false;
		bHorizon[i] = true;
		bBroken[i] = false;
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			bPlayerBoard[i][j] = false;
			bEBoomBoard[i][j] = false;
		}
	}

	OBJMAN()->LoadData(L"Data\\Pointer.png", ONEBLOCK, ONEBLOCK, &pPointerTex);
	vPointerPos = NULLPOS;
	uiPointerColor = ORIGINAL;
	rPointerRect = { 0, 0, ONEBLOCK, ONEBLOCK };
	bPointerVisible = false;
	bPointerLock = false;

	OBJMAN()->LoadData(L"Data\\Missile.png", 3520, 35, &pMissileTex);
	vMissilePos = NULLPOS;
	vDirectVec = { 0, 0 };
	for (int i = 0; i < 8; i++)
		rMissileRect[i] = { i * 440, 0, (i + 1) * 440, 35 };
	iMissileCount = 0;
	bMissileVisible = false;

	OBJMAN()->LoadData(L"Data\\BoomEffect.png", ONEBLOCK * 3 * 12, ONEBLOCK * 3, &pBoomEffectTex);
	OBJMAN()->LoadData(L"Data\\WaterEffect.png", ONEBLOCK * 3 * 7, ONEBLOCK * 3, &pWaterEffectTex);
	vBoomPos = NULLPOS;
	for (int i = 0; i < 12; i++)
		rBoomRect[i] = { i * ONEBLOCK * 3, 0, (i + 1) * ONEBLOCK * 3, ONEBLOCK * 3 };
	fBoomTimer = 0.0f;
	iBoomCount = 0;
	bBoomVisible = false;
	bMisFire = true;

	iCombo = 0;

	OBJMAN()->LoadData(L"Data\\WreckEffect.png", ONEBLOCK * 12, ONEBLOCK, &pWreckEffectTex);
	for (int i = 0; i < 12; i++)
		rWreckRect[i] = { i * ONEBLOCK, 0, (i + 1) * ONEBLOCK, ONEBLOCK };
	fWreckTimer = 0.0f;
	iWreckCount = 0;

	OBJMAN()->LoadData(L"Data\\PlayerWin.png", SCR_WIDTH, SCR_HEIGHT, &pEndingTex);
}

void Player::Release()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			pTex[i][j]->Release();
			pBrokenTex[i][j]->Release();
		}
	}

	pPointerTex->Release();
	pMissileTex->Release();

	pBoomEffectTex->Release();
	pWaterEffectTex->Release();
	pWreckEffectTex->Release();

	pEndingTex->Release();
}

void Player::ShipSetting(D3DXVECTOR3& _pos, RECT _rect, UINT& _color, bool& _visible, bool& _setted, bool& _horizon)
{
	_visible = true;

	_pos.x = ((INPMAN()->iXPos + ONEBLOCK) - (XBLANK - XBLANK / ONEBLOCK * ONEBLOCK))
		/ ONEBLOCK * ONEBLOCK + (XBLANK - XBLANK / ONEBLOCK * ONEBLOCK) - ONEBLOCK;
	_pos.y = ((INPMAN()->iYPos + ONEBLOCK) - (YBLANK - YBLANK / ONEBLOCK * ONEBLOCK))
		/ ONEBLOCK * ONEBLOCK + (YBLANK - YBLANK / ONEBLOCK * ONEBLOCK) - ONEBLOCK;

	bool bCut = false;
	for (int i = (_pos.y - YBLANK)/ ONEBLOCK; i < (_pos.y + _rect.bottom - YBLANK) / ONEBLOCK; i++)
		for (int j = (_pos.x - XBLANK) / ONEBLOCK; j < (_pos.x + _rect.right - XBLANK) / ONEBLOCK; j++)
			if (bPlayerBoard[i][j])
				bCut = true;


	_color = GREEN;
	if (bCut ||
		_pos.x < XBLANK ||
		_pos.y < YBLANK ||
		_pos.x + _rect.right > XBLANK + ONEBLOCK * 10 ||
		_pos.y + _rect.bottom > YBLANK + ONEBLOCK * 10)
		_color = RED;
	else if (INPMAN()->bM1Down)
	{
		_color = ORIGINAL;
		_setted = true;

		for (int i = (_pos.y - YBLANK) / ONEBLOCK; i < (_pos.y + _rect.bottom - YBLANK) / ONEBLOCK; i++)
			for (int j = (_pos.x - XBLANK) / ONEBLOCK; j < (_pos.x + _rect.right - XBLANK) / ONEBLOCK; j++)
				bPlayerBoard[i][j] = true;
	}

	if (GetAsyncKeyState('R') & 0x0001)
		_horizon = !_horizon;
}

void Player::TurnSystem()
{
	if (!bPointerLock)
	{
		bPointerVisible = true;

		vPointerPos.x = ((INPMAN()->iXPos + ONEBLOCK) - (EXBLANK - EXBLANK / ONEBLOCK * ONEBLOCK))
			/ ONEBLOCK * ONEBLOCK + (EXBLANK - EXBLANK / ONEBLOCK * ONEBLOCK) - ONEBLOCK;
		vPointerPos.y = ((INPMAN()->iYPos + ONEBLOCK) - (YBLANK - YBLANK / ONEBLOCK * ONEBLOCK))
			/ ONEBLOCK * ONEBLOCK + (YBLANK - YBLANK / ONEBLOCK * ONEBLOCK) - ONEBLOCK;
	}

	uiPointerColor = ORIGINAL;
	if (bEBoomBoard[int(vPointerPos.y - YBLANK) / ONEBLOCK][int(vPointerPos.x - EXBLANK) / ONEBLOCK])
		uiPointerColor = 0xffff0000;
	else if (vPointerPos.x < EXBLANK ||
		vPointerPos.y < YBLANK ||
		vPointerPos.x + rPointerRect.right > EXBLANK + ONEBLOCK * 10 ||
		vPointerPos.y + rPointerRect.bottom > YBLANK + ONEBLOCK * 10)
		bPointerVisible = false;
	else if (INPMAN()->bM1Down && !bMissileVisible)
	{
		MissileSpawn();
	}
}

void Player::MissileSpawn()
{
	bMissileVisible = true;
	bPointerLock = true;

	int iRand = rand() % 5;
	MissileReset:
	if (bSetted[iRand] == false)
	{
		iRand = rand() % 5;
		goto MissileReset;
	}

	vMissilePos.x = vPos[iRand].x - rMissileRect[0].right / 2;
	vMissilePos.y = vPos[iRand].y + rRect[iRand / 2][bHorizon[iRand]].bottom / 2 - rMissileRect[0].bottom / 2;

	vDirectVec.x = (vMissilePos.x + rMissileRect[0].right - ONEBLOCK / 2) - vPointerPos.x;
	vDirectVec.y = (vMissilePos.y + rMissileRect[0].bottom / 2 - ONEBLOCK / 2) - vPointerPos.y;
	D3DXVec2Normalize(&vDirectVec, &vDirectVec);
	vDirectVec = -vDirectVec;
}

void Player::MissileAnimation(bool bEnemyBoard[10][10])
{
	if (bMissileVisible)
	{
		vMissilePos.x += 1500 * vDirectVec.x * DXUTGetElapsedTime();
		vMissilePos.y += 1500 * vDirectVec.y * DXUTGetElapsedTime();

		if (++iMissileCount >= 8)
			iMissileCount = 0;

		if (vMissilePos.x + rMissileRect[0].right >= vPointerPos.x + ONEBLOCK / 2)
		{
			bMissileVisible = false;
			bPointerVisible = false;
			bBoomVisible = true;

			bEBoomBoard[int(vPointerPos.y - YBLANK) / ONEBLOCK][int(vPointerPos.x - EXBLANK) / ONEBLOCK] = true;

			if (bEnemyBoard[int(vPointerPos.y - YBLANK) / ONEBLOCK][int(vPointerPos.x - EXBLANK) / ONEBLOCK])
			{
				bMisFire = false;
				GAAPP()->PlusScore(100 + iCombo * 50);
				iCombo++;
				SNDMAN()->PlayBoom();
			}
			else
			{
				bMisFire = true;
				iCombo = 0;
				SNDMAN()->PlayMiss();
			}
		}
	}
}

bool Player::BoomEffect()
{
	if (bBoomVisible)
	{
		vBoomPos.x = vPointerPos.x - ONEBLOCK;
		vBoomPos.y = vPointerPos.y - ONEBLOCK;

		fBoomTimer += DXUTGetElapsedTime();
		if (fBoomTimer >= (bMisFire ? 0.05f : 0.02f))
		{
			fBoomTimer = 0.0f;

			if (++iBoomCount >= (bMisFire ? 7 : 12))
			{
				iBoomCount = 0;
				bBoomVisible = false;
				bPointerLock = false;
				return true;
			}
		}
	}

	return false;
}

bool Player::Distroyer(bool bPBoomBoard[10][10])
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (bPBoomBoard[i][j])
				for (int k = 0; k < 5; k++)
					if (vPos[k].x <= XBLANK + j * ONEBLOCK &&
						vPos[k].y <= YBLANK + i * ONEBLOCK &&
						vPos[k].x + rRect[k / 2][bHorizon[k]].right > XBLANK + j * ONEBLOCK &&
						vPos[k].y + rRect[k / 2][bHorizon[k]].bottom > YBLANK + i * ONEBLOCK)
						bBroken[k] = true;

	bool bEnding = true;
	for (int i = 0; i < 5; i++)
		if (bBroken[i] == false)
			bEnding = false;
	if (bEnding)
		return true;

	return false;
}

bool Player::SettingUpdate()
{
	bool bPass = true;

	for (int i = 0; i < 5; i++)
	{
		if (bSetted[i] == false)
		{
			ShipSetting(vPos[i], rRect[i / 2][bHorizon[i]], uiColor[i], bVisible[i], bSetted[i], bHorizon[i]);
			vDrawPos[i] = vPos[i];

			if (bHorizon[i])
				vDrawPos[i].y -= i / 2 * 10;

			bPass = false;
			break;
		}
	}

	if (bPass)
		return true;
	else
		return false;
}

int Player::TurnUpdate(bool bEnemyBoard[10][10], bool bPBoomBoard[10][10])
{
	TurnSystem();
	MissileAnimation(bEnemyBoard);
	if (BoomEffect())
		return 1;
	if (Distroyer(bPBoomBoard))
		return 2;

	return 0;
}

void Player::Render()
{
	for (int i = 0; i < 5; i++)
	{
		if (bVisible[i])
		{
			if (!bBroken[i])
				OBJMAN()->Draw(pTex[i / 2][bHorizon[i]], rDrawRect[i / 2][bHorizon[i]], vDrawPos[i], uiColor[i]);
			else
				OBJMAN()->Draw(pBrokenTex[i / 2][bHorizon[i]], rDrawRect[i / 2][bHorizon[i]], vDrawPos[i], uiColor[i]);
		}
	}
}

void Player::EffectRender()
{
	if (bPointerVisible)
		OBJMAN()->Draw(pPointerTex, rPointerRect, vPointerPos, uiPointerColor);

	if (bMissileVisible)
		OBJMAN()->Draw(pMissileTex, rMissileRect[iMissileCount], vMissilePos, ORIGINAL);

	if (bBoomVisible && bMisFire)
		OBJMAN()->Draw(pWaterEffectTex, rBoomRect[iBoomCount], vBoomPos, ORIGINAL);
	else if (bBoomVisible)
		OBJMAN()->Draw(pBoomEffectTex, rBoomRect[iBoomCount], vBoomPos, ORIGINAL);
}

void Player::WreckRender(bool bPBoomBoard[10][10])
{
	fWreckTimer += DXUTGetElapsedTime();
	if (fWreckTimer >= 0.03f)
	{
		fWreckTimer = 0;
		if (++iWreckCount >= 12)
			iWreckCount = 0;
	}

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (bPBoomBoard[i][j] && bPlayerBoard[i][j])
				OBJMAN()->Draw(pWreckEffectTex, rWreckRect[iWreckCount], { (float)XBLANK + j * ONEBLOCK, (float)YBLANK + i * ONEBLOCK, 0 }, ORIGINAL);
}

void Player::EndingRender()
{
	OBJMAN()->Draw(pEndingTex, SCRRECT, NULLPOS, 0x7fffffff);

	wchar_t buf[256];
	wsprintf(buf, L"적 함대 전멸,\n            플레이어 승리!\n최종점수 %d점\n최고점수 %d점\n\nEnter를 눌러 메인메뉴로", GAAPP()->GetScore(), GAAPP()->GetHighScore());
	FONMAN()->Draw(100, buf, { 100, 50 }, ORIGINAL);

	if (GAAPP()->GetScore() >= GAAPP()->GetHighScore())
	{
		wsprintf(buf, L"최고기록 갱신!");
		FONMAN()->Draw(100, buf, { 100, 450 }, ORIGINAL);
		GAAPP()->SetHighScore();
	}
}
