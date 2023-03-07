#include "pch.h"
#include "StructureSprite.h"

/// <summary>
/// Creates a VBQuad angled at the camera of the given width and height
/// </summary>
/// <param name="GD">DirectX 3D Device</param>
/// <param name="width_height">Vector 2 of width and height of sprite in world</param>
/// <param name="tile_pos">Position of structure</param>
/// <param name="tile_size">The number of tiles this structure occupies</param>
/// <param name="texture">The texture attached to the VBQuad</param>
StructureSprite::StructureSprite(ID3D11Device* GD, Vector2 width_height, Vector3 tile_pos, int _tile_size, std::string texture)
	: VBQuad(GD, width_height.x, width_height.y), tile_size(_tile_size)
{
	SetPitch(-30 * PI / 180);
	SetYaw(45 * PI / 180);
	SetPos(tile_pos + Vector3(-0.5, 0, 0.5) * tile_size + Vector3(0.1, 0, 0.1));
	SetTexture(texture);
	AddOccupiedTiles(tile_pos, tile_size);
}

StructureSprite::~StructureSprite()
{
}

/// <summary>
/// Add the tiles occupied by this structure to the occupied_tiles vector
/// </summary>
/// <param name="tile_pos">Position of the structure</param>
/// <param name="tile_size">How many tiles this structure occupies</param>
void StructureSprite::AddOccupiedTiles(Vector3 tile_pos, int tile_size)
{
	occupied_tiles.emplace_back(tile_pos);
	for (int x = 0; x < tile_size; x++)
	{
		for (int z = 0; z < tile_size; z++)
		{
			occupied_tiles.emplace_back(Vector3(tile_pos.x + x, 0, tile_pos.z + z));
		}
	}
}
