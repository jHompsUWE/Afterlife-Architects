#pragma once
#include "CMOGO.h"
#include "fileVBGO.h"
#include "StateTemplate.h"
#include "AdvisorManager.h"
#include "TextGO2D.h"
#include "GPGO.h"
#include "UIPanel.h"
#include "UIWindow.h"
#include "EconomyManager.h"

// Building System
#include "Tilemap.h"
#include "Raycast.h"
#include "PreviewQuad.h"
#include "BuildingManager.h"

class GPGO;

class GamePlay : public StateTemplate
{
public:
    GamePlay();
    ~GamePlay() override;

    bool init() override;

    //Update Cycles
    void Update(GameData* game_data) override;
    void ScaledUpdate(GameData* game_data, float& scaled_dt) override;
    void LateUpdate(GameData* game_data) override;

    //Events
    void GetEvents(std::list<AfterlifeEvent>& event_list) override;

    //Renders
    void Render2D(DrawData2D* draw_data2D) override;
    void Render3D(DrawData* draw_data) override;

    // Building System
    void TryCreateHouse();

private:
    std::unique_ptr<Tilemap> tilemap;
    std::unique_ptr<PreviewQuad> preview_quad;

    std::unique_ptr<BuildingManager> building_manager;
    void ResizeUI();
    
    TextGO2D* text = nullptr;

    bool do_once = true;

    bool mouse_pressed;
    Vector3 mouse_screen_pos;
    Vector3 mouse_world_pos;
    Vector3 mouse_pressed_pos;
    Vector3 mouse_released_pos;

    ZoneType selected_zone;

    ImageGO2D* ui_frame;
    
    UIWindow* window_one;
    
    UIPanel* main_panel;

    bool window_one_open = true;

    std::unique_ptr<AdvisorManager> adv_man = nullptr;

    EconomyManager* economy_manager;
};

