#include "pch.h"
#include "MainMenu.h"

MainMenu::MainMenu(GameData* _game_data) : StateTemplate(_game_data)
{
}

MainMenu::~MainMenu()
= default;

bool MainMenu::init()
{
    text = new TextGO2D("MAIN MENU");
    text->SetPos(Vector2(100, 10));
    text->SetColour(Color((float*)&Colors::Yellow));
    
    return true;
}

void MainMenu::Update(float& delta_time)
{
} 

void MainMenu::ScaledUpdate(float& delta_time)
{
}

void MainMenu::LateUpdate()
{
}

void MainMenu::Render()
{
    text->Draw(ScarlePointers::GetDD2D());
}

void MainMenu::GetInput()
{
    if(game_data->keybaord_state.A)
    {
        std::cout << "TEST" << std::endl;
        game_data->current_game_state = gs_gameplay;
    }
}


