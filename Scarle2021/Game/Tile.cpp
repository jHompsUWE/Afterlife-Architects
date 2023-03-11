#include "pch.h"
#include "Tile.h"


Tile::Tile(ID3D11Device* GD, Vector3 _tile_pos, ZoneType zone_type): tile_pos(_tile_pos), type(zone_type)
{
	quad = new VBQuad(GD, 1, 1);
	quad->SetPos(tile_pos);

	structure_origin = Vector3(0, -1, 0);
	is_occupied = false;
}

Tile::~Tile()
{
	delete quad;
}

void Tile::UpdateWorldMatrix()
{
	quad->UpdateWorldMatrix();
}

void Tile::Draw(DrawData* _DD)
{
	quad->Draw(_DD);
}

Vector3 Tile::GetTilePos()
{
	return tile_pos;
}

void Tile::SetTexture(ID3D11ShaderResourceView* texture)
{
	quad->SetTexture(texture);
}

void Tile::OccupyTile(Vector3 structure_origin_pos)
{
	structure_origin = structure_origin_pos;
	is_occupied = true;
}

void Tile::UnoccupyTile()
{
	structure_origin = Vector3(0, -1, 0);
	is_occupied = false;
}
