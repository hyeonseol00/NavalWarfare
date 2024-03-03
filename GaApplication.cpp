#include "DXUT.h"
#include "stdafx.h"
GaApplication GaApplication::singleton;

GaApplication::GaApplication()
{
	state = MENU;

	iScore = 0;
	iHighScore = 0;
	iTurnCount = 1;
}


GaApplication::~GaApplication()
{
}
