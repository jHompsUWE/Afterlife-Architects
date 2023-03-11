#include "pch.h"
#include "FSM.h"

#include "GameOver.h"
#include "GamePlay.h"
#include "LevelSelect.h"
#include "MainMenu.h"

FSM::FSM(GameState& _current_state) : current_state(_current_state)
{
    //Allocate a state to each slot of the state array
    state_array[gs_main_menu] = std::make_unique<MainMenu>();
    state_array[gs_level_select] = std::make_unique<LevelSelect>();
    state_array[gs_gameplay] = std::make_unique<GamePlay>();
    state_array[gs_game_over] = std::make_unique<GameOver>();
}

bool FSM::init()
{
    //Runs each state and its init function
    for (auto& state : state_array)
    {
        //If init fails return false
        if(!state->init())
        {
            std::cout << typeid(state).name() << " Failed Initialization" << std::endl;
            return false;
        }
    }
    return true;
}

//Update ---------------------------------------------------------------------------------------------------------------

/**
 * \brief Main part of the game loop, update is divided in different sections
 *
 * Get Events: Event queue will be provided here, containing all the events generated in the last frame
 * Update: Normal Update
 * Scaled Update: Delta time multiplied by scale value
 * Late Update: Last update function called before rendering
 * 
 * \param game_data game_data pointer
 */
void FSM::Update(GameData* game_data)
{
    //Update
    state_array[current_state]->Update(game_data);

    //If we're not in gameplay, we do not need Scaled Update.
    if(current_state == gs_gameplay)
    {
        if(game_data->time_scale_factor > 0)
        {
            //Scales the delta time accordingly with the time scale factor
            //TODO: Economy and time related stuff have to be inside scaled update
            float scaled_dt = game_data->delta_time * game_data->time_scale_factor;
            state_array[current_state]->ScaledUpdate(game_data, scaled_dt);
        }
    }

    //Runs this for last
    state_array[current_state]->LateUpdate(game_data);

    //Events are dispatched at the end of the update cycle
    state_array[current_state]->GetEvents(EventManager::GetEventList());
}

void FSM::DispatchEvents(std::vector<AL::Event>& event_list)
{
}

//Rendering ------------------------------------------------------------------------------------------------------------

/**
 * \brief Used to Render all the 3D GameObjects,
 * or any class that inherits from GameObject
 *
 * NOTE: RENDERING 2D OBJECTS HERE WILL RESULT IN A CRASH
 */
void FSM::Render3D(DrawData* draw_data) const
{
    state_array[current_state]->Render3D(draw_data);
}

/**
 * \brief Sprite batched, Used to Render all the 2D GameObjects,
 * or any class that inherits from GameObject2D
 */
void FSM::Render2D(DrawData2D* draw_data2D) const
{
    state_array[current_state]->Render2D(draw_data2D);
}
