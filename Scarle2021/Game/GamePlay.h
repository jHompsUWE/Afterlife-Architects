#pragma once
#include "CMOGO.h"
#include "fileVBGO.h"
#include "StateTemplate.h"
#include "TextGO2D.h"
#include "GPGO.h"

// Building System
#include "VBQuad.h"
#include "Tilemap.h"

#include "VBCube.h"

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
    Tilemap* tilemap = nullptr;
    
    TextGO2D* text = nullptr;

    bool do_once = true;

    Vector3 mouse_screen_pos;
    Vector3 mouse_world_pos;

    VBCube* cube = nullptr;
};

