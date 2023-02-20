#pragma once
#include "DataManager.h"
#include "array"
#include "StateTemplate.h"

/**
 * \brief This is the main game Finite State Machine, basically, our game loop!
 */
class FSM
{
public:
    explicit FSM(GameState& _current_state);
    ~FSM() = default;

    bool init();

    // Update
    void Update(GameData* game_data);

    // Renderers
    void Render3D(DrawData* draw_data) const;
    void Render2D(DrawData2D* draw_data2D) const;

private:
    GameState& current_state;
    // State Array 
    std::array<std::unique_ptr<StateTemplate>, 4> state_array{};
};

