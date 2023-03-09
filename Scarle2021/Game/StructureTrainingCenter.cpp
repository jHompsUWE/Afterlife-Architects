#include "pch.h"
#include "StructureTrainingCenter.h"

StructureTrainingCenter::StructureTrainingCenter(ID3D11Device* GD, Vector2 width_height, Vector3 tile_pos, int _tile_size, std::string texture):
	StructureSprite(GD, width_height, tile_pos, _tile_size, texture)
{
}

StructureTrainingCenter::~StructureTrainingCenter()
{
}

void StructureTrainingCenter::TickStructure(GameData* game_data)
{
	std::cout << "TRAINING CENTER" << std::endl;
}
