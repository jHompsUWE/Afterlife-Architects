#include "pch.h"
#include "EventManager.h"


EventManager& EventManager::Get()
{
    static EventManager instance;
    return instance;
}

/**
 * \brief Can be called to manually add an Event to the Event list
 * \param _event What event will be added
 */
void EventManager::GenerateEvent(AfterlifeEvent _event)
{
    Get().IGenerateEvent(_event);
}

/**
 * \brief When called will save all the current input states
 */
void EventManager::ReadInput(GameData* game_data)
{
    Get().IReadInput(game_data);
}

/**
 * \return std::list of all the Events generated from the last frame 
 */
std::list<AfterlifeEvent>& EventManager::GetEventList()
{
    return Get().event_list;
}

// Internal Functions --------------------------------------------------------------------------------------------------

void EventManager::IGenerateEvent(AfterlifeEvent _event)
{
    event_list.push_back(_event);
}

/**
 * \brief This is where all the keyboard and mouse inputs are mapped to Events.
 */
void EventManager::IReadInput(GameData* game_data)
{
    //Input states: kb = Keyboard, ms = Mouse, kbt = Keyboard Tracker
    auto& kb = game_data->keyboard_state;
    auto& ms = game_data->mouse_state;
    auto& kbt = game_data->keyboard_state_tracker;

    //TODO: Keyboard and mouse input has to be handled HERE
    //Input mapping to events
    MapInputToEvent(kb.D0, number_0);
    MapInputToEvent(kb.D1, number_1);
    MapInputToEvent(kb.D2, number_2);
    MapInputToEvent(kb.D3, number_3);
    MapInputToEvent(kb.D4, number_4);
    MapInputToEvent(kb.D5, number_5);
    MapInputToEvent(kb.D6, number_6);
    MapInputToEvent(kb.D7, number_7);
    MapInputToEvent(kb.D8, number_8);
    MapInputToEvent(kb.D9, number_9);
    MapInputToEvent(kb.E, input_E);
    MapInputToEvent(kb.NumPad8, dialogue_1);
    MapInputToEvent(kb.G, input_G);
    MapInputToEvent(kb.H, input_H);
    MapInputToEvent(kb.J, input_J);
    MapInputToEvent(kb.P, input_P);
    MapInputToEvent(kb.R, input_R);
    MapInputToEvent(kb.NumPad1, play_sound_theme1);
    MapInputToEvent(kb.NumPad2, play_sound_theme2);

    /*
    MapInputToEvent(kb.W, input_up);
    MapInputToEvent(kb.S, input_down);
    MapInputToEvent(kb.A, input_left);
    MapInputToEvent(kb.D, input_right);

    MapInputToEvent(kb.NumPad3, play_sound_theme3);
    MapInputToEvent(kb.NumPad4, play_sound_theme4);
    MapInputToEvent(kb.NumPad5, play_sound_theme5);
    MapInputToEvent(kb.NumPad6, play_sound_theme6);
    MapInputToEvent(kb.NumPad7, play_sound_theme7);
    */

}

/**
 * \brief Uses a map to track the current state of each button pressed or released
 * \param pressed button that is being pressed
 * \param event event generated/to be generated
 */
void EventManager::MapInputToEvent(const bool& pressed, AfterlifeEvent event)
{
    if(pressed)
    {
        //If the button is pressed update the input state map and add event to list
        if(!input_state[event])
        {
            event_list.push_back(event);
            input_state[event] = true;
        }
    }
    else
    {
        //When button is not being pressed anymore set it to false
        if(input_state[event])
        {
            input_state[event] = false;
        }
    }
}
