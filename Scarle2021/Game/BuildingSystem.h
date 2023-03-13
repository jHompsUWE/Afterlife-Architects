#pragma once

#include "GameData.h"
#include "NewEventManager.h"

#include "Tilemap.h"
#include "VibeTilemap.h"
#include "PreviewQuad.h"
#include "BuildingManager.h"
#include "TextureManager.h"

#include "PlaneAssembler.h"

class BuildingSystem : public IEventReceiver
{
public:
	BuildingSystem(std::shared_ptr<Vector3> mouse_pos, ID3D11Device* GD);
	~BuildingSystem() override;

	void Tick(GameData* game_data);
	void ReceiveEvents(const AL::Event& al_event) override;
	void Render3D(DrawData* draw_data);

	PlaneType GetPositionPlane(Vector3 position);

private:
	void GenerateTerrain(std::unique_ptr<Tilemap>& tilemap, std::unique_ptr<VibeTilemap>& vibe, std::unique_ptr<BuildingManager>& building_manager, PlaneType plane);

	Vector3 ClampMouseToAxis(Vector3 start, Vector3 end);

	bool TryCreateHouse(std::unique_ptr<Tilemap>& tilemap, std::unique_ptr<VibeTilemap>& vibe, std::unique_ptr<BuildingManager>& building_manager, ZoneType zone);
	void StartCreateStructure(StructureType structure_type);
	void PlaceSelectedStructure(PlaneType plane);

	bool SoulExceedsCapacity(PlaneType plane, ZoneType zone);

	bool CallEverySeconds(float dt, float time_interval);

	void CursorIntegration();

	std::shared_ptr<Vector3> mouse_world_pos{};
	ID3D11Device* d11_device = nullptr;

	// Timer
	float timer;

	// Player
	StructureType selected_structure;
	ZoneType selected_zone;

	// Mouse
	bool mouse_state;
	bool mouse_pressed;
	Vector3 mouse_pressed_world_pos;
	Vector3 mouse_released_world_pos;

	Vector3 mouse_pressed_heaven_pos;
	Vector3 mouse_released_heaven_pos;

	Vector3 mouse_pressed_hell_pos;
	Vector3 mouse_released_hell_pos;

	// Heaven
	std::unique_ptr<Tilemap> tilemap_heaven{};
	std::unique_ptr<VibeTilemap> vibe_tilemap_heaven{};
	std::unique_ptr<BuildingManager> building_manager_heaven{};

	// Hell
	std::unique_ptr<Tilemap> tilemap_hell{};
	std::unique_ptr<VibeTilemap> vibe_tilemap_hell{};
	std::unique_ptr<BuildingManager> building_manager_hell{};

	bool show_vibes = false;

	std::shared_ptr<TextureManager> texture_manager{};
	std::shared_ptr<PopulationManager> population_manager{};
	EconomyManager* econ_manager = nullptr;

	// Preview Quad
	bool show_preview_quad;
	std::unique_ptr<PreviewQuad> preview_quad{};
};

