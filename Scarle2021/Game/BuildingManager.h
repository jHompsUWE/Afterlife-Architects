#pragma once
#include <memory>
#include <vector>

#include "ZoneType.h"
#include "PlaneType.h"
#include "StructureType.h"

#include "PopulationManager.h"
#include "TextureManager.h"
#include "EconomyManager.h"

#include "StructureGate.h"
#include "StructureTopia.h"
#include "StructureTrainingCenter.h"
#include "StructureBuilding.h"
#include "StructureKarmaAnchor.h"
#include "StructureKarmaStation.h"

class BuildingManager
{
public:
	BuildingManager(ID3D11Device* GD, std::shared_ptr<TextureManager> _texture_manager, int _size, Vector3 _start, PlaneType _plane);
	~BuildingManager();

	void Tick(GameData* game_data);
	void Draw(DrawData* _DD);

	void CreateStructure(StructureType structure_type, Vector3 tile_position);
	void DestroyStructure(Vector3 tile_position);
	std::vector<Vector3> GetStructureOccupiedTiles(Vector3 tile_position);

	static int GetSizeOfStructure(StructureType structure_type);

protected:

private:
	ID3D11Device* d11_device = nullptr;
	Vector3 start;
	std::vector<std::vector<std::unique_ptr<StructureSprite>>> structure_map;

	EconomyManager* econ_manager = nullptr;
	std::shared_ptr<PopulationManager> population_manager;
	std::shared_ptr<TextureManager> texture_manager;

	PlaneType plane;
};

