#pragma once
#include "VBQuad.h"
#include "ZoneType.h"

class Tile
{
public:
	Tile(ID3D11Device* GD, Vector3 _tile_pos, ZoneType zone_type);
	~Tile();

	void Tick(GameData* game_data);
	void Draw(DrawData* _DD);

	Vector3 GetTilePos();
	ZoneType GetZoneType() { return type; }
	bool GetIsOccupied() { return is_occupied; }

	void SetTexture(ZoneType zone_type);
	void SetZoneType(ZoneType _type) { type = _type; }
	void SetIsOccupied(bool _is_occupied) { is_occupied = _is_occupied; }

	std::string GetTextureOfType(ZoneType type);

protected:

private:
	VBQuad* quad = nullptr;
	Vector3 tile_pos;
	ZoneType type;
	bool is_occupied;
};

