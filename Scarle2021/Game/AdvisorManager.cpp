#include "pch.h"
#include "AdvisorManager.h"
#include <iostream>

AdvisorManager::AdvisorManager()
= default;

AdvisorManager::~AdvisorManager()
{
}

/// <summary>
/// Initialise advisors UI
/// </summary>
/// <returns></returns>
bool AdvisorManager::init()
{
    srand(time(0));
    // WILL GET ASSISTANCE FOR UI GENERATION 27th MONDAY
    // Generate Back Window
    
    // Generate Aria Img
    
    // Generate Jasper Img
    
    // Generate Option Buttons
    
    // Generate Exit Button
    
    // Generate Dialogue Box
    return 0;
}

/// <summary>
/// Update the manager each frame to check if advise needs to be displayed or updated
/// </summary>
/// <param name="game_data"></param>
void AdvisorManager::Update(GameData* game_data)
{
    // Check for events
    GetEvents(EventManager::GetEventList());

    if (dia_state == Talking)
    {
        // Code for update whilst talking
        if (dia_time_tracker >= dia_time_scale * dia_string_length)
        {
            // If dialogue should end after timer
            if (dia_array_pointers[dia_current_index] != -1)
            {
                // If there is more dialogue to be displayed
                GenerateAdvise(dia_array_pointers[dia_current_index]);
            }
            else
            {
                // If not more dialogue is after
                dia_state = Finished;
                // CHANGE TEXTBOX TO BLANK
            }
        }
        else
        {
            // If dialogue is still going
            dia_time_tracker += game_data->delta_time;
        }
    }

    AnimationUpdate();
}

/// <summary>
/// Get advise event from Event Manager
/// </summary>
/// <param name="event_list"></param>
void AdvisorManager::GetEvents(list<AfterlifeEvent>& event_list)
{
    for (auto& ev : event_list)
    {
        switch (ev)
        {
        case dialogue_1:
            GenerateAdvise(0);
            break;

        default:
            break;
        }
    }
}

/// <summary>
/// Update both Aria and Jasper images to animate them
/// </summary>
void AdvisorManager::AnimationUpdate()
{
    if (dia_state == Talking)
    {
        // If Jasper is talking
        if (dia_array_advisor[dia_current_index] == Jasper)
        {
            // Update img based on char for Jasper
            TalkingJasper();
            // Update img idle for Aria
            IdleAria();
        }
        // If Aria is talking
        else
        {
            // Update img based on char for Aria
            TalkingAria();
            // Update img idle for Jasper
            TalkingJasper();
        }
    }
    else
    {
        // If neither are talking

        // Update img idle for Aria
        IdleAria();
        // Update img idle for Jasper
        IdleJasper();
    }
}

/// <summary>
/// Start the advise of a certain index
/// </summary>
/// <param name="index"></param>
void AdvisorManager::GenerateAdvise(int index)
{
    dia_time_tracker = 0;
    dia_current_index = index;
    // CHANGE TEXT BOX TO dia_array_string[index];
    // CHANGE TEXT COLOUR BASED ON ARIA OR JASPER
    dia_string_length = dia_array_string[index].length();
    dia_state = Talking;
}

/// <summary>
/// Play animation for Aria based on idle sprites
/// </summary>
void AdvisorManager::IdleAria()
{
    aria_blink_timer--;
    aria_tongue_timer--;
    if (aria_blink_timer == 2)
    {
        // CHANGE IMAGE BOX TO BLINK 1
    }
    else if (aria_blink_timer == 1)
    {
        // CHANGE IMAGE BOX TO BLINK 2
    }
    else if (aria_blink_timer <= 0)
    {
        // CHANGE IMAGE BOX TO BLINK 3
        aria_blink_timer = 120 + (rand() % 120);
    }
    else if (aria_tongue_timer == 2)
    {
        // CHANGE IMAGE BOX TO TONGUE 1
    }
    else if (aria_tongue_timer == 1)
    {
        // CHANGE IMAGE BOX TO TONGUE 2
    }
    else if (aria_tongue_timer <= 0)
    {
        // CHANGE IMAGE BOX TO TONGUE 3
        aria_tongue_timer = 240 + (rand() % 120);
    }
    else
    {
        // CHANGE IMAGE BOX TO IDLE 1
    }
}

/// <summary>
/// Play animation for Aria based on talking sprites
/// </summary>
void AdvisorManager::TalkingAria()
{
    // Get position of character (at current time in dialogue) in the alphabet
    int index = GetCharIndex();
    if (index < 0)
    {
        // CHANGE IMAGE BOX TO IDLE 1
    }
    else
    {
        // CHANGE IMAGE BOX TO aria_images[aria_img_pointers[index]];
    }
}

/// <summary>
/// Play animation for Jasper based on idle sprites
/// </summary>
void AdvisorManager::IdleJasper()
{
    jasper_blink_timer--;
    jasper_wing_timer--;
    if (jasper_blink_timer == 2)
    {
        // CHANGE IMAGE BOX TO BLINK 1
    }
    else if (jasper_blink_timer == 1)
    {
        // CHANGE IMAGE BOX TO BLINK 2
    }
    else if (jasper_blink_timer <= 0)
    {
        // CHANGE IMAGE BOX TO BLINK 3
        jasper_blink_timer = 120 + (rand() % 120);
    }
    else if (jasper_wing_timer == 2)
    {
        // CHANGE IMAGE BOX TO WING 1
    }
    else if (jasper_wing_timer == 1)
    {
        // CHANGE IMAGE BOX TO WING 2
    }
    else if (jasper_wing_timer <= 0)
    {
        // CHANGE IMAGE BOX TO WING 1
        jasper_wing_timer = 240 + (rand() % 120);
    }
    else
    {
        // CHANGE IMAGE BOX TO IDLE 1
    }
}

/// <summary>
/// Play animation for Jasper based on speaking sprites
/// </summary>
void AdvisorManager::TalkingJasper()
{
    // Get position of character (at current time in dialogue) in the alphabet
    int index = GetCharIndex();
    if (index < 0)
    {
        // CHANGE IMAGE BOX TO IDLE 1
    }
    else
    {
        // CHANGE IMAGE BOX TO jasper_images[jasper_img_pointers[index]];
    }
}

/// <summary>
/// Stop and remove any current advise
/// </summary>
void AdvisorManager::StopAdvise()
{
    dia_time_tracker = 0;
    // CHANGE TEXT BOX TO BLANK
    dia_state = Finished;
}

/// <summary>
/// Get position of character in the alphabet
/// </summary>
/// <returns></returns>
int AdvisorManager::GetCharIndex()
{
    int int_temp = (int)(dia_time_tracker / dia_time_scale);
    char char_temp = dia_array_string[dia_current_index][int_temp];
    // If space return -1 for idle sprite
    if (char_temp == ' ')
    {
        return -1;
    }
    char_temp = toupper(char_temp);
    int_temp = (int)char_temp - 65;
    return int_temp;
}