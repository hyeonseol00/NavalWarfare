#pragma once
class BackGround
{
public:
	BackGround();
	~BackGround();

	void Init();
	void Release();
	void Update();
	void Render();
	void UIRender();

private:
	LPDIRECT3DTEXTURE9 pTex;
	D3DXVECTOR3 vPos[4][3];

	LPDIRECT3DTEXTURE9 pBoardTex;
	D3DXVECTOR3 vBoardPos[2];
	RECT rBoardRect;

	LPDIRECT3DTEXTURE9 pFogTex;
	RECT rFogRect[3];
	float fFogTimer;
	int iFogCount;

	LPDIRECT3DTEXTURE9 pUITex;
};

