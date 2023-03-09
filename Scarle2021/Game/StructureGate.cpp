#include "pch.h"
#include "StructureGate.h"

StructureGate::StructureGate(ID3D11Device* GD, Vector2 width_height, Vector3 tile_pos, int _tile_size, std::string texture):
	StructureSprite(GD, width_height, tile_pos, _tile_size, texture)
{
}

StructureGate::~StructureGate()
{
}

void StructureGate::TickStructure(GameData* game_data)
{
	std::cout << "GATE" << std::endl;
}
