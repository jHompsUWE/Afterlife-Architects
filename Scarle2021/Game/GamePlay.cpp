#include "pch.h"
#include "GamePlay.h"

GamePlay::GamePlay()
= default;

GamePlay::~GamePlay()
{
    /*
    delete plane;
    delete cube;
    */

    delete quad;
}

bool GamePlay::init()
{
    text = new TextGO2D("this ist GAMEPLAYYY");
    text->SetPos(Vector2(100, 10));
    text->SetColour(Color((float*)&Colors::Yellow));

    /*
    plane = new CMOGO("Platform", DataManager::GetD3DDevice(), DataManager::GetEF());
    plane->SetPitch(1.57f);
    cube = new FileVBGO("cube", DataManager::GetD3DDevice());
    */

    quad = new VBQuad();
    quad->init(DataManager::GetD3DDevice());
    quad->SetPos(Vector3(0.0f, 0.0f, 0.0f));
    quad->SetPitch(3.142);

    /*
    float params[3];
    params[0] = params[1] = 20.0f; params[2] = (size_t)32;
    cone = new GPGO(DataManager::GetD3DContext(), GPGO_CONE, (float*)&Colors::Navy,params);
    //Cone->SetPos(Vector3(-50.0f, 10.0f, -70.f));
    */
    
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

    //constantly moves 

    /*
    plane->SetYaw(plane->GetYaw() + 0.01);
    
    plane->Tick(game_data);
    cube->Tick(game_data);
    cone->Tick(game_data);
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
    /*
    plane->Draw(draw_data);
    cube->Draw(draw_data);
    cone->Draw(draw_data);
    */

    quad->Draw(draw_data);
}


