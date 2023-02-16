#ifndef _GAME_DATA_H_
#define _GAME_DATA_H_

//=================================================================
//Data to be passed by game to all Game Objects via Tick
//=================================================================

#include "GameState.h"
#include "Keyboard.h"
#include "Mouse.h"

using namespace DirectX;

struct GameData
{
	float delta_time;  //Delta time
	float time_scale_factor = 1; //Scale of the scale update
	GameState current_game_state; //global GameState

	//player input
	Keyboard::State keybaord_state;
	Mouse::State mouse_state;
	Keyboard::KeyboardStateTracker keyboard_state_tracker;
};
#endif
