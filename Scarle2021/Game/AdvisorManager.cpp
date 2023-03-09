#include "pch.h"
#include "AdvisorManager.h"
#include <iostream>

AdvisorManager::AdvisorManager()
= default;

AdvisorManager::~AdvisorManager()
{
}

/// <summary>
/// Initialise advisors with UI ref
/// </summary>
/// <returns></returns>
bool AdvisorManager::init(AdvisorWindow* adv_wind)
{
    srand(time(0));
    advisor_window = adv_wind;
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
                // Clear textbox
                advisor_window->set_text("");
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
            // FUNCTIONS WITH CURRENT EVENT SYSTEM, CHANGE TO NEW IN MERGE
            /*
        case dialogue_1:
            GenerateAdvise(0);
            RemoveFault(0);
            break;
        case play_sound_theme1:
            AddFault(0);
            break;
        case play_sound_theme2:
            AddFault(1);
            break;
            */
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
            IdleJasper();
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
    advisor_window->set_text(dia_array_string[index]);
    // CHANGE TEXT COLOUR BASED ON ARIA OR JASPER
    dia_string_length = dia_array_string[index].length();
    dia_state = Talking;
}

/// <summary>
/// Play animation for Aria based on idle sprites
/// </summary>
void AdvisorManager::IdleAria()
{
    aria_blink_timer-=1;
    aria_tongue_timer-=1;

    if (aria_blink_timer <= 0)
    {
        aria_blink_timer = 600 + (rand() % 600);
    }
    else if (aria_blink_timer <= 5)
    {
        advisor_window->set_aria_image("ArBlink3");
    }
    else if (aria_blink_timer <= 10)
    {
        advisor_window->set_aria_image("ArBlink2");
    }
    else if (aria_blink_timer <= 15)
    {
        advisor_window->set_aria_image("ArBlink1");
    }
    else if (aria_tongue_timer <= 0)
    {
        aria_tongue_timer = 1200 + (rand() % 600);
    }
    else if (aria_tongue_timer <= 10)
    {
        advisor_window->set_aria_image("ArTongue2");
    }
    else if (aria_tongue_timer <= 20)
    {
        advisor_window->set_aria_image("ArTongue3");
    }
    else if (aria_tongue_timer <= 30)
    {
        advisor_window->set_aria_image("ArTongue2");
    }
    else if (aria_tongue_timer <= 40)
    {
        advisor_window->set_aria_image("ArTongue1");
    }
    else
    {
        advisor_window->set_aria_image("ArIdle1");
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
        advisor_window->set_aria_image("ArIdle1");
    }
    else
    {
        advisor_window->set_aria_image(aria_images[aria_img_pointers[index]]);
    }
}

/// <summary>
/// Play animation for Jasper based on idle sprites
/// </summary>
void AdvisorManager::IdleJasper()
{
    jasper_blink_timer--;
    jasper_wing_timer--;
    if (jasper_blink_timer <= 0)
    {
        jasper_blink_timer = 600 + (rand() % 600);
    }
    else if (jasper_blink_timer <= 5)
    {
        advisor_window->set_jasper_image("JaBlink3");
    }
    else if (jasper_blink_timer <= 10)
    {
        advisor_window->set_jasper_image("JaBlink2");
    }
    else if (jasper_blink_timer <= 15)
    {
        advisor_window->set_jasper_image("JaBlink1");
    }
    else if (jasper_wing_timer <= 0)
    {
        jasper_wing_timer = 1200 + (rand() % 600);
    }
    else if (jasper_wing_timer <= 10)
    {
        advisor_window->set_jasper_image("JaWings1");
    }
    else if (jasper_wing_timer <= 20)
    {
        advisor_window->set_jasper_image("JaWings2");
    }
    else if (jasper_wing_timer <= 30)
    {
        advisor_window->set_jasper_image("JaWings1");
    }
    else
    {
        advisor_window->set_jasper_image("JaIdle1");
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
        advisor_window->set_jasper_image("JaIdle1");
    }
    else
    {
        advisor_window->set_jasper_image(jasper_images[jasper_img_pointers[index]]);
    }
}

/// <summary>
/// Stop and remove any current advise
/// </summary>
void AdvisorManager::StopAdvise()
{
    dia_time_tracker = 0;
    advisor_window->set_text("");
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

/// <summary>
/// Add new fault to fault list dependant on an event
/// </summary>
/// <param name="index"></param>
void AdvisorManager::AddFault(int index)
{
    // Checks if fault is already shown
    bool contains_fault = false;
    int last_point = -1;
    for (int i = 0; i < 5; i++)
    {
        if (current_faults[i] == index)
        {
            contains_fault = true;
        }
        if (current_faults[i] != -1)
        {
            last_point = i;
        }
    }

    // If fault is not already shown and there is space to show this fault
    if (!contains_fault && current_faults[4] == -1)
    {
        current_faults[last_point + 1] = index;
        UpdateButtons();
    }
}

/// <summary>
/// Remove an existing fault of the list dependant on an event
/// </summary>
/// <param name="index"></param>
void AdvisorManager::RemoveFault(int index)
{
    // Checks if fault is already shown
    bool contains_fault = false;
    int fault_point = 0;
    for (int i = 0; i < 5; i++)
    {
        if (current_faults[i] == index)
        {
            contains_fault = true;
            fault_point = i;
        }
    }

    // If fault is not already shown and there is space to show this fault
    if (contains_fault)
    {
        for (int j = fault_point; j < 4; j++)
        {
            current_faults[j] = current_faults[j + 1];
        }
        current_faults[4] = -1;
        UpdateButtons();
    }
}

/// <summary>
/// Update all option buttons after fault addition or removal
/// </summary>
void AdvisorManager::UpdateButtons()
{
    for (int i = 0; i < 5; i++)
    {
        if (current_faults[i] != -1)
        {
            advisor_window->set_option_box(i, dialogue_standpoints[current_faults[i]], dialogue_titles[current_faults[i]]);
        }
        else
        {
            advisor_window->set_option_box(i, Neither, "");
        }
    }
}