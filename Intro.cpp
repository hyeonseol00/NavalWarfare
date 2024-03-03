#include "DXUT.h"
#include "stdafx.h"


Intro::Intro()
{
	Init();
}


Intro::~Intro()
{
	Release();
}

void Intro::Init()
{
	OBJMAN()->LoadData(L"Data\\Intro.png", SCR_WIDTH, SCR_HEIGHT, &pTex);
	fTimer = 0.0f;
}

void Intro::Release()
{
	pTex->Release();
}

void Intro::Update()
{
	fTimer += DXUTGetElapsedTime();
	if (fTimer >= 3.0f)
	{
		fTimer = 0;
		GAAPP()->SetGameState(GaApplication::MENU);
	}
}

void Intro::Render()
{
	OBJMAN()->Draw(pTex, SCRRECT, NULLPOS, ORIGINAL);
}
