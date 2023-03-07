#pragma once
#include <memory>
#include <vector>

#include "StructureSprite.h"
#include "ZoneType.h"
#include "StructureType.h"

class BuildingManager
{
public:
	BuildingManager(ID3D11Device* GD, int _size, Vector3 _start);
	~BuildingManager();

	void Draw(DrawData* _DD);

	void Create1x1House(ZoneType zone_type, Vector3 tile_position);
	void Create2x2House(ZoneType zone_type, Vector3 tile_position);
	void CreateStructure(StructureType structure_type, Vector3 tile_position);
	void DestroyStructure(Vector3 tile_position);
	std::vector<Vector3> GetStructureOccupiedTiles(Vector3 tile_position);

	static int GetSizeOfStructure(StructureType structure_type);

protected:

private:
	ID3D11Device* d11_device = nullptr;
	Vector3 start;
	std::vector<std::vector<std::unique_ptr<StructureSprite>>> structure_map;

};

