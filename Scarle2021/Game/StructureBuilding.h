#pragma once

#include "StructureSprite.h"
#include "PopulationManager.h"
#include "ZoneType.h"

class StructureBuilding : public StructureSprite
{
public:
	StructureBuilding(ID3D11Device* GD, Vector2 width_height, Vector3 tile_pos, int _tile_size, ID3D11ShaderResourceView* texture,
		PlaneType _plane, ZoneType _zone, std::shared_ptr<PopulationManager> _population_manager, float _capacity);
	~StructureBuilding();

	void TickStructure(GameData* game_data) override;

protected:

private:
	float capacity; // How many souls this building can hold
	std::shared_ptr<PopulationManager> population_manager;
	ZoneType zone;
};

