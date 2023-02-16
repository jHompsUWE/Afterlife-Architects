#pragma once
#include "StateTemplate.h"

class GameOver : public StateTemplate
{
public:
    explicit GameOver(GameData* _game_data);
    ~GameOver() override;

    bool init() override;
	
    void Update(float& delta_time) override;
    void ScaledUpdate(float& delta_time) override;
    void LateUpdate() override;

	void Render() override;
	
    void GetInput() override;
};

