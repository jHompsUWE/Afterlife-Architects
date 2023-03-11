#pragma once
#include <stdlib.h>

#include "EconomyManager.h"

#include "StructureSprite.h"
#include "ZoneType.h"

class StructureGate : public StructureSprite
{
public:
	StructureGate(ID3D11Device* GD, Vector2 width_height, Vector3 tile_pos, int _tile_size, std::string texture, PlaneType _plane, float _soul_rate, EconomyManager* _econ_manager);
	~StructureGate();

	void TickStructure(GameData* game_data) override;

protected:

private:
	void AddSoulHeaven(float souls, ZoneType zone);
	void AddSoulHell(float souls, ZoneType zone);

	EconomyManager* econ_manager = nullptr;
	float soul_rate;
};

