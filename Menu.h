#pragma once
class Menu
{
public:
	Menu();
	~Menu();
	enum MenuState { MAIN, HOWTO, THISGAME };

	void Init();
	void Release();
	void Update();
	void Render();

private:
	MenuState state;

	LPDIRECT3DTEXTURE9 pTex;

	LPDIRECT3DTEXTURE9 pButTex;
	D3DXVECTOR3 vButPos[4];
	RECT rButRect[4];

	LPDIRECT3DTEXTURE9 pHowtoTex;
	LPDIRECT3DTEXTURE9 pThisgameTex;
};

