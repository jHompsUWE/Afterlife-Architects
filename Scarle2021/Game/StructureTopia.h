#pragma once
#include "StructureSprite.h"

class StructureTopia : public StructureSprite
{
public:
	StructureTopia(ID3D11Device* GD, Vector2 width_height, Vector3 tile_pos, int _tile_size, std::string texture);
	~StructureTopia();

	void TickStructure(GameData* game_data) override;

protected:

private:

};
