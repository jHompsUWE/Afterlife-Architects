#include "pch.h"
#include "MainMenu.h"
#include "AStarPathfinding.h"

MainMenu::MainMenu()
= default;

MainMenu::~MainMenu()
{
    delete text;
    delete start_button;
}

bool MainMenu::init()
{
    text = new TextGO2D("This ist main menu");
    text->SetPos(Vector2(100, 10));
    text->SetColour(Color((float*)&Colors::Yellow));

    start_button = new Button(Vector2(540,360),DataManager::GetD3DDevice(),
        "Start Game","eevee",input_up);

    return true;
}

void MainMenu::Update(GameData* game_data)
{
    auto mouse_pos = Vector2(game_data->mouse_state.x, game_data->mouse_state.y);
    start_button->update(game_data,mouse_pos);
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
    text->Draw(draw_data2D);
    start_button->render(draw_data2D);
}

void MainMenu::Render3D(DrawData* draw_data)
{
    
}




