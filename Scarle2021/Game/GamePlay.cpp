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

    delete open_window_1;
    
}

bool GamePlay::init()
{
    // ui frame init
    ui_frame = new ImageGO2D("UIFrame",DataManager::GetD3DDevice());
    ui_frame->SetOrigin(Vector2(0,0));
    ui_frame->SetScale(Vector2(1,1));


    // ui window 
    windowImage = new ImageGO2D("Window",DataManager::GetD3DDevice());
    windowImage->SetOrigin(Vector2(0,0));
    windowImage->SetPos(Vector2(400,200));
    windowImage->SetScale(Vector2(0.5,0.5));

    ui_panel = new ImageGO2D("UIPanel",DataManager::GetD3DDevice());
    ui_panel->SetOrigin(Vector2(0,0));
    ui_panel->SetPos(Vector2(0,30));
    ui_panel->SetScale(Vector2(0.8,0.7));

    // UI game play buttons
    open_window_1 = new Button(Vector2(109,37),DataManager::GetD3DDevice(),
        "Start Game","ButtonBackgroundMM",test_window,Vector2(0.5,0.5));
        

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
    // mouse pos
    auto mouse_pos = Vector2(game_data->mouse_state.x, game_data->mouse_state.y);
    
    //constantly moves 
    plane->SetYaw(plane->GetYaw() + 0.01);
    
    plane->Tick(game_data);
    cube->Tick(game_data);
    cone->Tick(game_data);

    //updates buttons
    open_window_1->update(game_data,mouse_pos);
}

void GamePlay::ScaledUpdate(GameData* game_data, float& scaled_dt)
{
}

void GamePlay::LateUpdate(GameData* game_data)
{
}

void GamePlay::GetEvents(std::list<AfterlifeEvent>& event_list)
{
    for (auto& ev : event_list)
    {
        switch (ev)
        {
        case none:
            std::cout << "soooos" << std::endl;
            break;
            
        case test_window:
            window_one_open = !window_one_open; 
            break;
            
        case enter_main_menu:
            break;
            
        case input_left:
            break;
            
        case input_right:
            break;

        case game_resized:
            ResizeUI();
            break;
            
        default:
            break;
        }
    }
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

    open_window_1->render(draw_data2D);
}

void GamePlay::Render3D(DrawData* draw_data)
{
    plane->Draw(draw_data);
    cube->Draw(draw_data);
    cone->Draw(draw_data);
}
void GamePlay::ResizeUI()
{
    ui_frame->ReSize(DataManager::GetRES().first, DataManager::GetRES().second);
    windowImage->ReSize(DataManager::GetRES().first, DataManager::GetRES().second);
    ui_panel->ReSize(DataManager::GetRES().first, DataManager::GetRES().second);
}

