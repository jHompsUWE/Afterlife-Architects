#ifndef _GAME_DATA_H_
#define _GAME_DATA_H_

//=================================================================
//Main GameData class. Needed to be provided to most GOs in update
//=================================================================

#include "GameState.h"
#include "Keyboard.h"
#include "Mouse.h"

using namespace DirectX;

struct GameData
{
	float delta_time;  //Delta time
	float time_scale_factor = 1; //Scale of the scale update
	GameState current_game_state = gs_main_menu; //global GameState

	//player input state, this is here mostly for debug reasons.
	Keyboard::State keyboard_state;
	Mouse::State mouse_state;
	Keyboard::KeyboardStateTracker keyboard_state_tracker;
};
#endif
