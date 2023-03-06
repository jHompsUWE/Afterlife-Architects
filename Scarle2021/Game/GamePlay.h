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
#include "BuildingSystem.h"
#include "Raycast.h"

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

private:
    void ResizeUI();

    // Mouse
    void UpdateMousePos(DrawData* draw_data);
    Vector2 screen_size;
    
    // Building System
    std::unique_ptr<BuildingSystem> building_system;

    TextGO2D* text = nullptr;

    Vector3 mouse_screen_pos;
    std::shared_ptr<Vector3> mouse_world_pos;

    ImageGO2D* ui_frame;
    UIWindow* window_one;
    UIPanel* main_panel;
    AdvisorWindow* advisor_window;

    bool window_one_open = false;

    std::unique_ptr<AdvisorManager> adv_man = nullptr;

    EconomyManager* economy_manager;
};

