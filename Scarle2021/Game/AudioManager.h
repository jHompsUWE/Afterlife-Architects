#pragma once
#include "DataManager.h" 
#include "NewEventManager.h"
#include "Sound.h" 
#include <Audio.h> 
#include <array>
#include <random>


/**
 * \brief This is the main game Audio Manager, controlling all sound events/calls.
 */

class AudioManager : public IEventReceiver
{
public:
    AudioManager();
    ~AudioManager() override;

    bool init();
    
    // Update 
    void Update(GameData* game_data);

    //Events
    void ReceiveEvents(const AL::Event& al_event) override;

private:
    void PlaySound(string filename);
    void PlayMusic(int index);
    void ShuffleMusic();

    list<Sound*> sounds_list{};
    Sound* music{};
    std::vector<Sound*> temp_sounds{};
    std::unique_ptr<AudioEngine> audEngine{};
    std::array<int,7> music_index_array = {1,2,3,4,5,6,7};
    int current_music_index = 0;
};
