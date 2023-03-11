#include "pch.h"
#include "StructureGate.h"

StructureGate::StructureGate(ID3D11Device* GD, Vector2 width_height, Vector3 tile_pos, int _tile_size, ID3D11ShaderResourceView* texture, PlaneType _plane, EconomyManager* _econ_manager, float _soul_rate) :
	StructureSprite(GD, width_height, tile_pos, _tile_size, texture, _plane), soul_rate(_soul_rate), econ_manager(_econ_manager)
{
}

StructureGate::~StructureGate()
{
}

void StructureGate::TickStructure(GameData* game_data)
{
	// Generate souls based on the soul_rate for a random zone in the plane this gate is in
	ZoneType zone = ZoneType(rand() % 7 + 1);
	switch (plane)
	{
	case Heaven:
		AddSoulHeaven(soul_rate, zone);
		break;

	case Hell:
		AddSoulHell(soul_rate, zone);
		break;
	}
}

void StructureGate::AddSoulHeaven(float souls, ZoneType zone)
{
	switch (zone)
	{
	case Green:
		econ_manager->SetSoulsHeavenGreen(econ_manager->GetSoulsHeavenGreen() + souls);
		break;

	case Yellow:
		econ_manager->SetSoulsHeavenYellow(econ_manager->GetSoulsHeavenYellow() + souls);
		break;

	case Orange:
		econ_manager->SetSoulsHeavenOrange(econ_manager->GetSoulsHeavenOrange() + souls);
		break;

	case Brown:
		econ_manager->SetSoulsHeavenBrown(econ_manager->GetSoulsHeavenBrown() + souls);
		break;

	case Purple:
		econ_manager->SetSoulsHeavenPurple(econ_manager->GetSoulsHeavenPurple() + souls);
		break;

	case Red:
		econ_manager->SetSoulsHeavenRed(econ_manager->GetSoulsHeavenRed() + souls);
		break;

	case Blue:
		econ_manager->SetSoulsHeavenBlue(econ_manager->GetSoulsHeavenBlue() + souls);
		break;

	default:
		break;
	}
}

void StructureGate::AddSoulHell(float souls, ZoneType zone)
{
	switch (zone)
	{
	case Green:
		econ_manager->SetSoulsHellGreen(econ_manager->GetSoulsHellGreen() + souls);
		break;

	case Yellow:
		econ_manager->SetSoulsHellYellow(econ_manager->GetSoulsHellYellow() + souls);
		break;

	case Orange:
		econ_manager->SetSoulsHellOrange(econ_manager->GetSoulsHellOrange() + souls);
		break;

	case Brown:
		econ_manager->SetSoulsHellBrown(econ_manager->GetSoulsHellBrown() + souls);
		break;

	case Purple:
		econ_manager->SetSoulsHellPurple(econ_manager->GetSoulsHellPurple() + souls);
		break;

	case Red:
		econ_manager->SetSoulsHellRed(econ_manager->GetSoulsHellRed() + souls);
		break;

	case Blue:
		econ_manager->SetSoulsHellBlue(econ_manager->GetSoulsHellBlue() + souls);
		break;

	default:
		break;
	}
}
