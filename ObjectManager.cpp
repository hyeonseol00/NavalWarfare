#include "DXUT.h"
#include "stdafx.h"
ObjectManager ObjectManager::singleton;

ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}

void ObjectManager::LoadData(LPCWSTR _file, int width, int height, LPDIRECT3DTEXTURE9* pTex)
{
	D3DXCreateTextureFromFileEx(DXUTGetD3D9Device(), _file, width, height, 0, false, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT,
		D3DX_DEFAULT, D3DX_DEFAULT, NULL, NULL, NULL, pTex);
}

void ObjectManager::Draw(LPDIRECT3DTEXTURE9 pTex, RECT rRect, D3DXVECTOR3 vPos, UINT uiColor)
{
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	pSprite->Draw(pTex, &rRect, NULL, &vPos, uiColor);

	pSprite->End();
}

bool ObjectManager::Collision(D3DXVECTOR3 vPos, RECT rRect, D3DXVECTOR3 vOpponentPos, RECT rOpponentRect)
{
	if (vPos.x + rRect.left <= vOpponentPos.x + rOpponentRect.right &&
		vPos.y + rRect.top <= vOpponentPos.y + rOpponentRect.bottom &&
		vPos.x + rRect.right >= vOpponentPos.x + rOpponentRect.left &&
		vPos.y + rRect.bottom >= vOpponentPos.y + rOpponentRect.top)
		return true;

	return false;
}

void ObjectManager::Init()
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &pSprite);

	m_iIntro = new Intro;
	m_mMenu = new Menu;
	m_sStage = new Stage;
}

void ObjectManager::Release()
{
	if (pSprite != NULL)
		pSprite->Release();

	m_iIntro->Release();
	m_mMenu->Release();
	m_sStage->Release();
}

void ObjectManager::IntroUpdate() { m_iIntro->Update(); }
void ObjectManager::IntroRender() { m_iIntro->Render(); }
void ObjectManager::MenuUpdate() { m_mMenu->Update(); }
void ObjectManager::MenuRender() { m_mMenu->Render(); }
void ObjectManager::StageUpdate() { m_sStage->Update(); }
void ObjectManager::StageRender() { m_sStage->Render(); }
