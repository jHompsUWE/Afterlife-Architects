#pragma once
#include "StructureSprite.h"

class StructureTrainingCenter: public StructureSprite
{
public:
	StructureTrainingCenter(ID3D11Device* GD, Vector2 width_height, Vector3 tile_pos, int _tile_size, std::string texture);
	~StructureTrainingCenter();

	void TickStructure(GameData* game_data) override;

protected:

private:

};

