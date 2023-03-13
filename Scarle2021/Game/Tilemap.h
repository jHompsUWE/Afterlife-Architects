#pragma once

#include <list>
#include <memory>
#include <iostream>
#include <math.h>
#include <vector>

#include "Tile.h"
#include "BuildingManager.h"
#include "VibeTilemap.h"
#include "TextureManager.h"
#include "PlaneType.h"

class Tilemap
{
public:
	Tilemap(ID3D11Device* GD, std::shared_ptr<TextureManager> _texture_manager, std::shared_ptr<PopulationManager> _population_manager,
		int _size, Vector3 _start, PlaneType _plane);
	~Tilemap();

	void Draw(DrawData* _DD);

	void BoxFill(std::unique_ptr<BuildingManager>& building_manager, std::unique_ptr<VibeTilemap>& vibe_tilemap,
		ZoneType zone_type, Vector3 start, Vector3 end);
	bool SetTile(Vector3 tile_pos, ZoneType zone_type);
	Vector3 FindEmpty1x1TileOfType(ZoneType zone_type);
	Vector3 FindEmpty2x2TileOfType(ZoneType zone_type);
	bool IsTileOccupied(Vector3 tile_pos);
	void OccupyTile(Vector3 tile_pos, int _size);

	ZoneType GetActiveZone(ZoneType zone_type);
	ZoneType GetInactiveZone(ZoneType zone_type);

	bool IsPosValid(Vector3 tile_pos);
	bool IsAreaValid(Vector3 start, int _size);
	bool IsRoadNearby(Vector3 tile_pos);
	bool CanTileBeReplaced(ZoneType zone_type);
	void ActivateNearbyTile(Vector3 tile_pos);
	void DeactivateNearbyTile(Vector3 tile_pos);

	Vector3 WorldToLocalPos(Vector3 world_pos);
	Vector3 LocalToWorldPos(Vector3 local_pos);

protected:
	std::vector<std::vector<std::unique_ptr<Tile>>> tilemap;
	float size; // Size of the tilemap
	Vector3 start; // Starting/Origin point of the tilemap
	PlaneType plane;

private:
	std::shared_ptr<TextureManager> texture_manager;
	std::shared_ptr<PopulationManager> population_manager;
};

