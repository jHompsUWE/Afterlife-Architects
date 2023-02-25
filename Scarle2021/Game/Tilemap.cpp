#include "pch.h"
#include "Tilemap.h"

Tilemap::Tilemap(ID3D11Device* GD, int _size): size(_size)
{
	for (int x = 0; x < size; x++)
	{
		tilemap.emplace_back();
		for (int y = 0; y < size; y++)
		{
			tilemap[x].emplace_back(std::make_unique<Tile>(GD, Vector3(x, 0, y), "Tile_Yellow"));
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
/// Fills the box area from start to end with given texture
/// </summary>
/// <param name="texture">Name of texture</param>
/// <param name="start">Starting point of the box</param>
/// <param name="end">End point of the box</param>
void Tilemap::BoxFill(std::string texture, Vector3 start, Vector3 end)
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
			SetTile(tile_pos, texture);
		}
	}
}

/// <summary>
/// Set the tile at the given position to the given texture
/// </summary>
/// <param name="tile_pos"Position of tile</param>
/// <param name="texture"Name of texture></param>
void Tilemap::SetTile(Vector3 tile_pos, std::string texture)
{
	if (tile_pos.x > size || tile_pos.z > size)
	{
		std::cout << "Tile position exceeds tilemap size" << std::endl;
		return;
	}

	tilemap[tile_pos.x][tile_pos.z]->SetTexture(texture);
}
