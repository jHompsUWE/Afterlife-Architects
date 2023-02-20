#pragma once
#include "StateTemplate.h"

class MainMenu : public StateTemplate
{
public:
	MainMenu();
	~MainMenu() override;

	bool init() override;

	//Update Cycles
	void Update(GameData* game_data) override;
	void ScaledUpdate(GameData* game_data, float& scaled_dt) override;
	void LateUpdate(GameData* game_data) override;

	//Renders
	void Render2D(DrawData2D* draw_data2D) override;
	void Render3D(DrawData* draw_data) override;

	//Input
	void GetEvents(queue<AfterlifeEvent>&) override;

private:
};

