#include "pch.h"
#include "StructureSprite.h"

StructureSprite::StructureSprite(ID3D11Device* GD, Vector2 width_height, Vector3 tile_pos, std::string texture) 
	: VBQuad(GD, width_height.x, width_height.y), pos(tile_pos)
{
	SetPitch(-30 * PI / 180);
	SetYaw(45 * PI / 180);
	SetPos(pos + Vector3(-0.5 + 0.1, 0, 0.5 + 0.1));
	SetTexture(texture);
}

StructureSprite::~StructureSprite()
{
}
