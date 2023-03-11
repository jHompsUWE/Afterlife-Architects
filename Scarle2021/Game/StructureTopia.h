#pragma once
#include <memory>

#include "PopulationManager.h"
#include "StructureSprite.h"

class StructureTopia : public StructureSprite
{
public:
	StructureTopia(ID3D11Device* GD, Vector2 width_height, Vector3 tile_pos, int _tile_size, std::string texture, 
		PlaneType _plane, float _capacity, std::shared_ptr<PopulationManager> _population_manager);
	~StructureTopia();

	void TickStructure(GameData* game_data) override;

protected:

private:
	float capacity; // How many souls this building can hold
	std::shared_ptr<PopulationManager> population_manager;

};

