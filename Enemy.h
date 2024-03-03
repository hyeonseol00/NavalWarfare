#pragma once
class Enemy
{
public:
	Enemy();
	~Enemy();

	void Init();
	void Release();
	void ShipSetting(D3DXVECTOR3& _pos, RECT _rect, bool& _setted, bool& _horizon);
	void Fire(bool bPlayerBoard[10][10]);
	bool BoomAnimation();
	bool Distroyer(bool bEBoomBoard[10][10]);

	bool SettingUpdate();
	int TurnUpdate(bool bPlayerBoard[10][10], bool bEBoomBoard[10][10]);
	void Render();
	void FilterRender();
	void WreckRender(bool bEBoomBoard[10][10]);
	void EndingRender();

private:
	LPDIRECT3DTEXTURE9 pTex;
	D3DXVECTOR3 vPos[5];
	RECT rRect[3][2];
	bool bSetted[5];
	bool bHorizon[5];

	LPDIRECT3DTEXTURE9 pBoomTex;
	LPDIRECT3DTEXTURE9 pWaterTex;
	D3DXVECTOR3 vBoomPos;
	RECT rBoomRect[12];
	float fBoomTimer;
	int iBoomCount;
	bool bBoomVisible;
	bool bMisFire;

	float fDelay;

	LPDIRECT3DTEXTURE9 pDamageFilterTex[2];
	int iFilterCount;

	LPDIRECT3DTEXTURE9 pWreckEffectTex;
	RECT rWreckRect[12];
	float fWreckTimer;
	int iWreckCount;

	LPDIRECT3DTEXTURE9 pEndingTex;

public:
	bool bEnemyBoard[10][10];
	bool bPBoomBoard[10][10];

	bool bVisible;
};

