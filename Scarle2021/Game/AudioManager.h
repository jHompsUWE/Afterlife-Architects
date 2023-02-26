#pragma once
#include "DataManager.h" 
#include "StateTemplate.h" 
#include "Sound.h" 
#include <Audio.h> 

/**
 * \brief This is the main game Audio Manager, controlling all sound events/calls.
 */

class AudioManager
{
public:
    AudioManager();
    ~AudioManager();

    bool init();

    // Update 
    void Update(GameData* game_data);

    //Events 
    void GetEvents(list<AfterlifeEvent>& event_list);

private:
    void PlaySound(string filename);

    list<Sound*> s_sounds;
    std::vector<Sound*> temp_sounds;
    std::unique_ptr<AudioEngine> audEngine;
};
