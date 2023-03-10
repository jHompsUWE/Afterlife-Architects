
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
    ShuffleMusic();
    PlayMusic(music_index_array[current_music_index]);
    return true;
}

/// <summary>
/// Update the manager each frame to check if audio sources need to be deleted or created
/// </summary>
/// <param name="game_data"></param>
void AudioManager::Update(GameData* game_data)
{
    GetEvents(EventManager::GetEventList());
    if (!audEngine->Update())
    {
        //more 
    }
    // If any sounds stop playing
    for (auto& s : sounds_list)
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
        sounds_list.remove(t);
    }
    temp_sounds.clear();

    // If music stops
    if (!music->GetPlayState())
    {
        // If reaches last theme
        if (current_music_index == 6)
        {
            // Shuffle themes around and play again
            current_music_index = 0;
            ShuffleMusic();
        }
        else
        {
            // Otherwise go onto next theme
            current_music_index += 1;
        }
        PlayMusic(music_index_array[current_music_index]);
    }
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
        /*case play_sound_theme1:
            PlaySound("Afterlife Theme 1");
            break;*/
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
    sounds_list.push_back(sound_eff);
}

/// <summary>
/// Generate music with given index
/// </summary>
/// <param name="filename"></param>
void AudioManager::PlayMusic(int index)
{
    string temp_str = "Afterlife Theme " + std::to_string(index);
    Sound* sound_eff = new Sound(audEngine.get(), temp_str);
    music = sound_eff;
}

/// <summary>
/// Shuffle music index array around to produce different order played
/// </summary>
void AudioManager::ShuffleMusic()
{
    int temp_index = music_index_array[6];
    do {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle(music_index_array.begin(), music_index_array.end(), std::default_random_engine(seed));
    } while (music_index_array[0] == temp_index);
}