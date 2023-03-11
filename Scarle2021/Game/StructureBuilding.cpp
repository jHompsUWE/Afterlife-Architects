#include "pch.h"
#include "StructureBuilding.h"

StructureBuilding::StructureBuilding(ID3D11Device* GD, Vector2 width_height, Vector3 tile_pos, int _tile_size, ID3D11ShaderResourceView* texture, 
	PlaneType _plane, ZoneType _zone, std::shared_ptr<PopulationManager> _population_manager, float _capacity):
	StructureSprite(GD, width_height, tile_pos, _tile_size, texture, _plane), capacity(_capacity), population_manager(_population_manager), zone(_zone)
{
	// Increment soul capacity on creation
	population_manager->IncrementZoneCapacity(plane, zone, capacity);
}

StructureBuilding::~StructureBuilding()
{
	// Decrement soul capacity on creation
	population_manager->IncrementZoneCapacity(plane, zone, -capacity);
}

void StructureBuilding::TickStructure(GameData* game_data)
{
}
