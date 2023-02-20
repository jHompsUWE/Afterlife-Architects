#include "pch.h"
#include "MainMenu.h"

MainMenu::MainMenu()
= default;

MainMenu::~MainMenu()
= default;

bool MainMenu::init()
{
    text = new TextGO2D("This ist main menu");
    text->SetPos(Vector2(100, 10));
    text->SetColour(Color((float*)&Colors::Yellow));
    
    return true;
}

void MainMenu::GetEvents(queue<AfterlifeEvent>& event_queue)
{
    while (!event_queue.empty())
    {
        switch (event_queue.front())
        {
        case input_up:
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

        std::cout << event_queue.front() << " soos" << std::endl;
        
        event_queue.pop();
    }
}

void MainMenu::Update(GameData* game_data)
{
} 

void MainMenu::ScaledUpdate(GameData* game_data, float& scaled_dt)
{
}

void MainMenu::LateUpdate(GameData* game_data)
{
}

void MainMenu::Render2D(DrawData2D* draw_data2D)
{
    text->Draw(draw_data2D);
}

void MainMenu::Render3D(DrawData* draw_data)
{
}




