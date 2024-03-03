#pragma once
class Player
{
public:
	Player();
	~Player();

	void Init();
	void Release();
	void ShipSetting(D3DXVECTOR3& _pos, RECT _rect, UINT& _color, bool& _visible, bool& _setted, bool& _horizon);
	void TurnSystem();
	void MissileSpawn();
	void MissileAnimation(bool bEnemyBoard[10][10]);
	bool BoomEffect();
	bool Distroyer(bool bPBoomBoard[10][10]);

	bool SettingUpdate();
	int TurnUpdate(bool bEnemyBoard[10][10], bool bPBoomBoard[10][10]);
	void Render();
	void EffectRender();
	void WreckRender(bool bPBoomBoard[10][10]);
	void EndingRender();

private:
	LPDIRECT3DTEXTURE9 pTex[3][2];
	LPDIRECT3DTEXTURE9 pBrokenTex[3][2];
	D3DXVECTOR3 vPos[5];
	D3DXVECTOR3 vDrawPos[5];
	RECT rRect[3][2];
	RECT rDrawRect[3][2];
	UINT uiColor[5];
	bool bVisible[5];
	bool bSetted[5];
	bool bHorizon[5];
	bool bBroken[5];

	LPDIRECT3DTEXTURE9 pPointerTex;
	D3DXVECTOR3 vPointerPos;
	RECT rPointerRect;
	UINT uiPointerColor;
	bool bPointerVisible;
	bool bPointerLock;

	LPDIRECT3DTEXTURE9 pMissileTex;
	D3DXVECTOR3 vMissilePos;
	D3DXVECTOR2 vDirectVec;
	RECT rMissileRect[8];
	int iMissileCount;
	bool bMissileVisible;

	LPDIRECT3DTEXTURE9 pBoomEffectTex;
	LPDIRECT3DTEXTURE9 pWaterEffectTex;
	D3DXVECTOR3 vBoomPos;
	RECT rBoomRect[12];
	float fBoomTimer;
	int iBoomCount;
	bool bBoomVisible;
	bool bMisFire;

	LPDIRECT3DTEXTURE9 pWreckEffectTex;
	RECT rWreckRect[12];
	float fWreckTimer;
	int iWreckCount;

	LPDIRECT3DTEXTURE9 pEndingTex;

public:
	bool bPlayerBoard[10][10];
	bool bEBoomBoard[10][10];

	int iCombo;
};

