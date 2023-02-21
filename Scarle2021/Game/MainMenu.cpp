#include "pch.h"
#include "MainMenu.h"

MainMenu::MainMenu()
= default;

MainMenu::~MainMenu()
{
    delete text;
    delete start_button;
    delete MainMenu_bg;
    delete load_button;
    delete load_scenario_button;
    delete replay_intro;
    delete quit_afterlife;
}

bool MainMenu::init()
{   
    // main menu background image
    MainMenu_bg = new ImageGO2D("MainmenuBG",DataManager::GetD3DDevice());
    MainMenu_bg->SetOrigin(Vector2(0,0));

    // UI buttons init................
    //start button
    start_button = new Button(Vector2(109,37),DataManager::GetD3DDevice(),
        "Start Game","ButtonBackgroundMM",input_up,Vector2(0.5,0.5));
    
    //load button
    load_button = new Button(Vector2(536,37),DataManager::GetD3DDevice(),
        "Load Game","ButtonBackgroundMM",input_up,Vector2(0.5,0.5));
    
    //scenario button
    load_scenario_button = new Button(Vector2(960,37),DataManager::GetD3DDevice(),
        "Load Scenario","ButtonBackgroundMM",input_up,Vector2(0.5,0.5));
    
    //intro replay button
    replay_intro = new Button(Vector2(262,661),DataManager::GetD3DDevice(),
        "Replay Intro","ButtonBackgroundMM",input_up,Vector2(0.5,0.5));

    //Quit afterlife button
    quit_afterlife = new Button(Vector2(791,661),DataManager::GetD3DDevice(),
        "Quit AfterLife","ButtonBackgroundMM",input_up,Vector2(0.5,0.5));
    
    return true;
}

void MainMenu::Update(GameData* game_data)
{
    //saves mouse pos
    auto mouse_pos = Vector2(game_data->mouse_state.x, game_data->mouse_state.y);
    
    start_button->update(game_data,mouse_pos);
    load_button->update(game_data,mouse_pos);
    load_scenario_button->update(game_data,mouse_pos);
    replay_intro->update(game_data,mouse_pos);
    quit_afterlife->update(game_data,mouse_pos);
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
            
        case input_up:
            DataManager::GetGD()->current_game_state = gs_gameplay;
            break;
            
        case input_down:
            break;
            
        case input_left:
            break;
            
        case input_right:
            break;
            
        default:
            break;
        }
    }
}

void MainMenu::Render2D(DrawData2D* draw_data2D)
{
    MainMenu_bg->Draw(draw_data2D);
    start_button->render(draw_data2D);
    load_button->render(draw_data2D);
    load_scenario_button->render(draw_data2D);
    replay_intro->render(draw_data2D);
    quit_afterlife->render(draw_data2D);
}

void MainMenu::Render3D(DrawData* draw_data)
{
    
}




