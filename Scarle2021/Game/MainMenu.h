#pragma once
#include "StateTemplate.h"

class MainMenu : public StateTemplate
{
public:
	explicit MainMenu(GameData* _game_data);
	~MainMenu() override;

	bool init() override;
	
	void Update(float& delta_time) override;
	void ScaledUpdate(float& delta_time) override;
	void LateUpdate() override;

	void Render() override;
	
	void GetInput() override;

private:
	TextGO2D* text = nullptr;
};

