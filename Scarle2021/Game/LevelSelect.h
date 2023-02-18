#pragma once
#include "StateTemplate.h"

class LevelSelect : public StateTemplate
{
public:
    explicit LevelSelect(GameData* _game_data);
    ~LevelSelect() override;

    bool init() override;

    //Update Cycles
    void Update(float& delta_time) override;
    void ScaledUpdate(float& delta_time) override;
    void LateUpdate() override;

    //Renders
    void Render2D() override;
    void Render3D() override;

    //Input
    void GetInput() override;
};

