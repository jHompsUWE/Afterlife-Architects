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

// Based on https://forum.unity.com/threads/tilemap-boxfill-is-horrible.502864/ by shawnblais, Oct 11, 2012
/// <summary>
/// Changes the box area from start to end to the given ZoneType
/// </summary>
/// <param name="zone_type">ZoneType of the tile</param>
/// <param name="start">Starting point of the box</param>
/// <param name="end">End point of the box</param>
void Tilemap::BoxFill(std::unique_ptr<BuildingManager>& building_manager, ZoneType zone_type, Vector3 start, Vector3 end)
{
	//Determine directions on X and Y axis
	int xDir = start.x < end.x ? 1 : -1;
	int zDir = start.z < end.z ? 1 : -1;
	//How many tiles on each axis?
	int xCols = 1 + abs(start.x - end.x);
	int zCols = 1 + abs(start.z - end.z);

	// Iterate through all the tiles within the box selection
	for (int x = 0; x < xCols; x++)
	{
		for (int z = 0; z < zCols; z++)
		{
			Vector3 tile_pos = start + Vector3(x * xDir, 0, z * zDir);

			// Replace the tile at tile_pos with zone_type
			if (SetTile(tile_pos, zone_type))
			{
				// Tile at tile_pos is replaced, destroy structure on that tile
				building_manager->DestroyStructure(tile_pos);
			}
		}
	}
}

/// <summary>
/// Set the tile at the given position to the given ZoneType
/// </summary>
/// <param name="tile_pos">Position of tile</param>
/// <param name="zone_type">ZoneType of the tile</param>
/// <returns>true if tile is changed, false if tile is not changed</returns>
bool Tilemap::SetTile(Vector3 tile_pos, ZoneType zone_type)
{
	if (tile_pos.x > size - 1 || tile_pos.z > size - 1 || tile_pos.x < 0 || tile_pos.z < 0
		|| tilemap[tile_pos.x][tile_pos.z]->GetZoneType() == zone_type)
	{
		// Tile position exceeds tilemap size
		// Don't change texture if ZoneType is the same
		return false;
	}

	tilemap[tile_pos.x][tile_pos.z]->SetTexture(zone_type);
	tilemap[tile_pos.x][tile_pos.z]->SetIsOccupied(false);
	return true;
}

/// <summary>
/// Finds an non-occupied 1x1 tile of the given ZoneType
/// </summary>
/// <param name="zone_type">The ZoneType of the desired empty tile</param>
/// <returns>Vector3 position of the empty tile, returns Y = 1 if no valid tile is found</returns>
Vector3 Tilemap::FindEmpty1x1TileOfType(ZoneType zone_type)
{
	for (int x = 0; x < tilemap.size(); x++)
	{
		for (int z = 0; z < tilemap[x].size(); z++)
		{
			if (tilemap[x][z]->GetZoneType() == zone_type && tilemap[x][z]->GetIsOccupied() == false)
			{
				// Tile at (x, 0, z) matches zone_type and is not occupied
				return Vector3(x, 0, z);
			}
		}
	}

	// Return Y = 1 if no valid tile is found
	return Vector3(0, 1, 0);
}

/// <summary>
/// Checks if the tile at the given position is occupied by a structure
/// </summary>
/// <param name="tile_pos">Tile position</param>
/// <returns>true if occupied, false if not occupied</returns>
bool Tilemap::IsTileOccupied(Vector3 tile_pos)
{
	if (tile_pos.x > size - 1 || tile_pos.z > size - 1 || tile_pos.x < 0 || tile_pos.z < 0)
	{
		// Tile position exceeds tilemap size
		return true;
	}

	return tilemap[tile_pos.x][tile_pos.z]->GetIsOccupied();
}

/// <summary>
/// Marks the given tile as occupied
/// </summary>
/// <param name="tile_pos">Position of the tile to be occupied</param>
void Tilemap::OccupyTile(Vector3 tile_pos)
{
	if (tile_pos.x > size - 1 || tile_pos.z > size - 1 || tile_pos.x < 0 || tile_pos.z < 0)
	{
		// Tile position exceeds tilemap size
		return;
	}

	tilemap[tile_pos.x][tile_pos.z]->SetIsOccupied(true);
}
