#pragma once
#include <memory>
#include <vector>
#include "StructureSprite.h"
#include "ZoneType.h"

class BuildingManager
{
public:
	BuildingManager(ID3D11Device* GD);
	~BuildingManager();

	void Tick(GameData* game_data);
	void Draw(DrawData* _DD);

	void Create1x1House(ZoneType zone_type, Vector3 tile_position);
	void Create2x2House(ZoneType zone_type, Vector3 tile_position);
	void DestroyStructure(Vector3 tile_position);
	std::vector<Vector3> GetStructureOccupiedTiles(Vector3 tile_position);

protected:

private:
	ID3D11Device* d11_device = nullptr;

	std::vector<std::unique_ptr<StructureSprite>> structure_list;

};

