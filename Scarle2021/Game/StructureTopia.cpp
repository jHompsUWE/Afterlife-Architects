#include "pch.h"
#include "StructureTopia.h"

StructureTopia::StructureTopia(ID3D11Device* GD, Vector2 width_height, Vector3 tile_pos, int _tile_size, std::string texture, 
	PlaneType _plane, float _capacity, std::shared_ptr<PopulationManager> _population_manager):
	StructureSprite(GD, width_height, tile_pos, _tile_size, texture, _plane), capacity(_capacity), population_manager(_population_manager)
{
	// Increment Angels capacity on creation
	population_manager->IncrementADCapacity(plane, capacity);
}

StructureTopia::~StructureTopia()
{
	// Decrement Angels capacity on destruction
	population_manager->IncrementADCapacity(plane, -capacity);
}

void StructureTopia::TickStructure(GameData* game_data)
{
}

