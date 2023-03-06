#pragma once

#include "GameData.h"
#include "EventManager.h"

#include "Tilemap.h"
#include "PreviewQuad.h"
#include "BuildingManager.h"

class BuildingSystem
{
public:
	BuildingSystem(std::shared_ptr<Vector3> mouse_pos, ID3D11Device* GD);
	~BuildingSystem();

	void Tick(GameData* game_data);
	void GetEvents(std::list<AfterlifeEvent>& event_list);
	void Render3D(DrawData* draw_data);

protected:

private:
	void TryCreateHouse();
	void CreateStructure(StructureType structure_type);

	std::shared_ptr<Vector3> mouse_world_pos;
	ID3D11Device* d11_device = nullptr;

	// Player
	StructureType selected_structure;
	ZoneType selected_zone;

	// Mouse
	bool mouse_pressed;
	Vector3 mouse_pressed_pos;
	Vector3 mouse_released_pos;

	// Tilemap
	std::unique_ptr<Tilemap> tilemap;
	bool show_vibes = false;

	// Preview Quad
	bool show_preview_quad;
	std::unique_ptr<PreviewQuad> preview_quad;

	// Buildings
	std::unique_ptr<BuildingManager> building_manager;
};

