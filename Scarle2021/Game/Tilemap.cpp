#include "pch.h"
#include "Tilemap.h"

Tilemap::Tilemap(ID3D11Device* GD, std::shared_ptr<TextureManager> _texture_manager, int _size, Vector3 _start) :
	size(_size), start(_start), texture_manager(_texture_manager)
{
	for (int x = 0; x < size; x++)
	{
		tilemap.emplace_back();
		for (int y = 0; y < size; y++)
		{
			tilemap[x].emplace_back(std::make_unique<Tile>(GD, start + Vector3(x, 0, y), Void));
			tilemap[x][y]->SetTexture(texture_manager->GetTextureZone(Void));
			tilemap[x][y]->UpdateWorldMatrix();
		}
	}
}

Tilemap::~Tilemap()
{

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
void Tilemap::BoxFill(std::unique_ptr<BuildingManager>& building_manager, std::unique_ptr<VibeTilemap>& vibe_tilemap,
	ZoneType zone_type, Vector3 start, Vector3 end)
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
				Vector3 origin = tilemap[tile_pos.x][tile_pos.z]->GetStructureOrigin();
				if (origin.y == 0)
				{
					// There is a structure on tile_pos

					// Get the tiles that this structure occupy
					std::vector<Vector3> tiles_to_remove = building_manager->GetStructureOccupiedTiles(origin);
					for (auto& temp_pos : tiles_to_remove)
					{
						temp_pos = WorldToLocalPos(temp_pos);
						if (temp_pos != tile_pos)
						{
							// Replace the tiles that this structure occupy to Void
							SetTile(temp_pos, Void);
						}
					}

					// Destroy structure on tile_pos
					building_manager->DestroyStructure(origin);

					// Adjust the vibe of the tiles around the structure destroyed
					vibe_tilemap->VibeChange(origin, -5, sqrt(tiles_to_remove.size()));
				}

				tilemap[tile_pos.x][tile_pos.z]->UnoccupyTile();
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
		tilemap[tile_pos.x][tile_pos.z]->GetZoneType() == zone_type ||
		!CanTileBeReplaced(tilemap[tile_pos.x][tile_pos.z]->GetZoneType()))
	{
		// Tile position exceeds tilemap size
		// Don't change texture if ZoneType is the same
		// This tile cannot be replaced
		return false;
	}

	switch (zone_type)
	{
	case Green:
	case Yellow:
	case Orange:
	case Brown:
	case Purple:
	case Red:
	case Blue:
		if (!IsRoadNearby(tile_pos))
		{
			// Turn zone to inactive if there is no road nearby
			zone_type = GetInactiveZone(zone_type);
		}
		break;

	case Inactive_Green:
	case Inactive_Yellow:
	case Inactive_Orange:
	case Inactive_Brown:
	case Inactive_Purple:
	case Inactive_Red:
	case Inactive_Blue:
		if (IsRoadNearby(tile_pos))
		{
			// Dont set tile as inactive if there is a road nearby
			return false;
		}
		break;

	case Road:
		// Activate inactive tiles near road
		tilemap[tile_pos.x][tile_pos.z]->SetTexture(texture_manager->GetTextureZone(zone_type));
		tilemap[tile_pos.x][tile_pos.z]->SetZoneType(zone_type);
		ActivateNearbyTile(tile_pos);
		return true;

	default:
		break;
	}

	if (tilemap[tile_pos.x][tile_pos.z]->GetZoneType() == Road)
	{
		// Deactivate nearby tiles if road is replaced
		tilemap[tile_pos.x][tile_pos.z]->SetTexture(texture_manager->GetTextureZone(zone_type));
		tilemap[tile_pos.x][tile_pos.z]->SetZoneType(zone_type);
		DeactivateNearbyTile(tile_pos);
		return true;
	}

	tilemap[tile_pos.x][tile_pos.z]->SetTexture(texture_manager->GetTextureZone(zone_type));
	tilemap[tile_pos.x][tile_pos.z]->SetZoneType(zone_type);
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
			if (tilemap[x][z]->GetZoneType() == zone_type && tilemap[x][z]->IsTileOccupied() == false)
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

				if (tilemap[pos.x][pos.z]->GetZoneType() == zone_type && tilemap[pos.x][pos.z]->IsTileOccupied() == false)
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

	return tilemap[tile_pos.x][tile_pos.z]->IsTileOccupied();
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
			tilemap[tile_pos.x + x][tile_pos.z + z]->OccupyTile(Vector3(tile_pos.x, 0, tile_pos.z));
		}
	}
}

/// <summary>
/// Get the active tile counterpart of a ZoneType
/// </summary>
/// <param name="zone_type">The ZoneType</param>
/// <returns>Active ZoneType of the inactive tile of the given zone</returns>
ZoneType Tilemap::GetActiveZone(ZoneType zone_type)
{
	switch (zone_type)
	{
	case Inactive_Green:
		return Green;

	case Inactive_Yellow:
		return Yellow;

	case Inactive_Orange:
		return Orange;

	case Inactive_Brown:
		return Brown;

	case Inactive_Purple:
		return Purple;

	case Inactive_Red:
		return Red;

	case Inactive_Blue:
		return Blue;

	default:
		return zone_type;
	}
}

/// <summary>
/// Get the inactive tile counterpart of a ZoneType
/// </summary>
/// <param name="zone_type">The ZoneType</param>
/// <returns>Inactive ZoneType of the inactive tile of the given zone</returns>
ZoneType Tilemap::GetInactiveZone(ZoneType zone_type)
{
	switch (zone_type)
	{
	case Green:
		return Inactive_Green;

	case Yellow:
		return Inactive_Yellow;

	case Orange:
		return Inactive_Orange;

	case Brown:
		return Inactive_Brown;

	case Purple:
		return Inactive_Purple;

	case Red:
		return Inactive_Red;

	case Blue:
		return Inactive_Blue;

	default:
		return zone_type;
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
			if (!IsPosValid(Vector3(start.x + x, 0, start.z + z)) || IsTileOccupied(Vector3(start.x + x, 0, start.z + z)))
			{
				return false;
			}
		}
	}
	return true;
}

/// <summary>
/// Checks if there is a road in a 3 tile radius around the tilePos
/// </summary>
/// <param name="tile_pos">Position of tile to be checked</param>
/// <returns>True if there is a road, False if there is no road</returns>
bool Tilemap::IsRoadNearby(Vector3 tile_pos)
{
	for (int x = -3; x <= 3; x++)
	{
		for (int z = -3; z <= 3; z++)
		{
			if (IsPosValid(Vector3(tile_pos.x + x, 0, tile_pos.z + z)))
			{
				if (tilemap[tile_pos.x + x][tile_pos.z + z]->GetZoneType() == Road)
				{
					return true;
				}
			}
		}
	}
	return false;
}

/// <summary>
/// Checks if the given ZoneType can be replaced
/// </summary>
/// <param name="zone_type">ZoneType</param>
/// <returns>True if it can be replaced, False otherwise</returns>
bool Tilemap::CanTileBeReplaced(ZoneType zone_type)
{
	switch (zone_type)
	{
	case Water:
	case Lava:
	case Karma_Anchor:
	case Rock:
		return false;

	default:
		return true;
	}
}

/// <summary>
/// Activates the tiles in a 3 tile radius around the tile pos
/// </summary>
/// <param name="tile_pos">Vector3 tile position</param>
void Tilemap::ActivateNearbyTile(Vector3 tile_pos)
{
	for (int x = -3; x <= 3; x++)
	{
		for (int z = -3; z <= 3; z++)
		{
			if (IsPosValid(Vector3(tile_pos.x + x, 0, tile_pos.z + z)))
			{
				ZoneType zone_type = GetActiveZone(tilemap[tile_pos.x + x][tile_pos.z + z]->GetZoneType());
				switch (zone_type)
				{
				case Green:
				case Yellow:
				case Orange:
				case Brown:
				case Purple:
				case Red:
				case Blue:
					// Activate this tile
					SetTile(Vector3(tile_pos.x + x, 0, tile_pos.z + z), zone_type);
					break;

				default:
					break;
				}
			}
		}
	}
}

/// <summary>
/// Deactivates the tiles in a 3 tile radius around the tile pos
/// </summary>
/// <param name="tile_pos">Vector3 tile position</param>
void Tilemap::DeactivateNearbyTile(Vector3 tile_pos)
{
	for (int x = -3; x <= 3; x++)
	{
		for (int z = -3; z <= 3; z++)
		{
			if (IsPosValid(Vector3(tile_pos.x + x, 0, tile_pos.z + z)))
			{
				ZoneType zone_type = GetInactiveZone(tilemap[tile_pos.x + x][tile_pos.z + z]->GetZoneType());
				switch (zone_type)
				{
				case Inactive_Green:
				case Inactive_Yellow:
				case Inactive_Orange:
				case Inactive_Brown:
				case Inactive_Purple:
				case Inactive_Red:
				case Inactive_Blue:
					// Deactivate this tile
					SetTile(Vector3(tile_pos.x + x, 0, tile_pos.z + z), zone_type);
					break;

				default:
					break;
				}
			}
		}
	}
}

/// <summary>
/// Converts world poistion to local position
/// </summary>
/// <param name="world_pos">World position to be converted</param>
/// <returns>Local position</returns>
Vector3 Tilemap::WorldToLocalPos(Vector3 world_pos)
{
	return Vector3(world_pos.x - start.x, 0, world_pos.z - start.z);
}

/// <summary>
/// Converts local position to world position
/// </summary>
/// <param name="local_pos">Local position to be converted</param>
/// <returns>Word position</returns>
Vector3 Tilemap::LocalToWorldPos(Vector3 local_pos)
{
	return Vector3(local_pos.x + start.x, 0, local_pos.z + start.z);
}