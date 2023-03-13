#include "pch.h"
#include "GamePlay.h"


GamePlay::GamePlay()
= default;

GamePlay::~GamePlay()
{
    delete ui_frame;
    delete window_one_gate;
    delete advisor_window;
    delete window_two_karma_station;
    delete window_three_topias;
    delete window_four_training_centers_window;
}

bool GamePlay::init()
{
    // window init
    window_one_gate = new UIWindow(Vector2(*DataManager::GetRES().first*0.5,*DataManager::GetRES()
        .second*0.5),DataManager::GetD3DDevice(),"","Window",Vector2(0.5,0.5));
    
    //build panel
    main_panel = new UIPanel(Vector2(0,30),DataManager::GetD3DDevice(),"UIPanel",Vector2(1,1));
    
    //advisor
    advisor_window = new AdvisorWindow(Vector2(675,30),DataManager::
        GetD3DDevice(),"","AdvisorBackground",Vector2(0.5,0.5));
    //advisor
    soul_view = new SoulViewWindow(Vector2(400,120),DataManager::
        GetD3DDevice(),"","SoulView",Vector2(1,1));
    //karma station
    window_two_karma_station = new KarmaStationWindow(Vector2(*DataManager::GetRES().first*0.5,*DataManager::GetRES()
        .second*0.5),DataManager::
        GetD3DDevice(),"","Window",Vector2(0.5,0.5));
    //topias
    window_three_topias = new TopiasWindowUI(Vector2(*DataManager::GetRES().first*0.5,*DataManager::GetRES()
        .second*0.5),DataManager::
        GetD3DDevice(),"","Window",Vector2(0.5,0.5));
    //training center
    window_four_training_centers_window = new TrainingCentersWindow(Vector2(*DataManager::GetRES().first*0.5,*DataManager::GetRES()
        .second*0.5),DataManager::
        GetD3DDevice(),"","Window",Vector2(0.5,0.5));
    
    // ui frame init
    ui_frame = new ImageGO2D("UIFrame",DataManager::GetD3DDevice());
    ui_frame->SetOrigin(Vector2(0,0));
    ui_frame->SetScale(Vector2(1,1));
    
    // Mouse
    mouse_screen_pos.z = 0;
    mouse_world_pos = std::make_shared<Vector3>(0, 0, 0);

    // Building System
    building_system = std::make_unique<BuildingSystem>(mouse_world_pos, DataManager::GetD3DDevice());
    do_once = true;

    adv_man = std::make_unique<AdvisorManager>();
    adv_man->init(advisor_window);

    window_one_gate->setVisibility(false);
    window_two_karma_station->setVisibility(false);
    window_three_topias->setVisibility(false);
    window_four_training_centers_window->setVisibility(false);
    
    return true;
}

void GamePlay::Update(GameData* game_data)
{   
    if (do_once)
    {
        ResizeUI();
        do_once = false;
    }

    // mouse pos
    auto mouse_pos = Vector2(game_data->mouse_state.x, game_data->mouse_state.y);
    
    //updates panel
    main_panel->update(game_data,mouse_pos);
    //gates
    window_one_gate->update(game_data,mouse_pos);
    //update advisor
    advisor_window->update(game_data,mouse_pos);
    //update soul view
    soul_view->update(game_data,mouse_pos);
    //karma station
    window_two_karma_station->update(game_data,mouse_pos);
    //Topais
    window_three_topias->update(game_data,mouse_pos);
    //training centre
    window_four_training_centers_window->update(game_data,mouse_pos);
    

    adv_man->Update(game_data);
    EconomyManager::UpdateCurrency(game_data);
    EconomyManager::UpdateSouls();
}

void GamePlay::ScaledUpdate(GameData* game_data, float& scaled_dt)
{
}

void GamePlay::LateUpdate(GameData* game_data)
{
    // Update mouse position
    mouse_screen_pos.x = game_data->mouse_state.x;
    mouse_screen_pos.y = game_data->mouse_state.y;

    // Building System
    building_system->Tick(game_data);
}

void GamePlay::GetEvents(const AL::Event& al_event)
{
    switch (al_event.type)
    {
    case AL::unknown:
        break;
        
    case AL::event_input:
        break;
        
    case AL::event_cursor_move:
        break;
        
    case AL::event_cursor_interact:
        break;
        
    case AL::event_sound_start:
        break;
        
    case AL::event_sound_stop:
        break;
        
    case AL::event_ui:

        switch (al_event.ui.action)
        {
            case AL::UI::resize_ui:
                ResizeUI();
                break;

            case AL::UI::window_gate:
                window_one_gate->setVisibility(!window_one_gate->getVisibility());
                break;

            case AL::UI::window_karma_station:
                window_two_karma_station->setVisibility(!window_two_karma_station->getVisibility());
                break;

            case AL::UI::window_advisors:
                advisor_window->is_visible = !advisor_window->is_visible;
                break;

            case AL::UI::window_topias:
                window_three_topias->setVisibility(!window_three_topias->getVisibility());
                break;

            case AL::UI::window_training_centre:
                window_four_training_centers_window->setVisibility(!window_four_training_centers_window->getVisibility());
                break;

            case AL::UI::window_soulview:
                soul_view->generateRandSoul();
                soul_view->is_visible = !soul_view->is_visible;
                break;
            
            default:
                break;
        }
        break;
        
    case AL::event_build_sys:
        break;
        
    case AL::event_game:
        break;
        
    default:
        break;
    }
}

void GamePlay::Render2D(DrawData2D* draw_data2D)
{
    ui_frame->Draw(draw_data2D);
    
    //render advisor
    advisor_window->render(draw_data2D);

    //render soul view
    soul_view->render(draw_data2D);
    
    // checks if window is open to render

    //Render window
    window_one_gate->render(draw_data2D);
    
    //karma station
    window_two_karma_station->render(draw_data2D);
    //Topias
    window_three_topias->render(draw_data2D);
    //training centre
    window_four_training_centers_window->render(draw_data2D);
    
    //renders panel
    main_panel->render(draw_data2D);
}

void GamePlay::Render3D(DrawData* draw_data)
{
    UpdateMousePos(draw_data);
    
    // Building System
    building_system->Render3D(draw_data);
}

void GamePlay::UpdateMousePos(DrawData* draw_data)
{
    // Translate screen pos to world pos
    // TODO: update the screen width and height
    Vector3 temp_world_pos = XMVector3Unproject(mouse_screen_pos, 0, 0, screen_size.x, screen_size.y,
        draw_data->main_camera->GetNearZ(),
        draw_data->main_camera->GetFarZ(),
        draw_data->main_camera->GetProj(),
        draw_data->main_camera->GetView(),
        draw_data->main_camera->GetWorldMatrix());

    *mouse_world_pos = Raycast::GetPosOnY(0, draw_data->main_camera->GetDirection(), temp_world_pos);

    // Offset by camera movement
    mouse_world_pos->x += draw_data->main_camera->GetTarget().x;
    mouse_world_pos->z += draw_data->main_camera->GetTarget().z;

    // Floor mouse_world_pos to tilemap grid (each tile is 1x1 unit)
    *mouse_world_pos = Vector3(std::floor(mouse_world_pos->x), 0, std::floor(mouse_world_pos->z));
}

void GamePlay::ResizeUI()
{
    screen_size = Vector2(*DataManager::GetRES().first, *DataManager::GetRES().second);
    ui_frame->ReSize(screen_size.x, screen_size.y);
    window_one_gate->reSize(screen_size);
    main_panel->reSize(screen_size);
    advisor_window->reSize(screen_size);
    soul_view->reSize(screen_size);
    window_two_karma_station->reSize(screen_size);
    window_three_topias->reSize(screen_size);
    window_four_training_centers_window->reSize(screen_size);
}

