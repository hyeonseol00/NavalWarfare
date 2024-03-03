#pragma once
class InputManager
{
public:
	InputManager();
	~InputManager();
	static InputManager* Instance() { return &singleton; }

	void GetMouseState(bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos);

private:
	static InputManager singleton;

public:
	bool bM1Down;
	bool bM2Down;
	bool bM3Down;
	bool bM4Down;
	bool bM5Down;
	int iWheelDelta;
	int iXPos;
	int iYPos;
};

#define INPMAN() InputManager::Instance()