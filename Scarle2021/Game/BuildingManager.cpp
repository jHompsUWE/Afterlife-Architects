#include "pch.h"
#include "BuildingManager.h"
#include <iostream>

BuildingManager::BuildingManager(ID3D11Device* GD): d11_device(GD)
{
}

BuildingManager::~BuildingManager()
{
}

void BuildingManager::Draw(DrawData* _DD)
{
	for (auto& structure : structure_list)
	{
		structure->Draw(_DD);
	}
}

/// <summary>
/// Creates a 1x1 house of the given ZoneType at the given tile position
/// </summary>
/// <param name="zone_type">ZoneType of the house to be built</param>
/// <param name="tile_position">Tile position of the house</param>
void BuildingManager::Create1x1House(ZoneType zone_type, Vector3 tile_position)
{
	// height value is calculated by dividing the texture height with witdh
	float height = 0;
	std::string texture;

	switch (zone_type)
	{
	case Green:
		height = 38.0f / 32.0f;
		texture = "Building_Green_Heaven_1x1";
		break;

	case Yellow:
		height = 84.0f / 32.0f;
		texture = "Building_Yellow_Heaven_1x1";
		break;

	case Orange:
		height = 1;
		texture = "Building_Orange_Heaven_1x1";
		break;

	case Brown:
		height = 33.0f / 32.0f;
		texture = "Building_Brown_Heaven_1x1";
		break;

	case Purple:
		height = 52.0f / 32.0f;
		texture = "Building_Purple_Heaven_1x1";
		break;

	case Red:
		height = 39.0f / 32.0f;
		texture = "Building_Red_Heaven_1x1";
		break;

	case Blue:
		height = 49.0f / 32.0f;
		texture = "Building_Blue_Heaven_1x1";
		break;

	default:
		return;
	}

	// sqrt(2) is the size of the quad needed to fit structure to a 1x1 unit isometric tile
	structure_list.emplace_back(std::make_unique<StructureSprite>(
		d11_device, Vector2(sqrt(2), sqrt(2) * height), tile_position, 1, texture));
	structure_list.back()->UpdateWorldMatrix();
}

/// <summary>
/// Creates a 2x2 house of the given ZoneType at the given tile position
/// </summary>
/// <param name="zone_type">ZoneType of the house to be built</param>
/// <param name="tile_position">Tile position of the house</param>
void BuildingManager::Create2x2House(ZoneType zone_type, Vector3 tile_position)
{
	// height value is calculated by dividing the texture height with witdh
	float height = 0;
	std::string texture;

	switch (zone_type)
	{
	case Green:
		height = 81.0f / 64.0f;
		texture = "Building_Green_Heaven_2x2";
		break;

	case Yellow:
		height = 87.0f / 64.0f;
		texture = "Building_Yellow_Heaven_2x2";
		break;

	case Orange:
		height = 51.0f / 64.0f;
		texture = "Building_Orange_Heaven_2x2";
		break;

	case Brown:
		height = 90.0f / 64.0f;
		texture = "Building_Brown_Heaven_2x2";
		break;

	case Purple:
		height = 82.0f / 64.0f;
		texture = "Building_Purple_Heaven_2x2";
		break;

	case Red:
		height = 88.0f / 64.0f;
		texture = "Building_Red_Heaven_2x2";
		break;

	case Blue:
		height = 89.0f / 64.0f;
		texture = "Building_Blue_Heaven_2x2";
		break;

	default:
		return;
	}

	// sqrt(2) * 2 is the size of the quad needed to fit structure to a 2x2 unit isometric tile
	structure_list.emplace_back(std::make_unique<StructureSprite>(
		d11_device, Vector2(sqrt(2) * 2, sqrt(2) * height * 2), tile_position, 2, texture));
	structure_list.back()->UpdateWorldMatrix();
}

/// <summary>
/// Creates a structure of the given type at the given tile position
/// </summary>
/// <param name="structure_type">The type of the structure</param>
/// <param name="tile_position">The position of the strucutre</param>
void BuildingManager::CreateStructure(StructureType structure_type, Vector3 tile_position)
{
	// height value is calculated by dividing the texture height with witdh
	float height = 0;
	std::string texture;
	int size = GetSizeOfStructure(structure_type);

	switch (structure_type)
	{
	case Gate:
		height = 90.0f / 95.0f;
		texture = "Gate_T1_Heaven_3x3";
		break;

	case Topia:
		height = 138.0f / 128.0f;
		texture = "Topias_T1_Heaven_4x4";
		break;

	case TrainingCenter:
		height = 102.0f / 95.0f;
		texture = "TC_T1_Heaven_3x3";
		break;

	case KarmaPortal:
		height = 102.0f / 95.0f;
		texture = "KA_Heaven_3x3";	
		break;
	}

	structure_list.emplace_back(std::make_unique<StructureSprite>(
		d11_device, Vector2(sqrt(2) * size, sqrt(2) * height * size), tile_position, size, texture));
	structure_list.back()->UpdateWorldMatrix();
}

/// <summary>
/// Destroy the structure at the given tile position
/// </summary>
/// <param name="tile_position">Tile position of the structure to be destroyed</param>
Vector3 BuildingManager::DestroyStructure(Vector3 tile_position)
{
	auto it = structure_list.begin();
	for (; it != structure_list.end(); it++)
	{
		for (auto& temp_pos : (*it)->GetOccupiedTiles())
		{
			if (temp_pos == tile_position)
			{
				Vector3 origin_point = (*(*it)->GetOccupiedTiles().begin());
				origin_point.y = (*it)->GetTileSize();
				structure_list.erase(it);
				return origin_point;
			}
		}
	}
	return Vector3(0,-1,0);
}

/// <summary>
/// Get the vector of occupied tiles that the structure on tile_position occupies
/// </summary>
/// <param name="tile_position">The position of the structure</param>
/// <returns>A Vector (C++ dynamic list) of Vector3 (x, y, z) that contains the occupied tiles</returns>
std::vector<Vector3> BuildingManager::GetStructureOccupiedTiles(Vector3 tile_position)
{
	auto it = structure_list.begin();
	for (; it != structure_list.end(); it++)
	{
		for (auto& temp_pos : (*it)->GetOccupiedTiles())
		{
			if (temp_pos == tile_position)
			{
				return (*it)->GetOccupiedTiles();
			}
		}
	}
}

/// <summary>
/// Get how many tiles a structure occupy
/// </summary>
/// <param name="structure_type">The type of structure</param>
/// <returns>Int of the size of the structure</returns>
int BuildingManager::GetSizeOfStructure(StructureType structure_type)
{
	switch (structure_type)
	{
	case Gate:
		return 3;

	case Topia:
		return 4;

	case TrainingCenter:
		return 3;

	case KarmaPortal:
		return 3;
	}
	return 0;
}
