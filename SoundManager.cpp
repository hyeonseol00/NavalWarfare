#include "DXUT.h"
#include "stdafx.h"
SoundManager SoundManager::singleton;

SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
}

void SoundManager::Init()
{
	m_cSoundManager = new CSoundManager;

	m_cSoundManager->Initialize(DXUTGetHWND(), DSSCL_PRIORITY);
	m_cSoundManager->SetPrimaryBufferFormat(2, 22050, 16);

	m_cSoundManager->Create(&m_cBGM, L"Data\\Techno_1.wav", NULL, GUID_NULL);
	for (int i = 0; i < 5; i++)
	{
		m_cSoundManager->Create(&m_cMiss[i], L"Data\\zap.wav", NULL, GUID_NULL);
		m_cSoundManager->Create(&m_cBoom[i], L"Data\\droid_destroyed3.wav", NULL, GUID_NULL);
	}
	iMissCount = 0;
	iBoomCount = 0;
}
