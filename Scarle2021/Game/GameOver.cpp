#include "pch.h"
#include "GameOver.h"

GameOver::GameOver()
= default;

GameOver::~GameOver()
= default;

bool GameOver::init()
{
    return true;
}

void GameOver::GetEvents(queue<AfterlifeEvent>&event_queue)
{
}

void GameOver::Update(GameData* game_data)
{
}

void GameOver::ScaledUpdate(GameData* game_data, float& scaled_dt)
{
}

void GameOver::LateUpdate(GameData* game_data)
{
}

void GameOver::Render2D(DrawData2D* draw_data2D)
{
}

void GameOver::Render3D(DrawData* draw_data)
{
}



