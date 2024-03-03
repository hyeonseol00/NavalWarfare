#pragma once
class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();
	static ObjectManager* Instance() { return &singleton; }
	void LoadData(LPCWSTR _file, int width, int height, LPDIRECT3DTEXTURE9* pTex);
	void Draw(LPDIRECT3DTEXTURE9 pTex, RECT rRect, D3DXVECTOR3 vPos, UINT uiColor);
	bool Collision(D3DXVECTOR3 vPos, RECT rRect, D3DXVECTOR3 vOpponentPos, RECT rOpponentRect);

	void Init();
	void Release();

	void IntroUpdate();
	void IntroRender();
	void MenuUpdate();
	void MenuRender();
	void StageUpdate();
	void StageRender();

private:
	static ObjectManager singleton;

	LPD3DXSPRITE pSprite;

	Intro* m_iIntro;
	Menu* m_mMenu;
	Stage* m_sStage;
};

#define OBJMAN() ObjectManager::Instance()