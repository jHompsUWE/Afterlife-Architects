#pragma once

#include <list>
#include <memory>
#include <iostream>
#include <math.h>
#include <vector>

#include "Tile.h"
#include "BuildingManager.h"

class Tilemap
{
public:
	Tilemap(ID3D11Device* GD, int _size);
	~Tilemap();

	void Tick(GameData* game_data);
	void Draw(DrawData* _DD);

	void BoxFill(std::unique_ptr<BuildingManager> & building_manager, ZoneType zone_type, Vector3 start, Vector3 end);
	bool SetTile(Vector3 tile_pos, ZoneType zone_type);
	Vector3 FindEmpty1x1TileOfType(ZoneType zone_type);
	Vector3 FindEmpty2x2TileOfType(ZoneType zone_type);
	bool IsTileOccupied(Vector3 tile_pos);
	void OccupyTile(Vector3 tile_pos, int _size);

protected:

private:
	std::vector<std::vector<std::unique_ptr<Tile>>> tilemap;
	float size;
};

