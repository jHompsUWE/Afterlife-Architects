#pragma once
#include "VBQuad.h"

class Tile
{
public:
	Tile(ID3D11Device* GD, Vector3 _tile_pos, std::string texture);
	~Tile();

	Vector3 GetTilePos();

	void Tick(GameData* game_data);
	void Draw(DrawData* _DD);

protected:

private:
	VBQuad* quad = nullptr;
	Vector3 tile_pos;
};

