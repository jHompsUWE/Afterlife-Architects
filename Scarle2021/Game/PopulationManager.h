#pragma once
#include "ZoneType.h"
#include "PlaneType.h"

class PopulationManager
{
public:
	PopulationManager();
	~PopulationManager();

	void IncrementZoneCapacity(PlaneType plane, ZoneType zone, int capacity_increase);
	void IncrementADCapacity(PlaneType plane, int capacity_increase);

	int GetZoneCapacity(PlaneType plane, ZoneType zone);
	int GetADCapacity(PlaneType plane);

protected:

private:
	// Heaven
	int capacity_heaven_green;
	int capacity_heaven_yellow;
	int capacity_heaven_orange;
	int capacity_heaven_brown;
	int capacity_heaven_purple;
	int capacity_heaven_red;
	int capacity_heaven_blue;
	int capacity_angel;

	// Hell
	int capacity_hell_green;
	int capacity_hell_yellow;
	int capacity_hell_orange;
	int capacity_hell_brown;
	int capacity_hell_purple;
	int capacity_hell_red;
	int capacity_hell_blue;
	int capacity_demon;
};

