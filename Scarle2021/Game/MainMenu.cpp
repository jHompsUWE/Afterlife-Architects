#include "pch.h"
#include "MainMenu.h"
#include "AStarPathfinding.h"

MainMenu::MainMenu()
= default;

MainMenu::~MainMenu()
{
    for (auto button : buttons)
    {
        delete button;        
    }
    
    /*
    delete start_button;
    delete main_menu_bg;
    delete load_button;
    delete load_scenario_button;
    delete replay_intro;
    delete quit_afterlife;
    */
}

bool MainMenu::init()
{
    // main menu background image
    main_menu_bg = new ImageGO2D("MainmenuBG",DataManager::GetD3DDevice());
    main_menu_bg->SetOrigin(Vector2(0,0));

    // UI buttons init................
    //start button
    buttons.push_back(new Button(Vector2(109,37),DataManager::GetD3DDevice(),
        "Start Game","ButtonBackgroundMM",enter_level_select,Vector2(0.5,0.5)));
    
    //load button
    buttons.push_back(new Button(Vector2(536,37),DataManager::GetD3DDevice(),
        "Load Game","ButtonBackgroundMM",enter_level_select,Vector2(0.5,0.5)));
    
    //scenario button
    buttons.push_back(new Button(Vector2(960,37),DataManager::GetD3DDevice(),
        "Load Scenario","ButtonBackgroundMM",enter_level_select,Vector2(0.5,0.5)));
    
    //intro replay button
    buttons.push_back(new Button(Vector2(262,661),DataManager::GetD3DDevice(),
        "Replay Intro","ButtonBackgroundMM",enter_level_select,Vector2(0.5,0.5)));

    //Quit afterlife button
    buttons.push_back(new Button(Vector2(791,661),DataManager::GetD3DDevice(),
        "Quit AfterLife","ButtonBackgroundMM",enter_level_select,Vector2(0.5,0.5)));
    
    return true;
}

void MainMenu::Update(GameData* game_data)
{
    //saves mouse pos
    auto mouse_pos = Vector2(game_data->mouse_state.x, game_data->mouse_state.y);

    for (auto& button : buttons)
    {
        button->update(game_data,mouse_pos);
    }
    
    main_menu_bg->Tick(game_data);
    
    /*
    start_button->update(game_data,mouse_pos);
    load_button->update(game_data,mouse_pos);
    load_scenario_button->update(game_data,mouse_pos);
    replay_intro->update(game_data,mouse_pos);
    quit_afterlife->update(game_data,mouse_pos);
    */
} 

void MainMenu::ScaledUpdate(GameData* game_data, float& scaled_dt)
{
}

void MainMenu::LateUpdate(GameData* game_data)
{
}

void MainMenu::GetEvents(std::list<AfterlifeEvent>& event_list)
{
    for (auto& ev : event_list)
    {
        switch (ev)
        {
        case none:
            std::cout << "soooos" << std::endl;
            break;
            
        case enter_level_select:
            DataManager::GetGD()->current_game_state = gs_level_select;
            break;
            
        case enter_main_menu:
            DataManager::GetGD()->current_game_state = gs_main_menu;
            break;
            
        case input_left:
            break;
            
        case input_right:
            DataManager::GetGD()->current_game_state = gs_gameplay;
            break;

        case game_resized:
            ResizeUI();
            break;
            
        default:
            break;
        }
    }
}

void MainMenu::Render2D(DrawData2D* draw_data2D)
{
    main_menu_bg->Draw(draw_data2D);
    
    for (auto& button : buttons)
    {
        button->render(draw_data2D);
    }

    
    
    /*
    main_menu_bg->Draw(draw_data2D);
    start_button->render(draw_data2D);
    load_button->render(draw_data2D);
    load_scenario_button->render(draw_data2D);
    replay_intro->render(draw_data2D);
    quit_afterlife->render(draw_data2D);
    */
}

void MainMenu::Render3D(DrawData* draw_data)
{
}

void MainMenu::ResizeUI()
{
    main_menu_bg->ReSize(DataManager::GetRES().first, DataManager::GetRES().second);
    
    for (auto& button : buttons)
    {
        button->reSize(DataManager::GetRES());
    }
}





