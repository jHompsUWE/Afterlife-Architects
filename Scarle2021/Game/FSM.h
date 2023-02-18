#pragma once
#include "DataManager.h"
#include "array"
#include "StateTemplate.h"

class FSM
{
public:
    FSM(GameData* _game_data);
    ~FSM() = default;

    bool init();

    // Update
    void Update(float& delta_time);

    //Renderers
    void Render3D();
    void Render2D();
    
    // M&K input queue
    void GetInput();

private:
    //Gamedata, pointer save for ease of access of the gamestate
    GameData* game_data = nullptr;
    
    //State Array
    std::array<std::unique_ptr<StateTemplate>, 4> state_array{};
};

