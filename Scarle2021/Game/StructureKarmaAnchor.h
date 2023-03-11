#pragma once
#include "StructureSprite.h"

class StructureKarmaAnchor : public StructureSprite
{
public:
	StructureKarmaAnchor(ID3D11Device* GD, Vector2 width_height, Vector3 tile_pos, int _tile_size, ID3D11ShaderResourceView* texture,
		PlaneType _plane);
	~StructureKarmaAnchor();

	void TickStructure(GameData* game_data) override;

protected:

private:
};

