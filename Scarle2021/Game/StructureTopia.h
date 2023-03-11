#pragma once
#include <memory>

#include "PopulationManager.h"
#include "StructureSprite.h"

class StructureTopia : public StructureSprite
{
public:
	StructureTopia(ID3D11Device* GD, Vector2 width_height, Vector3 tile_pos, int _tile_size, ID3D11ShaderResourceView* texture,
		PlaneType _plane, std::shared_ptr<PopulationManager> _population_manager, float _capacity);
	~StructureTopia();

	void TickStructure(GameData* game_data) override;

protected:

private:
	float capacity; // How many angels/demons this building can hold
	std::shared_ptr<PopulationManager> population_manager;
};

