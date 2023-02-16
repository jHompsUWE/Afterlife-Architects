#include "pch.h"
#include "FSM.h"
#include "iostream"

#include "GameOver.h"
#include "GamePlay.h"
#include "LevelSelect.h"
#include "MainMenu.h"


FSM::FSM(GameData* _game_data) : game_data(_game_data)
{
    //Allocate a state to each slot of the state array
    state_array[gs_main_menu] = std::make_unique<MainMenu>(game_data);
    state_array[gs_level_select] = std::make_unique<LevelSelect>(game_data);
    state_array[gs_gameplay] = std::make_unique<GamePlay>(game_data);
    state_array[gs_game_over] = std::make_unique<GameOver>(game_data);
}

bool FSM::init()
{
    //Runs each state and its init function
    for (auto& state : state_array)
    {
        if(!state->init())
        {
            std::cout << typeid(state).name() << " Failed Initilization" << std::endl;
            return false;
        }
    }
    return true;
}

void FSM::Update(float& delta_time)
{
    //normal update
    state_array[game_data->current_game_state]->Update(delta_time);

    //If we're not in gameplay, we do not need Scaled Update.
    if(game_data->current_game_state == gs_gameplay)
    {
        if(game_data->time_scale_factor != 0)
        {
            //Scales the delta time accordingly with the time scale factor
            float scaled_dt = delta_time * game_data->time_scale_factor;
            state_array[game_data->current_game_state]->ScaledUpdate(scaled_dt);
        }
    }

    //Runs this for last
    state_array[game_data->current_game_state]->LateUpdate();
}

void FSM::Render()
{
    state_array[game_data->current_game_state]->Render();
}

void FSM::GetInput()
{
    state_array[game_data->current_game_state]->GetInput();
}
