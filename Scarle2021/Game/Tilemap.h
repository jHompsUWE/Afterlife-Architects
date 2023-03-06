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

	void Draw(DrawData* _DD, bool show_vibe);

	void BoxFill(std::unique_ptr<BuildingManager> & building_manager, ZoneType zone_type, Vector3 start, Vector3 end);
	bool SetTile(Vector3 tile_pos, ZoneType zone_type);
	Vector3 FindEmpty1x1TileOfType(ZoneType zone_type);
	Vector3 FindEmpty2x2TileOfType(ZoneType zone_type);
	bool IsTileOccupied(Vector3 tile_pos);
	void OccupyTile(Vector3 tile_pos, int _size);

	bool IsPosValid(Vector3 tile_pos);
	bool IsAreaValid(Vector3 start, int _size);

	//void VibeChange1x1(Vector3 tile_pos, int vibe_diff);
	//void VibeChange2x2(Vector3 tile_pos, int vibe_diff);
	//void VibeChange3x3(Vector3 tile_pos, int vibe_diff);
	void VibeChange(Vector3 tile_pos, int vibe_diff, int size);

protected:

private:
	std::vector<std::vector<std::unique_ptr<Tile>>> tilemap;
	float size; // Size of the tilemap
};

