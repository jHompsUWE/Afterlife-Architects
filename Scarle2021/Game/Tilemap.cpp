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
			tilemap[x][y]->Tick();
		}
	}
}

Tilemap::~Tilemap()
{

}

void Tilemap::Draw(DrawData* _DD, bool show_vibe)
{
	for (auto& x : tilemap)
	{
		for (auto& y : x)
		{
			y->Draw(_DD, show_vibe);
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
			if (SetTile(tile_pos, zone_type) || zone_type == Structure)
			{
				// Tile at tile_pos is replaced
				// Check if there is structure on tile_pos
				std::vector<Vector3> tiles_to_remove = building_manager->GetStructureOccupiedTiles(tile_pos);
				if (!tiles_to_remove.empty())
				{				
					// Replace the tiles that this structure occupy to Void
					for (auto& temp_pos : tiles_to_remove)
					{
						if (temp_pos != tile_pos)
						{
							SetTile(temp_pos, Void);
						}
					}

					// Destroy structure on tile_pos
					Vector3 origin_point = building_manager->DestroyStructure(tile_pos);
					int temp_int = origin_point.y;
					switch (temp_int)
					{
						case 1:
							VibeChange1x1(origin_point, -5);
							break;
						case 2:
							VibeChange2x2(origin_point, -5);
							break;
						case 3:
							VibeChange3x3(origin_point, -5);
							break;
						default:
							break;
					}
				}
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
	if (!IsPosValid(tile_pos) ||
		tilemap[tile_pos.x][tile_pos.z]->GetZoneType() == zone_type)
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
/// Finds an non-occupied 2x2 tile of the given ZoneType
/// </summary>
/// <param name="zone_type">The ZoneType of the desired empty tile</param>
/// <returns>Vector3 position of the empty tile, returns Y = 1 if no valid tile is found</returns>
Vector3 Tilemap::FindEmpty2x2TileOfType(ZoneType zone_type)
{
	for (int x = 0; x < tilemap.size(); x++)
	{
		for (int z = 0; z < tilemap[x].size(); z++)
		{
			Vector3 tile_pos = Vector3(x, 0, z);
			std::vector<Vector3> tile_list;
			tile_list.emplace_back(tile_pos);
			tile_list.emplace_back(tile_pos + Vector3(1, 0, 0));
			tile_list.emplace_back(tile_pos + Vector3(0, 0, 1));
			tile_list.emplace_back(tile_pos + Vector3(1, 0, 1));

			int tile_found = 0;
			for(auto& pos : tile_list)
			{
				if (pos.x > size - 1 || pos.z > size - 1 || pos.x < 0 || pos.z < 0)
				{
					break;
				}

				if (tilemap[pos.x][pos.z]->GetZoneType() == zone_type && tilemap[pos.x][pos.z]->GetIsOccupied() == false)
				{
					tile_found += 1;
				}
			}

			// 2x2 empty tiles are found around this tile_pos
			if (tile_found == 4)
			{
				return tile_pos;
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
	if (!IsPosValid(tile_pos))
	{
		return true;
	}

	return tilemap[tile_pos.x][tile_pos.z]->GetIsOccupied();
}

/// <summary>
/// Marks the area around tile_pos of the given size as occupied
/// </summary>
/// <param name="tile_pos">The tile to be marked as occupied</param>
/// <param name="_size">The size of the area in positive X and Z direction to be marked as occupied</param>
void Tilemap::OccupyTile(Vector3 tile_pos, int _size)
{
	if (!IsPosValid(tile_pos))
	{
		return;
	}

	for (int x = 0; x < _size; x++)
	{
		for (int z = 0; z < _size; z++)
		{
			tilemap[tile_pos.x + x][tile_pos.z + z]->SetIsOccupied(true);
		}
	}
}

/// <summary>
/// Checks if the given tile position is within the tilemap
/// </summary>
/// <param name="tile_pos">Vector 3 position of the tile position</param>
/// <returns>True if valid, false if invalid</returns>
bool Tilemap::IsPosValid(Vector3 tile_pos)
{
	if (tile_pos.x > size - 1 || tile_pos.z > size - 1 || tile_pos.x < 0 || tile_pos.z < 0)
	{
		// Tile position exceeds tilemap size
		return false;
	}
	return true;
}

/// <summary>
/// Checks if every tile of the box area at the given position with the given size is within the tilemap
/// </summary>
/// <param name="start">Starting point of the box area</param>
/// <param name="_size">Size of the box</param>
/// <returns>True if valid, false if invalid</returns>
bool Tilemap::IsAreaValid(Vector3 start, int _size)
{
	for (int x = 0; x < _size; x++)
	{
		for (int z = 0; z < _size; z++)
		{
			if (!IsPosValid(Vector3(start.x + x, 0, start.z + z)))
			{
				return false;
			}
		}
	}
	return true;
}

/// <summary>
/// Change tilemap's vibes system at certain tile pos and value for a 1 by 1 building
/// </summary>
/// <param name="tile_pos"></param>
/// <param name="vibe_diff"></param>
void Tilemap::VibeChange1x1(Vector3 tile_pos, int vibe_diff)
{
	tilemap[tile_pos.x][tile_pos.z]->ChangeVibe(vibe_diff);
	if (tile_pos.x > 0)
	{
		tilemap[tile_pos.x-1][tile_pos.z]->ChangeVibe(vibe_diff);
	}
	if (tile_pos.x < 99)
	{
		tilemap[tile_pos.x+1][tile_pos.z]->ChangeVibe(vibe_diff);
	}
	if (tile_pos.z > 0)
	{
		tilemap[tile_pos.x][tile_pos.z-1]->ChangeVibe(vibe_diff);
	}
	if (tile_pos.z < 99)
	{
		tilemap[tile_pos.x][tile_pos.z+1]->ChangeVibe(vibe_diff);
	}
}

/// <summary>
/// Change tilemap's vibes system at certain tile pos and value for a 2 by 2 building
/// </summary>
/// <param name="tile_pos"></param>
/// <param name="vibe_diff"></param>
void Tilemap::VibeChange2x2(Vector3 tile_pos, int vibe_diff)
{
	tilemap[tile_pos.x][tile_pos.z]->ChangeVibe(vibe_diff);
	tilemap[tile_pos.x+1][tile_pos.z]->ChangeVibe(vibe_diff);
	tilemap[tile_pos.x][tile_pos.z+1]->ChangeVibe(vibe_diff);
	tilemap[tile_pos.x+1][tile_pos.z+1]->ChangeVibe(vibe_diff);
	if (tile_pos.x > 0)
	{
		tilemap[tile_pos.x - 1][tile_pos.z]->ChangeVibe(vibe_diff);
		tilemap[tile_pos.x - 1][tile_pos.z+1]->ChangeVibe(vibe_diff);
	}
	if (tile_pos.x < 98)
	{
		tilemap[tile_pos.x + 2][tile_pos.z]->ChangeVibe(vibe_diff);
		tilemap[tile_pos.x + 2][tile_pos.z+1]->ChangeVibe(vibe_diff);
	}
	if (tile_pos.z > 0)
	{
		tilemap[tile_pos.x][tile_pos.z - 1]->ChangeVibe(vibe_diff);
		tilemap[tile_pos.x+1][tile_pos.z - 1]->ChangeVibe(vibe_diff);
	}
	if (tile_pos.z < 98)
	{
		tilemap[tile_pos.x][tile_pos.z + 2]->ChangeVibe(vibe_diff);
		tilemap[tile_pos.x+1][tile_pos.z + 2]->ChangeVibe(vibe_diff);
	}
}

/// <summary>
/// Change tilemap's vibes system at certain tile pos and value for a 3 by 3 building
/// </summary>
/// <param name="tile_pos"></param>
/// <param name="vibe_diff"></param>
void Tilemap::VibeChange3x3(Vector3 tile_pos, int vibe_diff)
{

}