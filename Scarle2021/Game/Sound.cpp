#include "pch.h"
#include "Sound.h"
#include <iostream>

Sound::Sound(AudioEngine* _audEngine, string _filename)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	string fullpath = "../Sounds/" + _filename + ".wav";
	std::wstring wFilename = converter.from_bytes(fullpath.c_str());

	m_sfx = std::make_unique<SoundEffect>(_audEngine, wFilename.c_str());
	if (m_sfx)
	{
		m_sfx->Play(m_volume, m_pitch, m_pan);
	}
}
void SetVolume(float _vol) 
{ 
	//float _vol = 1.0f;
	//m_volume = _vol; 
}

Sound::~Sound()
{
	m_sfx.reset();
}

bool Sound::GetPlayState()
{
	return m_sfx->IsInUse();
}
