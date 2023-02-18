#include "pch.h"
#include "GameOver.h"

GameOver::GameOver(GameData* _game_data) : StateTemplate(_game_data)
{
}

GameOver::~GameOver()
= default;

bool GameOver::init()
{
    return true;
}

void GameOver::Update(float& delta_time)
{
}

void GameOver::ScaledUpdate(float& delta_time)
{
}

void GameOver::LateUpdate()
{
}

void GameOver::Render2D()
{
}

void GameOver::Render3D()
{
}

void GameOver::GetInput()
{
}




