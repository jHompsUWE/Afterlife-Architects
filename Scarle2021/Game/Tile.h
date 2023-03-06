#pragma once
#include "VBQuad.h"
#include "ZoneType.h"

class Tile
{
public:
	Tile(ID3D11Device* GD, Vector3 _tile_pos, ZoneType zone_type);
	~Tile();

	void Tick();
	void Draw(DrawData* _DD, bool show_vibe);

	Vector3 GetTilePos();
	ZoneType GetZoneType() { return type; }
	bool GetIsOccupied() { return is_occupied; }

	void SetTexture(ZoneType zone_type);
	void SetZoneType(ZoneType _type) { type = _type; }
	void SetIsOccupied(bool _is_occupied) { is_occupied = _is_occupied; }

	std::string GetTextureOfType(ZoneType type);

	void ChangeVibe(int vibe_diff);

protected:

private:
	VBQuad* quad = nullptr;
	VBQuad* vibe_quad = nullptr;
	Vector3 tile_pos;
	ZoneType type;
	bool is_occupied;
	int vibe_value = 0;
	float colour_scaling = 0.5;
};

