#include "pch.h"
#include "GamePlay.h"

GamePlay::GamePlay()
= default;

GamePlay::~GamePlay()
{
    delete plane;
    delete cube;
    delete ui_frame;
}

bool GamePlay::init()
{
    //text = new TextGO2D("this ist GAMEPLAYYY");
    //text->SetPos(Vector2(100, 10));
    //text->SetColour(Color((float*)&Colors::Yellow));

    ui_frame = new ImageGO2D("UIFrame",DataManager::GetD3DDevice());
    ui_frame->SetOrigin(Vector2(0,0));

    plane = new CMOGO("Platform", DataManager::GetD3DDevice(), DataManager::GetEF());
    plane->SetPitch(1.57f);
    cube = new FileVBGO("cube", DataManager::GetD3DDevice());

    float params[3];
    params[0] = params[1] = 20.0f; params[2] = (size_t)32;
    cone = new GPGO(DataManager::GetD3DContext(), GPGO_CONE, (float*)&Colors::Navy,params);
    //Cone->SetPos(Vector3(-50.0f, 10.0f, -70.f));
    
    return true;
}

void GamePlay::Update(GameData* game_data)
{
    //constantly moves 
    plane->SetYaw(plane->GetYaw() + 0.01);
    
    plane->Tick(game_data);
    cube->Tick(game_data);
    cone->Tick(game_data);
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
    //text->Draw(draw_data2D);
    ui_frame->Draw(draw_data2D);
}

void GamePlay::Render3D(DrawData* draw_data)
{
    plane->Draw(draw_data);
    cube->Draw(draw_data);
    cone->Draw(draw_data);
}


