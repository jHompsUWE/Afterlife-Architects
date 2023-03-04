
#include "pch.h" 
#include "AudioManager.h" 
#include <iostream>

AudioManager::AudioManager()
= default;

AudioManager::~AudioManager()
{
}

/// <summary>
/// Generating Audio Engine within initialisation
/// </summary>
/// <returns></returns>
bool AudioManager::init()
{
    AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
#ifdef _DEBUG 
    eflags |= AudioEngine_Debug;
#endif 
    audEngine = std::make_unique<AudioEngine>(eflags);
    return true;
}

/// <summary>
/// Update the manager each frame to check if audio sources need to be deleted or created
/// </summary>
/// <param name="game_data"></param>
void AudioManager::Update(GameData* game_data)
{
    GetEvents(OldEventManager::GetEventList());
    if (!audEngine->Update())
    {
        //more 
    }
    for (auto& s : s_sounds)
    {
        if (!s->GetPlayState())
        {
            /// Remove sound at this point
            temp_sounds.push_back(s);
        }
    }
    for (auto& t : temp_sounds)
    {
        delete t;
        s_sounds.remove(t);
    }
    temp_sounds.clear();
}

/// <summary>
/// Get sound event from Event Manager
/// </summary>
/// <param name="event_list"></param>
void AudioManager::GetEvents(list<AfterlifeEvent>& event_list)
{
    for (auto& ev : event_list)
    {
        switch (ev)
        {
        case play_sound_theme1:
            PlaySound("Afterlife Theme 1");
            break;

        case play_sound_theme2:
            PlaySound("Afterlife Theme 2");
            break;

        case play_sound_theme3:
            PlaySound("Afterlife Theme 3");
            break;

        case play_sound_theme4:
            PlaySound("Afterlife Theme 4");
            break;

        case play_sound_theme5:
            PlaySound("Afterlife Theme 5");
            break;

        case play_sound_theme6:
            PlaySound("Afterlife Theme 6");
            break;

        case play_sound_theme7:
            PlaySound("Afterlife Theme 7");
            break;
        default:
            break;
        }
    }
}

/// <summary>
/// Generate sound with given filename
/// </summary>
/// <param name="filename"></param>
void AudioManager::PlaySound(string filename)
{
    Sound* sound_eff = new Sound(audEngine.get(), filename);
    s_sounds.push_back(sound_eff);
}