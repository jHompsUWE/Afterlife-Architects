#pragma once
#include "VBQuad.h"
#include "ZoneType.h"

class Tile
{
public:
	Tile(ID3D11Device* GD, Vector3 _tile_pos, ZoneType zone_type);
	~Tile();

	void UpdateWorldMatrix();
	void Draw(DrawData* _DD);

	Vector3 GetTilePos();
	Vector3 GetStructureOrigin() { return structure_origin; }
	ZoneType GetZoneType() { return type; }
	bool IsTileOccupied() { return is_occupied; }

	void SetTexture(ZoneType zone_type);
	void SetZoneType(ZoneType _type) { type = _type; }
	void OccupyTile(Vector3 structure_origin_pos);
	void UnoccupyTile();

	std::string GetTextureOfType(ZoneType type);

protected:
	VBQuad* quad = nullptr;

	Vector3 tile_pos;
	Vector3 structure_origin;
	ZoneType type;
	bool is_occupied;

private:

};

