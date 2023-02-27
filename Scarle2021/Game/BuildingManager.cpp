#include "pch.h"
#include "BuildingManager.h"

BuildingManager::BuildingManager(ID3D11Device* GD): d11_device(GD)
{
}

BuildingManager::~BuildingManager()
{
}

void BuildingManager::Tick(GameData* game_data)
{
	for (auto& structure : structure_list)
	{
		structure->Tick(game_data);
	}
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
/// <param name="zone_type">ZoneType fo the house to be built</param>
/// <param name="tile_position">Tile position of the house</param>
void BuildingManager::Create1x1House(ZoneType zone_type, Vector3 tile_position)
{
	// height value is calculated by dividing the texture height with witdh
	// all the values below are set manually because division on runtime gives incorrect values
	float height = 0;
	std::string texture;

	switch (zone_type)
	{
	case Green:
		height = 1.1875;
		texture = "Building_Green_Heaven_1x1";
		break;

	case Yellow:
		height = 2.625;
		texture = "Building_Yellow_Heaven_1x1";
		break;

	case Orange:
		height = 1;
		texture = "Building_Orange_Heaven_1x1";
		break;

	case Brown:
		height = 1.03125;
		texture = "Building_Brown_Heaven_1x1";
		break;

	case Purple:
		height = 1.625;
		texture = "Building_Purple_Heaven_1x1";
		break;

	case Red:
		height = 1.21875;
		texture = "Building_Red_Heaven_1x1";
		break;

	case Blue:
		height = 1.53125;
		texture = "Building_Blue_Heaven_1x1";
		break;

	default:
		break;
	}

	// sqrt(2) is the size of the quad needed to fit structure to a 1x1 unit isometric tile
	structure_list.emplace_back(std::make_unique<StructureSprite>(d11_device, Vector2(sqrt(2), sqrt(2) * height), tile_position, texture));
}

/// <summary>
/// Destroy the structure at the given tile position
/// </summary>
/// <param name="tile_position">Tile position of the structure to be destroyed</param>
void BuildingManager::DestroyStructure(Vector3 tile_position)
{
	auto it = structure_list.begin();
	for (; it != structure_list.end(); it++)
	{
		if ((*it)->GetTilePos() == tile_position)
		{
			structure_list.erase(it);
			return;
		}
	}
}
