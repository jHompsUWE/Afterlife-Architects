#pragma once

#include "EconomyManager.h"
#include "StructureSprite.h"
#include "PopulationManager.h"
#include "ZoneType.h"

class StructureTrainingCenter: public StructureSprite
{
public:
	StructureTrainingCenter(ID3D11Device* GD, Vector2 width_height, Vector3 tile_pos, int _tile_size, ID3D11ShaderResourceView* texture,
		PlaneType _plane, EconomyManager* _econ_manager, std::shared_ptr<PopulationManager> _population_manager, float _conversion_rate);
	~StructureTrainingCenter();

	void TickStructure(GameData* game_data) override;

protected:

private:
	bool IsSoulHeavenGreater(float souls, ZoneType zone);
	bool IsSoulHellGreater(float souls, ZoneType zone);

	void AddSoulHeaven(float souls, ZoneType zone);
	void AddSoulHell(float souls, ZoneType zone);

	EconomyManager* econ_manager = nullptr;
	std::shared_ptr<PopulationManager> population_manager;
	float conversion_rate; // Conversion of souls to angels/demons
};

