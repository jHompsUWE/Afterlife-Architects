#include "pch.h"
#include "StructureKarmaStation.h"

StructureKarmaStation::StructureKarmaStation(ID3D11Device* GD, Vector2 width_height, Vector3 tile_pos, int _tile_size, ID3D11ShaderResourceView* texture,
	PlaneType _plane) :
	StructureSprite(GD, width_height, tile_pos, _tile_size, texture, _plane)
{
}

StructureKarmaStation::~StructureKarmaStation()
{
}

void StructureKarmaStation::TickStructure(GameData* game_data)
{
	// Insert Functionality for Karma Station here
	// This function is called every few seconds instead of per frame
}
