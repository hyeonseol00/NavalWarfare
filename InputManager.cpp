#include "DXUT.h"
#include "stdafx.h"
InputManager InputManager::singleton;

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::GetMouseState(bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos)
{
	bM1Down = bLeftButtonDown;
	bM2Down = bRightButtonDown;
	bM3Down = bMiddleButtonDown;
	bM4Down = bSideButton1Down;
	bM5Down = bSideButton2Down;
	iWheelDelta = nMouseWheelDelta;
	iXPos = xPos;
	iYPos = yPos;
}
