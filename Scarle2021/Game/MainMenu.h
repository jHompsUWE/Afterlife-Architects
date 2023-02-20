#pragma once
#include "StateTemplate.h"
#include "TextGO2D.h"

class MainMenu : public StateTemplate
{
public:
	MainMenu();
	~MainMenu() override;

	bool init() override;

	//Events
	void GetEvents(queue<AfterlifeEvent>& event_queue) override;
	
	//Update Cycles
	void Update(GameData* game_data) override;
	void ScaledUpdate(GameData* game_data, float& scaled_dt) override;
	void LateUpdate(GameData* game_data) override;
	
	//Renders
	void Render2D(DrawData2D* draw_data2D) override;
	void Render3D(DrawData* draw_data) override;

private:
	TextGO2D* text = nullptr;
};

