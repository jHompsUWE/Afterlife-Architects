#pragma once
#include "StateTemplate.h"

class GameOver : public StateTemplate
{
public:
    explicit GameOver(GameData* _game_data);
    ~GameOver() override;

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

