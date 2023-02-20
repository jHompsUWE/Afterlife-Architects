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
    MapInputToEvent(kb.W, input_up);
    MapInputToEvent(kb.S, input_down);
    MapInputToEvent(kb.A, input_left);
    MapInputToEvent(kb.D, input_right);
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
