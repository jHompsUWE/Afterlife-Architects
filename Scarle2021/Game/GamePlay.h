#pragma once
#include "StateTemplate.h"

class GamePlay : public StateTemplate
{
public:
    explicit GamePlay(GameData* _game_data);
    ~GamePlay() override;

    bool init() override;
	
    void Update(float& delta_time) override;
    void ScaledUpdate(float& delta_time) override;
    void LateUpdate() override;
    
    void Render() override;
    
    void GetInput() override;

private:
    TextGO2D* text = nullptr;
};

