#include "pch.h"
#include "GamePlay.h"

GamePlay::GamePlay()
= default;

GamePlay::~GamePlay()
{
    delete plane;
    delete cube;
    delete cone;
    
    delete ui_frame;
    delete windowImage;
    delete ui_panel;
    
}

bool GamePlay::init()
{
    // ui frame init
    ui_frame = new ImageGO2D("UIFrame",DataManager::GetD3DDevice());
    ui_frame->SetOrigin(Vector2(0,0));


    // ui window 
    windowImage = new ImageGO2D("Window",DataManager::GetD3DDevice());
    windowImage->SetOrigin(Vector2(0,0));
    windowImage->SetPos(Vector2(400,200));
    windowImage->SetScale(Vector2(0.5,0.5));

    ui_panel = new ImageGO2D("UIPanel",DataManager::GetD3DDevice());
    ui_panel->SetOrigin(Vector2(0,0));
    ui_panel->SetPos(Vector2(0,30));
    ui_panel->SetScale(Vector2(0.8,0.7));
        

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
    ui_panel->Draw(draw_data2D);

    // checks if window is open to render
    if (window_one_open)
    {
        windowImage->Draw(draw_data2D);
    }
}

void GamePlay::Render3D(DrawData* draw_data)
{
    plane->Draw(draw_data);
    cube->Draw(draw_data);
    cone->Draw(draw_data);
}


