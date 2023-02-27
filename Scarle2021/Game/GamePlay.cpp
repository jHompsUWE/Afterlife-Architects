#include "pch.h"
#include "GamePlay.h"

#include "UIPanel.h"

GamePlay::GamePlay()
= default;

GamePlay::~GamePlay()
{
    delete plane;
    delete cube;
    delete cone;
    delete ui_frame;
    delete window_one;
}

bool GamePlay::init()
{
    // window init

    window_one = new UIWindow(Vector2(*DataManager::GetRES().first*0.5,*DataManager::GetRES()
        .second*0.5),DataManager::GetD3DDevice(),"","Window",Vector2(0.5,0.5));

    main_panel = new UIPanel(Vector2(0,30),DataManager::GetD3DDevice(),"UIPanel",Vector2(1,1)); 
    // ui frame init
    ui_frame = new ImageGO2D("UIFrame",DataManager::GetD3DDevice());
    ui_frame->SetOrigin(Vector2(0,0));
    ui_frame->SetScale(Vector2(1,1));
    
    plane = new CMOGO("Platform", DataManager::GetD3DDevice(), DataManager::GetEF());
    plane->SetPitch(1.57f);
    cube = new FileVBGO("cube", DataManager::GetD3DDevice());

    float params[3];
    params[0] = params[1] = 20.0f; params[2] = (size_t)32;
    cone = new GPGO(DataManager::GetD3DContext(), GPGO_CONE, (float*)&Colors::Navy,params);
    //Cone->SetPos(Vector3(-50.0f, 10.0f, -70.f));

    adv_man = std::make_unique<AdvisorManager>();
    adv_man->init();

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

    //update window
    window_one->update(game_data,mouse_pos);
    
    //updates panel
    main_panel->update(game_data,mouse_pos);
    
   

    adv_man->Update(game_data);
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
            
        case window_1_green:
            window_one_open = !window_one_open;
         
            break;
            
        case enter_main_menu:
            break;
            
        case input_left:
            break;

        case game_resized:
            ResizeUI();
            break;
             
        case input_right:
            DataManager::GetGD()->current_game_state = gs_game_over;
            break;
            
        default:
            break;
        }
    }
}

void GamePlay::Render2D(DrawData2D* draw_data2D)
{
    ui_frame->Draw(draw_data2D);

    //renders panel
    main_panel->render(draw_data2D);
    
    // checks if window is open to render
    if (window_one_open)
    {
        //render window
        window_one->render(draw_data2D);
    }
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
    window_one->reSize(DataManager::GetRES());
    main_panel->reSize(DataManager::GetRES());
}

