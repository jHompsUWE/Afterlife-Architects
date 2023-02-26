#include "pch.h"
#include "Sound.h"

Sound::Sound(AudioEngine* _audEngine, std::string _filename)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::string fullpath = "../Sounds/" + _filename + ".wav";
	std::wstring wFilename = converter.from_bytes(fullpath.c_str());

	m_sfx = std::make_unique<SoundEffect>(_audEngine, wFilename.c_str());
	if (m_sfx)
	{
		m_sfx->Play(m_volume, m_pitch, m_pan);
	}
}

Sound::~Sound()
{
	m_sfx.reset();
}

bool Sound::GetPlayState() const
{
	return m_sfx->IsInUse();
}
