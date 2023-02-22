
#include "pch.h" 
#include "AudioManager.h" 

/*
AudioManager& AudioManager::Get()
{
    static AudioManager instance;
    return instance;
}
*/

AudioManager::AudioManager()
= default;

AudioManager::~AudioManager()
{
}

bool AudioManager::init()
{
    AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
#ifdef _DEBUG 
    eflags |= AudioEngine_Debug;
#endif 
    audEngine = std::make_unique<AudioEngine>(eflags);
    return true;
}

void AudioManager::Update(GameData* game_data)
{
    GetEvents(EventManager::GetEventList());
    if (!audEngine->Update())
    {
        //more 
    }
}

void AudioManager::GetEvents(list<AfterlifeEvent>& event_list)
{
    for (auto& ev : event_list)
    {
        switch (ev)
        {
        case play_sound_1:
            PlaySound("Afterlife Theme 1");
            break;

        case play_sound_2:
            PlaySound("Demolish3");
            break;

        case play_sound_3:
            PlaySound("InstituteHeaven");
            break;

        case play_sound_4:
            PlaySound("Port");
            break;

        default:
            break;
        }
        std::cout << ev << " soos" << std::endl;
    }
}

void AudioManager::PlaySound(string filename)
{
    Sound* sound_eff = new Sound(audEngine.get(), filename);
    //s_sounds.push_back(sound_eff);
}