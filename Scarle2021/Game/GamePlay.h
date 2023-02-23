#pragma once
#include "CMOGO.h"
#include "fileVBGO.h"
#include "StateTemplate.h"
#include "TextGO2D.h"
#include "GPGO.h"
#include "Button.h"
#include "UIWindow.h"

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
    
    CMOGO* plane = nullptr;
    FileVBGO* cube = nullptr;
    GPGO* cone = nullptr;
    
    TextGO2D* text = nullptr;

    ImageGO2D* ui_frame;
    ImageGO2D* ui_panel;

    //Button vector
    std::vector<UIButtonInterFace*> buttons;

    UIWindow* window_one;

    bool window_one_open = true;
};

