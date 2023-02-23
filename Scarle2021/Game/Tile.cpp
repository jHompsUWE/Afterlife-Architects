#include "pch.h"
#include "Tile.h"

Tile::Tile(ID3D11Device* GD, Vector3 _tile_pos, std::string texture): tile_pos(_tile_pos)
{
	quad = new VBQuad(GD, texture);
	quad->SetPos(tile_pos);
}

Tile::~Tile()
{
	delete quad;
}

Vector3 Tile::GetTilePos()
{
	return tile_pos;
}

void Tile::Tick(GameData* game_data)
{
	quad->Tick(game_data);
}

void Tile::Draw(DrawData* _DD)
{
	quad->Draw(_DD);
}
