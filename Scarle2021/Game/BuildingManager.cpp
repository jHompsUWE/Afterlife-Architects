#include "pch.h"
#include "BuildingManager.h"
#include <iostream>

BuildingManager::BuildingManager(ID3D11Device* GD, int _size, Vector3 _start): d11_device(GD), start(_start)
{
	for (int x = 0; x < _size; x++)
	{
		structure_map.emplace_back();
		for (int y = 0; y < _size; y++)
		{
			structure_map[x].emplace_back(nullptr);
		}
	}
}

BuildingManager::~BuildingManager()
{
}

void BuildingManager::Tick(GameData* game_data)
{
	for (auto& x : structure_map)
	{
		for (auto& y : x)
		{
			if (y)
			{
				y->TickStructure(game_data);
			}
		}
	}
}

void BuildingManager::Draw(DrawData* _DD)
{
	for (auto& x : structure_map)
	{
		for (auto& y : x)
		{
			if (y)
			{
				y->Draw(_DD);
			}
		}
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
	structure_map[tile_position.x][tile_position.z] =
		std::make_unique<StructureSprite>(d11_device, Vector2(sqrt(2), sqrt(2) * height), tile_position + start, 1, texture);
	structure_map[tile_position.x][tile_position.z]->UpdateWorldMatrix();
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
	structure_map[tile_position.x][tile_position.z] =
		std::make_unique<StructureSprite>(d11_device, Vector2(sqrt(2) * 2, sqrt(2) * height * 2), tile_position + start, 2, texture);
	structure_map[tile_position.x][tile_position.z]->UpdateWorldMatrix();
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
	int size = GetSizeOfStructure(structure_type);
	std::string texture;

	switch (structure_type)
	{
	case Gate:
		height = 90.0f / 95.0f;
		texture = "Gate_T1_Heaven_3x3";

		// Create StructureGate derived from StructureSprite base class
		structure_map[tile_position.x][tile_position.z] =
			std::make_unique<StructureGate>(d11_device, Vector2(sqrt(2) * size, sqrt(2) * height * size), tile_position + start, size, texture);
		break;

	case Topia:
		height = 138.0f / 128.0f;
		texture = "Topias_T1_Heaven_4x4";

		// Create StructureTopia derived from StructureSprite base class
		structure_map[tile_position.x][tile_position.z] =
			std::make_unique<StructureTopia>(d11_device, Vector2(sqrt(2) * size, sqrt(2) * height * size), tile_position + start, size, texture);
		break;

	case TrainingCenter:
		height = 102.0f / 95.0f;
		texture = "TC_T1_Heaven_3x3";

		// Create StructureTrainingCenter derived from StructureSprite base class
		structure_map[tile_position.x][tile_position.z] =
			std::make_unique<StructureTrainingCenter>(d11_device, Vector2(sqrt(2) * size, sqrt(2) * height * size), tile_position + start, size, texture);
		break;
	}

	structure_map[tile_position.x][tile_position.z]->UpdateWorldMatrix();
}

/// <summary>
/// Destroy the structure at the given tile position
/// </summary>
/// <param name="tile_position">Tile position of the structure to be destroyed</param>
void BuildingManager::DestroyStructure(Vector3 tile_position)
{
	if (structure_map[tile_position.x][tile_position.z])
	{
		structure_map[tile_position.x][tile_position.z] = nullptr;
	}
}

/// <summary>
/// Get the vector of occupied tiles that the structure on tile_position occupies
/// </summary>
/// <param name="tile_position">The position of the structure</param>
/// <returns>A Vector (C++ dynamic list) of Vector3 (x, y, z) that contains the occupied tiles</returns>
std::vector<Vector3> BuildingManager::GetStructureOccupiedTiles(Vector3 tile_position)
{
	if (structure_map[tile_position.x][tile_position.z])
	{
		return structure_map[tile_position.x][tile_position.z]->GetOccupiedTiles();
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
	}

	return 0;
}
