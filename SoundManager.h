#pragma once
class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	static SoundManager* Instance() { return &singleton; }

	void Init();

private:
	static SoundManager singleton;

	CSoundManager* m_cSoundManager;
	CSound* m_cBGM;
	CSound* m_cMiss[5];
	CSound* m_cBoom[5];
	int iMissCount;
	int iBoomCount;

public:
	void PlayBGM() { m_cBGM->Play(0, DSBPLAY_LOOPING); }
	void StopBGM() { m_cBGM->Stop(); m_cBGM->Reset(); }
	void PlayMiss() { m_cMiss[iMissCount]->Play(0, NULL); if (++iMissCount >= 5) iMissCount = 0; }
	void PlayBoom() { m_cBoom[iBoomCount]->Play(0, NULL); if (++iBoomCount >= 5) iBoomCount = 0; }
};

#define SNDMAN() SoundManager::Instance()