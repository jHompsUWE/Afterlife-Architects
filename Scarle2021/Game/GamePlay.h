#pragma once
#include "CMOGO.h"
#include "fileVBGO.h"
#include "StateTemplate.h"
#include "AdvisorManager.h"
#include "TextGO2D.h"
#include "GPGO.h"
//UI systems
#include "UIPanel.h"
#include "UIWindow.h"
#include "SoulViewWindow.h"
#include "KarmaStationWindow.h"
#include "TopiasWindowUI.h"
//
#include "EconomyManager.h"

// Building System
#include "BuildingSystem.h"
#include "Raycast.h"
#include "TopiasWindowUI.h"
#include "TrainingCentersWindow.h"

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
    void GetEvents(const AL::Event& al_event) override;

    //Renders
    void Render2D(DrawData2D* draw_data2D) override;
    void Render3D(DrawData* draw_data) override;

private:
    void ResizeUI();

    bool do_once;

    // Mouse
    void UpdateMousePos(DrawData* draw_data);
    Vector2 screen_size;
    
    // Building System
    std::unique_ptr<BuildingSystem> building_system;

    TextGO2D* text = nullptr;

    Vector3 mouse_screen_pos;
    std::shared_ptr<Vector3> mouse_world_pos;

    //ui Boarder
    ImageGO2D* ui_frame;
    
    //main build panel
    UIPanel* main_panel;
    
    // UI windows
    UIWindow* window_one_gate;
    KarmaStationWindow* window_two_kara_station;
    AdvisorWindow* advisor_window;
    TopiasWindowUI* window_three_topias;
    TrainingCentersWindow* window_four_training_centers_window;
    SoulViewWindow* soul_view;

    bool window_one_open = false;

    std::unique_ptr<AdvisorManager> adv_man = nullptr;
};

