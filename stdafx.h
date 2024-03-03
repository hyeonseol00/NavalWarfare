#pragma once
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#define SCR_WIDTH 1280
#define SCR_HEIGHT 720

#define NULLPOS D3DXVECTOR3{0, 0, 0}
#define NULLRECT RECT{0, 0, 0, 0}
#define SCRRECT RECT{0, 0, SCR_WIDTH, SCR_HEIGHT}

#define ORIGINAL 0xffffffff
#define RED 0xffff7f7f
#define GREEN 0xff7fff7f
#define BLUE 0xff7f7fff

#define ONEBLOCK 60
#define XBLANK 20
#define YBLANK 100
#define EXBLANK 660

#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <math.h>

#include "SDKsound.h"

//		Custom Header		//
#include "GaApplication.h"
#include "InputManager.h"
#include "FontManager.h"
#include "SoundManager.h"

	#include "Intro.h"
	#include "Menu.h"

		#include "BackGround.h"
		#include "Player.h"
		#include "Enemy.h"
	#include "Stage.h"
#include "ObjectManager.h"