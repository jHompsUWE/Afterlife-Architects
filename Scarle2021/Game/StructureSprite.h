#pragma once
#include "VBQuad.h"
#include <vector>
#include <memory>

class StructureSprite : public VBQuad
{
public:
	StructureSprite(ID3D11Device* GD, Vector2 width_height, Vector3 tile_pos, int _tile_size, std::string texture);
	~StructureSprite();

	virtual void TickStructure(GameData* game_data) {}

	std::vector<Vector3> GetOccupiedTiles() { return occupied_tiles; }
	int GetTileSize() { return tile_size; }

protected:
	void AddOccupiedTiles(Vector3 tile_pos, int tile_size);

private:
	const float PI = 3.141592653589793238462643383279502884197169399375105820974944;
	std::vector<Vector3> occupied_tiles; //Tiles occupied by this structure
	int tile_size;
};

