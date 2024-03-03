#pragma once
class Stage
{
public:
	Stage();
	~Stage();
	enum StageState { PSETTING, ESETTING, PTURN, ETURN, PENDING, EENDING };

	void Init();
	void Release();
	void Update();
	void Render();

	void CheatKey();

private:
	StageState state;

	BackGround* m_bBackGround;
	Player* m_pPlayer;
	Enemy* m_eEnemy;
};

