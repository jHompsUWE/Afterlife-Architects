#include "pch.h"
#include "Tilemap.h"

Tilemap::Tilemap(ID3D11Device* GD, int _size): size(_size)
{
	for (int x = 0; x < size; x++)
	{
		tilemap.emplace_back();
		for (int y = 0; y < size; y++)
		{
			tilemap[x].emplace_back(std::make_unique<Tile>(GD, Vector3(x, 0, y), Void));
		}
	}
}

Tilemap::~Tilemap()
{

}

void Tilemap::Tick(GameData* game_data)
{
	for (auto& x : tilemap)
	{
		for (auto& y : x)
		{
			y->Tick(game_data);
		}
	}
}

void Tilemap::Draw(DrawData* _DD)
{
	for (auto& x : tilemap)
	{
		for (auto& y : x)
		{
			y->Draw(_DD);
		}
	}
}

/// <summary>
/// Changes the box area from start to end to the given ZoneType
/// </summary>
/// <param name="zone_type">ZoneType of the tile</param>
/// <param name="start">Starting point of the box</param>
/// <param name="end">End point of the box</param>
void Tilemap::BoxFill(ZoneType zone_type, Vector3 start, Vector3 end)
{
	//Determine directions on X and Y axis
	int xDir = start.x < end.x ? 1 : -1;
	int zDir = start.z < end.z ? 1 : -1;
	//How many tiles on each axis?
	int xCols = 1 + abs(start.x - end.x);
	int zCols = 1 + abs(start.z - end.z);

	for (int x = 0; x < xCols; x++)
	{
		for (int z = 0; z < zCols; z++)
		{
			Vector3 tile_pos = start + Vector3(x * xDir, 0, z * zDir);
			SetTile(tile_pos, zone_type);
		}
	}
}

/// <summary>
/// Set the tile at the given position to the given ZoneType
/// </summary>
/// <param name="tile_pos">Position of tile</param>
/// <param name="zone_type">ZoneType of the tile</param>
void Tilemap::SetTile(Vector3 tile_pos, ZoneType zone_type)
{
	if (tile_pos.x > size - 1 || tile_pos.z > size - 1 || tile_pos.x < 0 || tile_pos.z < 0)
	{
		// Tile position exceeds tilemap size
		return;
	}

	tilemap[tile_pos.x][tile_pos.z]->SetTexture(zone_type);
}
