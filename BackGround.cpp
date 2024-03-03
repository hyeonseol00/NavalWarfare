#include "DXUT.h"
#include "stdafx.h"


BackGround::BackGround()
{
	Init();
}


BackGround::~BackGround()
{
	Release();
}

void BackGround::Init()
{
	OBJMAN()->LoadData(L"Data\\BackGround.png", SCR_WIDTH, SCR_HEIGHT, &pTex);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			vPos[i][j] = { -1200 + (float)j * 900, -50 + (float)i * 200, 0 };

	OBJMAN()->LoadData(L"Data\\Board.png", 600, 600, &pBoardTex);
	vBoardPos[0] = { XBLANK, YBLANK, 0 };
	vBoardPos[1] = { EXBLANK, YBLANK, 0 };
	rBoardRect = { 0, 0, 600, 600 };

	OBJMAN()->LoadData(L"Data\\Fog.png", SCR_WIDTH * 3, SCR_HEIGHT, &pFogTex);
	for (int i = 0; i < 3; i++)
		rFogRect[i] = { i * SCR_WIDTH, 0, (i + 1) * SCR_WIDTH, SCR_HEIGHT };
	fFogTimer = 0.0f;
	iFogCount = 0;

	OBJMAN()->LoadData(L"Data\\ui.png", SCR_WIDTH, SCR_HEIGHT, &pUITex);
}

void BackGround::Release()
{
	pTex->Release();
	pBoardTex->Release();
	pFogTex->Release();
	pUITex->Release();
}

void BackGround::Update()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			vPos[i][j].x += (100 + i * 100) * DXUTGetElapsedTime();

			if (vPos[i][j].x >= SCR_WIDTH)
				vPos[i][j].x = -SCR_WIDTH;
		}
	}

	fFogTimer += DXUTGetElapsedTime();
	if (fFogTimer >= 1.0f)
	{
		fFogTimer = 0;
		if (++iFogCount >= 3)
			iFogCount = 0;
	}
}

void BackGround::Render()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			OBJMAN()->Draw(pTex, SCRRECT, vPos[i][j], ORIGINAL);

	OBJMAN()->Draw(pBoardTex, rBoardRect, vBoardPos[0], GREEN);
	OBJMAN()->Draw(pFogTex, rFogRect[iFogCount], NULLPOS, ORIGINAL);
	OBJMAN()->Draw(pBoardTex, rBoardRect, vBoardPos[1], RED);
}

void BackGround::UIRender()
{
	OBJMAN()->Draw(pUITex, SCRRECT, NULLPOS, ORIGINAL);
}
