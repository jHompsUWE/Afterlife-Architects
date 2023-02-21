#include "pch.h"
#include "GamePlay.h"

GamePlay::GamePlay()
= default;

GamePlay::~GamePlay()
{
    delete quad;
}

bool GamePlay::init()
{
    text = new TextGO2D("this ist GAMEPLAYYY");
    text->SetPos(Vector2(100, 10));
    text->SetColour(Color((float*)&Colors::Yellow));

    quad = new VBQuad(DataManager::GetD3DDevice(), "Tile_Purple");
    quad->SetPos(Vector3(0.0f, 0.0f, 0.0f));
    quad->SetPitch(3.142);
    
    return true;
}

void GamePlay::Update(GameData* game_data)
{
    /*
    * Changing texture on runtime
    if (!a)
    {
        quad->SetTexture(DataManager::GetD3DDevice(), "Tile_Lava");
        a = true;
    }
    */
}

void GamePlay::ScaledUpdate(GameData* game_data, float& scaled_dt)
{
}

void GamePlay::LateUpdate(GameData* game_data)
{
}

void GamePlay::GetEvents(std::list<AfterlifeEvent>& event_list)
{
}

void GamePlay::Render2D(DrawData2D* draw_data2D)
{
    text->Draw(draw_data2D);
}

void GamePlay::Render3D(DrawData* draw_data)
{
    quad->Draw(draw_data);
}


