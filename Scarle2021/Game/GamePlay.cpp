#include "pch.h"
#include "GamePlay.h"

GamePlay::GamePlay()
= default;

GamePlay::~GamePlay()
= default;

bool GamePlay::init()
{
    return true;
}

void GamePlay::Update(GameData* game_data)
{
}

void GamePlay::ScaledUpdate(GameData* game_data, float& scaled_dt)
{
}

void GamePlay::LateUpdate(GameData* game_data)
{
}

void GamePlay::Render2D(DrawData2D* draw_data2D)
{
}

void GamePlay::Render3D(DrawData* draw_data)
{
}

void GamePlay::GetEvents(queue<AfterlifeEvent>&)
{
}

