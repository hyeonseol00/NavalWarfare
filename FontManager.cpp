#include "DXUT.h"
#include "stdafx.h"
FontManager FontManager::singleton;

FontManager::FontManager()
{
}


FontManager::~FontManager()
{
}

void FontManager::Draw(int iSize, LPCWSTR _string, RECT rPos, UINT uiColor)
{
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	switch (iSize)
	{
	case 40:
		pFont40->DrawTextW(pSprite, _string, -1, &rPos, DT_NOCLIP, uiColor);
		break;
	case 100:
		pFont100->DrawTextW(pSprite, _string, -1, &rPos, DT_NOCLIP, uiColor);
		break;
	}

	pSprite->End();
}

void FontManager::Init()
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &pSprite);

	D3DXCreateFont(DXUTGetD3D9Device(), 40, 0, FW_NORMAL, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"HYKANB", &pFont40);
	D3DXCreateFont(DXUTGetD3D9Device(), 100, 0, FW_NORMAL, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"HYKANB", &pFont100);
}

void FontManager::Release()
{
	if (pSprite != NULL)
		pSprite->Release();

	if (pFont40 != NULL)
		pFont40->Release();

	if (pFont100 != NULL)
		pFont100->Release();
}
