#include "pch.h"
#include "LevelSelect.h"

LevelSelect::LevelSelect()
= default;

LevelSelect::~LevelSelect()
= default;

bool LevelSelect::init()
{
    return true;
}

void LevelSelect::Update(GameData* game_data)
{
}

void LevelSelect::ScaledUpdate(GameData* game_data, float& scaled_dt)
{
}

void LevelSelect::LateUpdate(GameData* game_data)
{
}

void LevelSelect::GetEvents(std::list<AfterlifeEvent>& event_list)
{
}

void LevelSelect::Render2D(DrawData2D* draw_data2D)
{
}

void LevelSelect::Render3D(DrawData* draw_data)
{
}

