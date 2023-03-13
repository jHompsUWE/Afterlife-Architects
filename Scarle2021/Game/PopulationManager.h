#pragma once
#include "ZoneType.h"
#include "PlaneType.h"
#include <vector>

class PopulationManager
{
public:
	PopulationManager();
	~PopulationManager();

	void IncrementZoneCapacity(PlaneType plane, ZoneType zone, int capacity_increase);
	void IncrementADCapacity(PlaneType plane, int capacity_increase);
	void SetZoneFull(PlaneType plane, ZoneType zone, bool is_full);

	int GetZoneCapacity(PlaneType plane, ZoneType zone);
	int GetADCapacity(PlaneType plane);
	bool GetZoneFull(PlaneType plane, ZoneType zone);

protected:

private:
	// Heaven
	std::vector<int> heaven_capacity;
	std::vector<bool> heaven_full;
	int capacity_angel;


	// Hell
	std::vector<int> hell_capacity;
	std::vector<bool> hell_full;
	int capacity_demon;
};

