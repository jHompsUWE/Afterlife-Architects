#include "pch.h"
#include "PopulationManager.h"

PopulationManager::PopulationManager()
{
	// Heaven
	capacity_heaven_green = 0;
	capacity_heaven_yellow = 0;
	capacity_heaven_orange = 0;
	capacity_heaven_brown = 0;
	capacity_heaven_purple = 0;
	capacity_heaven_red = 0;
	capacity_heaven_blue = 0;
	capacity_angel = 0;

	// Hell
	capacity_hell_green = 0;
	capacity_hell_yellow = 0;
	capacity_hell_orange = 0;
	capacity_hell_brown = 0;
	capacity_hell_purple = 0;
	capacity_hell_red = 0;
	capacity_hell_blue = 0;
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
		switch (zone)
		{
		case Green:
			capacity_heaven_green += capacity_increase;
			break;

		case Yellow:
			capacity_heaven_yellow += capacity_increase;
			break;

		case Orange:
			capacity_heaven_orange += capacity_increase;
			break;

		case Brown:
			capacity_heaven_brown += capacity_increase;
			break;

		case Purple:
			capacity_heaven_purple += capacity_increase;
			break;

		case Red:
			capacity_heaven_red += capacity_increase;
			break;

		case Blue:
			capacity_heaven_blue += capacity_increase;
			break;

		default:
			break;
		}
		break;

	case Hell:
		switch (zone)
		{
		case Green:
			capacity_hell_green += capacity_increase;
			break;

		case Yellow:
			capacity_hell_yellow += capacity_increase;
			break;

		case Orange:
			capacity_hell_orange += capacity_increase;
			break;

		case Brown:
			capacity_hell_brown += capacity_increase;
			break;

		case Purple:
			capacity_hell_purple += capacity_increase;
			break;

		case Red:
			capacity_hell_red += capacity_increase;
			break;

		case Blue:
			capacity_hell_blue += capacity_increase;
			break;

		default:
			break;
		}
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

int PopulationManager::GetZoneCapacity(PlaneType plane, ZoneType zone)
{
	switch (plane)
	{
	case Heaven:
		switch (zone)
		{
		case Green:
			return capacity_heaven_green;

		case Yellow:
			return capacity_heaven_yellow;

		case Orange:
			return capacity_heaven_orange;

		case Brown:
			return capacity_heaven_brown;

		case Purple:
			return capacity_heaven_purple;

		case Red:
			return capacity_heaven_red;

		case Blue:
			return capacity_heaven_blue;

		default:
			return 0;
		}
		break;

	case Hell:
		switch (zone)
		{
		case Green:
			return capacity_hell_green;

		case Yellow:
			return capacity_hell_yellow;

		case Orange:
			return capacity_hell_orange;

		case Brown:
			return capacity_hell_brown;

		case Purple:
			return capacity_hell_purple;

		case Red:
			return capacity_hell_red;

		case Blue:
			return capacity_hell_blue;

		default:
			return 0;
		}
		break;
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
