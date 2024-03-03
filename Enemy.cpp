#include "DXUT.h"
#include "stdafx.h"


Enemy::Enemy()
{
	Init();
}


Enemy::~Enemy()
{
	Release();
}

void Enemy::Init()
{
	OBJMAN()->LoadData(L"Data\\Enemy.png", ONEBLOCK, ONEBLOCK, &pTex);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 2; j++)
			rRect[i][j] = { 0, 0, ONEBLOCK + ONEBLOCK * (i + 1) * j, ONEBLOCK + ONEBLOCK * (i + 1) * !j };

	for (int i = 0; i < 5; i++)
	{
		vPos[i] = { 0, 0, 0 };
		bSetted[i] = false;
		bHorizon[i] = true;
	}
	bVisible = false;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			bEnemyBoard[i][j] = false;
			bPBoomBoard[i][j] = false;
		}
	}

	OBJMAN()->LoadData(L"Data\\BoomEffect.png", ONEBLOCK * 3 * 12, ONEBLOCK * 3, &pBoomTex);
	OBJMAN()->LoadData(L"Data\\WaterEffect.png", ONEBLOCK * 3 * 7, ONEBLOCK * 3, &pWaterTex);
	vBoomPos = NULLPOS;
	for (int i = 0; i < 12; i++)
		rBoomRect[i] = { i * ONEBLOCK * 3, 0, (i + 1) * ONEBLOCK * 3, ONEBLOCK * 3 };
	fBoomTimer = 0.0f;
	iBoomCount = 0;
	bBoomVisible = false;
	bMisFire = false;
	
	fDelay = 0.0f;

	OBJMAN()->LoadData(L"Data\\damage1.png", SCR_WIDTH, SCR_HEIGHT, &pDamageFilterTex[0]);
	OBJMAN()->LoadData(L"Data\\damage2.png", SCR_WIDTH, SCR_HEIGHT, &pDamageFilterTex[1]);
	iFilterCount = 0;

	OBJMAN()->LoadData(L"Data\\WreckEffect.png", ONEBLOCK * 12, ONEBLOCK, &pWreckEffectTex);
	for (int i = 0; i < 12; i++)
		rWreckRect[i] = { i * ONEBLOCK, 0, (i + 1) * ONEBLOCK, ONEBLOCK };
	fWreckTimer = 0.0f;
	iWreckCount = 0;

	OBJMAN()->LoadData(L"Data\\EnemyWin.png", SCR_WIDTH, SCR_HEIGHT, &pEndingTex);
}

void Enemy::Release()
{
	pTex->Release();
	pBoomTex->Release();
	pWaterTex->Release();

	for (int i = 0; i < 2; i++)
		pDamageFilterTex[i]->Release();

	pWreckEffectTex->Release();
	pEndingTex->Release();
}

void Enemy::ShipSetting(D3DXVECTOR3& _pos, RECT _rect, bool& _setted, bool& _horizon)
{
	int iHorizon = rand() % 7;
	int iVertical = rand() % 7;

	_pos.x = EXBLANK + iHorizon * ONEBLOCK;
	_pos.y = YBLANK + iVertical * ONEBLOCK;

	bool bCut = false;
	for (int i = (_pos.y - YBLANK) / ONEBLOCK; i < (_pos.y + _rect.bottom - YBLANK) / ONEBLOCK; i++)
		for (int j = (_pos.x - EXBLANK) / ONEBLOCK; j < (_pos.x + _rect.right - EXBLANK) / ONEBLOCK; j++)
			if (bEnemyBoard[i][j])
				bCut = true;

	if (bCut ||
		_pos.x < EXBLANK ||
		_pos.y < YBLANK ||
		_pos.x + _rect.right > EXBLANK + ONEBLOCK * 10 ||
		_pos.y + _rect.bottom > YBLANK + ONEBLOCK * 10);
	else
	{
		_setted = true;

		for (int i = (_pos.y - YBLANK) / ONEBLOCK; i < (_pos.y + _rect.bottom - YBLANK) / ONEBLOCK; i++)
			for (int j = (_pos.x - EXBLANK) / ONEBLOCK; j < (_pos.x + _rect.right - EXBLANK) / ONEBLOCK; j++)
				bEnemyBoard[i][j] = true;
	}
}

void Enemy::Fire(bool bPlayerBoard[10][10])
{
	if (!bBoomVisible)
	{
		int iHorizon = rand() % 10;
		int iVertical = rand() % 10;

		FireReset:
		if (bPBoomBoard[iVertical][iHorizon])
		{
			iHorizon = rand() % 10;
			iVertical = rand() % 10;
			goto FireReset;
		}

		bBoomVisible = true;
		vBoomPos.x = XBLANK + iHorizon * ONEBLOCK - ONEBLOCK;
		vBoomPos.y = YBLANK + iVertical * ONEBLOCK - ONEBLOCK;

		bPBoomBoard[iVertical][iHorizon] = true;

		if (bPlayerBoard[iVertical][iHorizon])
		{
			bMisFire = false;
			GAAPP()->PlusScore(-5);
			SNDMAN()->PlayBoom();
		}
		else
		{
			bMisFire = true;
			SNDMAN()->PlayMiss();
		}
	}
}

bool Enemy::BoomAnimation()
{
	if (bBoomVisible)
	{
		fBoomTimer += DXUTGetElapsedTime();
		if (fBoomTimer >= (bMisFire ? 0.05f : 0.02f))
		{
			fBoomTimer = 0.0f;

			if (bMisFire == false)
				iFilterCount = !iFilterCount;

			if (++iBoomCount >= (bMisFire ? 7 : 12))
			{
				iBoomCount = 0;
				bBoomVisible = false;
				return true;
			}
		}
	}

	return false;
}

bool Enemy::Distroyer(bool bEBoomBoard[10][10])
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (bEBoomBoard[i][j])
				for (int k = 0; k < 5; k++)
					if (vPos[k].x <= EXBLANK + j * ONEBLOCK &&
						vPos[k].y <= YBLANK + i * ONEBLOCK &&
						vPos[k].x + rRect[k / 2][bHorizon[k]].right > EXBLANK + j * ONEBLOCK &&
						vPos[k].y + rRect[k / 2][bHorizon[k]].bottom > YBLANK + i * ONEBLOCK)
						bSetted[k] = false;

	bool bEnding = true;
	for (int i = 0; i < 5; i++)
		if (bSetted[i] == true)
			bEnding = false;
	if (bEnding)
		return true;

	return false;

	return false;
}

bool Enemy::SettingUpdate()
{
	fDelay += DXUTGetElapsedTime();
	if (fDelay >= 3.0f)
	{
		bool bPass = true;

		for (int i = 0; i < 5; i++)
		{
			if (bSetted[i] == false)
			{
				bHorizon[i] = rand() % 2;
				ShipSetting(vPos[i], rRect[i / 2][bHorizon[i]], bSetted[i], bHorizon[i]);
				bPass = false;
				break;
			}
		}

		if (bPass)
		{
			fDelay = 0.0f;
			return true;
		}
	}

	return false;
}

int Enemy::TurnUpdate(bool bPlayerBoard[10][10], bool bEBoomBoard[10][10])
{
	fDelay += DXUTGetElapsedTime();
	if (fDelay >= 3.0f)
	{
		Fire(bPlayerBoard);
		if (BoomAnimation())
		{
			fDelay = 0.0f;
			return 1;
		}
	}
	if (Distroyer(bEBoomBoard))
		return 2;

	return 0;
}

void Enemy::Render()
{
	if (bVisible)
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				if (bEnemyBoard[i][j])
					OBJMAN()->Draw(pTex, { 0, 0, ONEBLOCK, ONEBLOCK }, { (float)EXBLANK + j * ONEBLOCK, (float)YBLANK + i * ONEBLOCK, 0 }, 0x7fffffff);

	if (bBoomVisible && bMisFire)
		OBJMAN()->Draw(pWaterTex, rBoomRect[iBoomCount], vBoomPos, ORIGINAL);
	else if (bBoomVisible)
		OBJMAN()->Draw(pBoomTex, rBoomRect[iBoomCount], vBoomPos, ORIGINAL);
}

void Enemy::FilterRender()
{
	if (bBoomVisible && !bMisFire)
		OBJMAN()->Draw(pDamageFilterTex[iFilterCount], SCRRECT, NULLPOS, 0x9fffffff);
}

void Enemy::WreckRender(bool bEBoomBoard[10][10])
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
			if (bEBoomBoard[i][j] && bEnemyBoard[i][j])
				OBJMAN()->Draw(pWreckEffectTex, rWreckRect[iWreckCount], { (float)EXBLANK + j * ONEBLOCK, (float)YBLANK + i * ONEBLOCK, 0 }, ORIGINAL);

}

void Enemy::EndingRender()
{
	OBJMAN()->Draw(pEndingTex, SCRRECT, NULLPOS, 0x7fffffff);

	wchar_t buf[256];
	wsprintf(buf, L"아군 함대 전멸,\n            플레이어 패배..\n최종점수 %d점\n최고점수 %d점\n\nEnter를 눌러 메인메뉴로", GAAPP()->GetScore(), GAAPP()->GetHighScore());
	FONMAN()->Draw(100, buf, { 100, 50 }, ORIGINAL);

	if (GAAPP()->GetScore() >= GAAPP()->GetHighScore())
	{
		wsprintf(buf, L"최고기록 갱신!");
		FONMAN()->Draw(100, buf, { 100, 450 }, ORIGINAL);
		GAAPP()->SetHighScore();
	}
}
