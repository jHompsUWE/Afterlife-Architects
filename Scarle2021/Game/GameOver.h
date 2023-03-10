#pragma once
#include "StateTemplate.h"
#include "ImageGO2D.h"

class GameOver : public StateTemplate
{
public:
	GameOver();
    ~GameOver() override;

	bool init() override;

	//Update Cycles
	void Update(GameData* game_data) override;
	void ScaledUpdate(GameData* game_data, float& scaled_dt) override;
	void LateUpdate(GameData* game_data) override;

	void regenPerlin();
	void regenPerlin(int seed);
	
	//Events
	void GetEvents(std::list<AfterlifeEvent>& event_list) override;

	//Renders
	void Render2D(DrawData2D* draw_data2D) override;
	void Render3D(DrawData* draw_data) override;

private:
	//Visualization of pathfinding
	std::vector<GameObject2D*> on_screen_tiles{};

	float scale = 0.50f;
	float persitance = 0.65f;
	float lacunarity = 4.0f;
};

