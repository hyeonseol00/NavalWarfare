#pragma once
class GaApplication
{
public:
	GaApplication();
	~GaApplication();
	static GaApplication* Instance() { return &singleton; }
	enum GameState { INTRO, MENU, STAGE };

private:
	static GaApplication singleton;

	GameState state;

	int iScore;
	int iHighScore;
	int iTurnCount;

public:
	GameState GetGameState() { return state; }
	int GetScore() { return iScore; }
	int GetHighScore() { return iHighScore; }
	int GetTurnCount() { return iTurnCount; }

	void SetGameState(GameState _state) { state = _state; }
	void PlusScore(int _score) { iScore += _score; if (iScore < 0) iScore = 0; }
	void SetHighScore() { iHighScore = iScore; }
	void PlusTurnCount() { iTurnCount++; }
	void ResetScore() { iScore = 0; iTurnCount = 1; }
};

#define GAAPP() GaApplication::Instance()