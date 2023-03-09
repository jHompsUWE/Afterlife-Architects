#include "pch.h"
#include "StructureTopia.h"

StructureTopia::StructureTopia(ID3D11Device* GD, Vector2 width_height, Vector3 tile_pos, int _tile_size, std::string texture):
	StructureSprite(GD, width_height, tile_pos, _tile_size, texture)
{
}

StructureTopia::~StructureTopia()
{
}

void StructureTopia::TickStructure(GameData* game_data)
{
	std::cout << "TOPIA" << std::endl;
}

