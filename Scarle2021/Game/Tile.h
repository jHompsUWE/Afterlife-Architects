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

	void SetTexture(ZoneType zone_type);
	void SetZoneType(ZoneType _type) { type = _type; }

	std::string GetTextureOfType(ZoneType type);

protected:

private:
	VBQuad* quad = nullptr;
	Vector3 tile_pos;
	ZoneType type;
};

