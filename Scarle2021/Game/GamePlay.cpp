#include "pch.h"
#include "GamePlay.h"

GamePlay::GamePlay(GameData* _game_data) : StateTemplate(_game_data)
{
}

GamePlay::~GamePlay()
= default;

bool GamePlay::init()
{
    text = new TextGO2D("GAMEPLAYYYYYYYYYYYYY");
    text->SetPos(Vector2(100, 10));
    text->SetColour(Color((float*)&Colors::Yellow));
    
    return true;
}

void GamePlay::Update(float& delta_time)
{
}

void GamePlay::ScaledUpdate(float& delta_time)
{
}

void GamePlay::LateUpdate()
{
}

void GamePlay::Render2D()
{
    text->Draw(DataManager::GetDD2D());
}

void GamePlay::Render3D()
{
}

void GamePlay::GetInput()
{
}

