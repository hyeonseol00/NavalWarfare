#include "DXUT.h"
#include "stdafx.h"


Menu::Menu()
{
	Init();
}


Menu::~Menu()
{
	Release();
}

void Menu::Init()
{
	state = MAIN;

	OBJMAN()->LoadData(L"Data\\Menu.png", SCR_WIDTH, SCR_HEIGHT, &pTex);

	OBJMAN()->LoadData(L"Data\\MenuButton.png", 418, 252, &pButTex);
	for (int i = 0; i < 4; i++)
	{
		vButPos[i] = { 800, 300 + (float)i * 100, 0 };
		rButRect[i] = { 0, i * 64, 418, (i + 1) * 64 };
	}

	OBJMAN()->LoadData(L"Data\\Howto.png", SCR_WIDTH, SCR_HEIGHT, &pHowtoTex);
	OBJMAN()->LoadData(L"Data\\Thisgame.png", SCR_WIDTH, SCR_HEIGHT, &pThisgameTex);
}

void Menu::Release()
{
	pTex->Release();
	pButTex->Release();
	pHowtoTex->Release();
	pThisgameTex->Release();
}

void Menu::Update()
{
	int iMessage = 4;

	for (int i = 0; i < 4; i++)
		if (OBJMAN()->Collision({ (float)INPMAN()->iXPos, (float)INPMAN()->iYPos, 0 }, NULLRECT, vButPos[i], rButRect[0]) && INPMAN()->bM1Down)
			iMessage = i;

	switch (iMessage)
	{
	case 0:
		GAAPP()->SetGameState(GaApplication::STAGE);
		SNDMAN()->PlayBGM();
		break;
	case 1:
		state = THISGAME;
		break;
	case 2:
		state = HOWTO;
		break;
	case 3:
		PostQuitMessage(0);
		break;
	}

	if (GetAsyncKeyState(VK_ESCAPE) & 0x0001 || GetAsyncKeyState(VK_RETURN) & 0x0001)
		state = MAIN;
}

void Menu::Render()
{
	switch (state)
	{
	case Menu::MAIN:
		OBJMAN()->Draw(pTex, SCRRECT, NULLPOS, ORIGINAL);
		for (int i = 0; i < 4; i++)
			OBJMAN()->Draw(pButTex, rButRect[i], vButPos[i], ORIGINAL);
		break;
	case Menu::HOWTO:
		OBJMAN()->Draw(pHowtoTex, SCRRECT, NULLPOS, ORIGINAL);
		break;
	case Menu::THISGAME:
		OBJMAN()->Draw(pThisgameTex, SCRRECT, NULLPOS, ORIGINAL);
		break;
	}
}
