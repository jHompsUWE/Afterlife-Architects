#pragma once
#include "StateTemplate.h"

class GamePlay : public StateTemplate
{
public:
    explicit GamePlay(GameData* _game_data);
    ~GamePlay() override;

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

private:
    TextGO2D* text = nullptr;
};

