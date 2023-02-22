#pragma once
#pragma once 
#include "DataManager.h" 
#include "array" 
#include "StateTemplate.h" 
#include "Sound.h" 
#include <Audio.h> 

/**
 * \brief This is the main game Audio Manager, controlling all sound events/calls.
 */

class AudioManager
{
public:
    /*
    //Deleted copy/assignment operators
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = default;

    //Create class and instance
    static AudioManager& Get();
    */

    AudioManager();
    ~AudioManager();

    bool init();

    // Update 
    void Update(GameData* game_data);

    //Events 
    void GetEvents(list<AfterlifeEvent>& event_list);

private:
    /*
    //Private constructor
    AudioManager() = default;
    ~AudioManager() = default;
    */
    void PlaySound(string filename);

    list<Sound*> s_sounds;
    std::unique_ptr<AudioEngine> audEngine;
};
