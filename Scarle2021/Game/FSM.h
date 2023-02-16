#pragma once
#include "ScarlePointers.h"
#include "array"
#include "StateTemplate.h"

class FSM
{
public:
    FSM(GameData* _game_data);
    ~FSM() = default;

    bool init();

    // Updates
    void Update(float& delta_time);

    //Render
    void Render();
    
    // M&K input queue
    void GetInput();

private:
    //Gamedata, pointer save for ease of access of the gamestate
    GameData* game_data = nullptr;
    //State Array
    std::array<std::unique_ptr<StateTemplate>, 4> state_array{};
};

