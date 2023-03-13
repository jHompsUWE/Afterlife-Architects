#include "pch.h"
#include "PopulationManager.h"

PopulationManager::PopulationManager()
{
	// Heaven
	heaven_capacity = std::vector<int>(7, 0);
	heaven_full = std::vector<bool>(7, true);
	capacity_angel = 0;

	// Hell
	hell_capacity = std::vector<int>(7, 0);
	hell_full = std::vector<bool>(7, true);
	capacity_demon = 0;
}

PopulationManager::~PopulationManager()
{
}

void PopulationManager::IncrementZoneCapacity(PlaneType plane, ZoneType zone, int capacity_increase)
{
	switch (plane)
	{
	case Heaven:
		heaven_capacity[(int)zone - 1] += capacity_increase;
		break;

	case Hell:
		hell_capacity[(int)zone - 1] += capacity_increase;
		break;
	}
}

void PopulationManager::IncrementADCapacity(PlaneType plane, int capacity_increase)
{
	switch (plane)
	{
	case Heaven:
		capacity_angel += capacity_increase;
		break;

	case Hell:
		capacity_demon += capacity_increase;
		break;
	}
}

void PopulationManager::SetZoneFull(PlaneType plane, ZoneType zone, bool is_full)
{
	switch (plane)
	{
	case Heaven:
		heaven_full[(int)zone - 1] = is_full;
		break;

	case Hell:
		hell_full[(int)zone - 1] = is_full;
		break;
	}
}

int PopulationManager::GetZoneCapacity(PlaneType plane, ZoneType zone)
{
	switch (plane)
	{
	case Heaven:
		return heaven_capacity[(int)zone - 1];

	case Hell:
		return hell_capacity[(int)zone - 1];
	}

	return 0;
}

int PopulationManager::GetADCapacity(PlaneType plane)
{
	switch (plane)
	{
	case Heaven:
		return capacity_angel;

	case Hell:
		return capacity_demon;
	}

	return 0;
}

bool PopulationManager::GetZoneFull(PlaneType plane, ZoneType zone)
{
	switch (plane)
	{
	case Heaven:
		return heaven_full[(int)zone - 1];

	case Hell:
		return hell_full[(int)zone - 1];
	}
}
