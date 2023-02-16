#pragma once
#include "StateTemplate.h"

class LevelSelect : public StateTemplate
{
public:
    explicit LevelSelect(GameData* _game_data);
    ~LevelSelect() override;

    bool init() override;
	
    void Update(float& delta_time) override;
    auto ScaledUpdate(float& delta_time) -> void override;
    void LateUpdate() override;

    void Render() override;

    void GetInput() override;
};

