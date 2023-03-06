#include "pch.h"
#include "LevelSelect.h"

LevelSelect::LevelSelect()
= default;

LevelSelect::~LevelSelect()
{
    for (auto button : buttons)
    {
        delete button;        
    }
}


bool LevelSelect::init()
{
    // level select background image
    main_menu_bg = new ImageGO2D("MainmenuBG",DataManager::GetD3DDevice());
    main_menu_bg->SetOrigin(Vector2(0,0));

    // UI buttons init................
    //Easy button
    buttons.push_back(new Button(Vector2(109,37),DataManager::GetD3DDevice(),
        "Easy","ButtonBackgroundMM",enter_game_play,Vector2(0.5,0.5)));
    
    //Medium button
    buttons.push_back(new Button(Vector2(536,37),DataManager::GetD3DDevice(),
        "Medium","ButtonBackgroundMM",enter_game_play,Vector2(0.5,0.5)));
    
    //Bard button
    buttons.push_back(new Button(Vector2(960,37),DataManager::GetD3DDevice(),
        "Hard","ButtonBackgroundMM",enter_game_play,Vector2(0.5,0.5)));

    //Return Main menu button
    buttons.push_back(new Button(Vector2(262,661),DataManager::GetD3DDevice(),
        "Return to Main Menu","ButtonBackgroundMM",enter_main_menu,Vector2(0.5,0.5)));

    
    return true;
}

void LevelSelect::Update(GameData* game_data)
{
    //saves mouse pos
    auto mouse_pos = Vector2(game_data->mouse_state.x, game_data->mouse_state.y);

    for (auto& button : buttons)
    {
        button->update(game_data,mouse_pos);
    }

    main_menu_bg->Tick(game_data);
}

void LevelSelect::ScaledUpdate(GameData* game_data, float& scaled_dt)
{
}

void LevelSelect::LateUpdate(GameData* game_data)
{
}

void LevelSelect::GetEvents(std::list<AfterlifeEvent>& event_list)
{
    for (auto& ev : event_list)
    {
        switch (ev)
        {
        case none:
            std::cout << "soooos" << std::endl;
            break;
            
        case enter_game_play:
            DataManager::GetGD()->current_game_state = gs_gameplay;
            break;
            
        case enter_main_menu:
            DataManager::GetGD()->current_game_state = gs_main_menu;
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

void LevelSelect::Render2D(DrawData2D* draw_data2D)
{
    main_menu_bg->Draw(draw_data2D);
    
    for (auto& button : buttons)
    {
        button->render(draw_data2D);
    }
}

void LevelSelect::Render3D(DrawData* draw_data)
{
}

void LevelSelect::ResizeUI()
{
    Vector2 game_res = Vector2(*DataManager::GetRES().first, *DataManager::GetRES().second);
    main_menu_bg->ReSize(game_res.x, game_res.y);
    
    for (auto& button : buttons)
    {
        button->reSize(game_res);
    }
}
