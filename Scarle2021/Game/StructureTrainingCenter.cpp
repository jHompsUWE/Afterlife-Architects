#include "pch.h"
#include "StructureTrainingCenter.h"

StructureTrainingCenter::StructureTrainingCenter(ID3D11Device* GD, Vector2 width_height, Vector3 tile_pos, int _tile_size, ID3D11ShaderResourceView* texture,
	PlaneType _plane, EconomyManager* _econ_manager, std::shared_ptr<PopulationManager> _population_manager, float _conversion_rate):
	StructureSprite(GD, width_height, tile_pos, _tile_size, texture, _plane), econ_manager(_econ_manager), 
	population_manager(_population_manager), conversion_rate(_conversion_rate)
{
}

StructureTrainingCenter::~StructureTrainingCenter()
{
}

void StructureTrainingCenter::TickStructure(GameData* game_data)
{
	// Check if capacity for Angels/Demons is full
	switch (plane)
	{
	case Heaven:
		if ((econ_manager->GetAngels() + conversion_rate) <= population_manager->GetADCapacity(Heaven))
		{
			// Heaven Angels capacity is NOT full

			// Select a random soul type to convert
			ZoneType zone = ZoneType(rand() % 7 + 1);

			if (IsSoulHeavenGreater(conversion_rate, zone))
			{
				// There is enough soul to be converted
				AddSoulHeaven(-conversion_rate, zone);
				econ_manager->SetAngels(econ_manager->GetAngels() + conversion_rate);
			}
		}
		break;

	case Hell:
		if ((econ_manager->GetDemons() + conversion_rate) < population_manager->GetADCapacity(Hell))
		{
			// Hell Angels capacity is NOT full

			// Select a random soul type to convert
			ZoneType zone = ZoneType(rand() % 7 + 1);

			if (IsSoulHellGreater(conversion_rate, zone))
			{
				// There is enough soul to be converted
				AddSoulHell(-conversion_rate, zone);
				econ_manager->SetDemons(econ_manager->GetDemons() + conversion_rate);
			}
		}
		break;
	}
}

bool StructureTrainingCenter::IsSoulHeavenGreater(float souls, ZoneType zone)
{
	switch (zone)
	{
	case Green:
		if (econ_manager->GetSoulsHeavenGreen() >= souls)
		{
			return true;
		}

	case Yellow:
		if (econ_manager->GetSoulsHeavenYellow() >= souls)
		{
			return true;
		}

	case Orange:
		if (econ_manager->GetSoulsHeavenOrange() >= souls)
		{
			return true;
		}

	case Brown:
		if (econ_manager->GetSoulsHeavenBrown() >= souls)
		{
			return true;
		}

	case Purple:
		if (econ_manager->GetSoulsHeavenPurple() >= souls)
		{
			return true;
		}

	case Red:
		if (econ_manager->GetSoulsHeavenRed() >= souls)
		{
			return true;
		}

	case Blue:
		if (econ_manager->GetSoulsHeavenBlue() >= souls)
		{
			return true;
		}

	default:
		break;
	}
	return false;
}

bool StructureTrainingCenter::IsSoulHellGreater(float souls, ZoneType zone)
{
	switch (zone)
	{
	case Green:
		if (econ_manager->GetSoulsHeavenGreen() >= souls)
		{
			return true;
		}

	case Yellow:
		if (econ_manager->GetSoulsHeavenYellow() >= souls)
		{
			return true;
		}

	case Orange:
		if (econ_manager->GetSoulsHeavenOrange() >= souls)
		{
			return true;
		}

	case Brown:
		if (econ_manager->GetSoulsHeavenBrown() >= souls)
		{
			return true;
		}

	case Purple:
		if (econ_manager->GetSoulsHeavenPurple() >= souls)
		{
			return true;
		}

	case Red:
		if (econ_manager->GetSoulsHeavenRed() >= souls)
		{
			return true;
		}

	case Blue:
		if (econ_manager->GetSoulsHeavenBlue() >= souls)
		{
			return true;
		}

	default:
		break;
	}
	return false;
}

void StructureTrainingCenter::AddSoulHeaven(float souls, ZoneType zone)
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

void StructureTrainingCenter::AddSoulHell(float souls, ZoneType zone)
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
