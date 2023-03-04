#pragma once
#include "DataManager.h" 
#include "OldEventManager.h"
#include <unordered_map>

enum DialogueState
{
    Talking, Finished
};

enum Advisor
{
    Jasper, Aria
};

class AdvisorManager
{
public:
    AdvisorManager();
    ~AdvisorManager();

    bool init();

    // Update 
    void Update(GameData* game_data);

    //Events 
    void GetEvents(list<AfterlifeEvent>& event_list);

private:
    // Starting, updating and stopping advise
    void StopAdvise();
    void AnimationUpdate();
    void GenerateAdvise(int index);

    // Animation handling
    void IdleJasper();
    void TalkingJasper();
    void IdleAria();
    void TalkingAria();

    int GetCharIndex();

    DialogueState dia_state = Finished;
    float dia_time_tracker = 0;
    float dia_time_scale = 0.25;
    int dia_string_length = 0;
    int dia_current_index = -1;

    // String for every dialogue
    string dia_array_string[5] = {"First Dialogue","Second Dialogue","Third Dialogue","Fourth Dialogue","Fifth Dialogue"};
    // NOT POINTERS but instead directs the next dialogue index
    int dia_array_pointers[5] = { 1,2,3,4,-1 };
    // Dictates who is saying what
    Advisor dia_array_advisor[5] = { Jasper,Aria,Aria,Jasper,Aria };

    // All images for Jasper dialogue (CHARACTERS)
    string jasper_images[20] = { "JaA", "JaC", "JaE", "JaH", "JaM", "JaY" };
    // Index for what character is what image
    int jasper_img_pointers[26] = { 0 , 4 , 1 , 1 , 2 , 1 , 5 , 3 , 0 , 5 , 1 , 5 , 4 , 4 , 5 , 2 , 5 , 0 , 1 , 2 , 5 , 2 , 5 , 1 , 5 , 1 };

    // All images for Aria dialogue (CHARACTERS)
    string aria_images[20] = { "ArA", "ArE", "ArL", "ArM", "ArO", "ArS"};
    // Index for what character is what image
    int aria_img_pointers[26] = { 0 , 3 , 5 , 1 , 1 , 5 , 4 , 0 , 1 , 1 , 1 , 2 , 3 , 3 , 4 , 1 , 4 , 1 , 5 , 1 , 4 , 1 , 3 , 1 , 4 , 1 };

    int jasper_wing_timer = 150;
    int jasper_blink_timer = 60;
    int aria_tongue_timer = 120;
    int aria_blink_timer = 30;
};

