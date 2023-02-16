#include "pch.h"
#include "LevelSelect.h"

LevelSelect::LevelSelect(GameData* _game_data) : StateTemplate(_game_data)
{
}

LevelSelect::~LevelSelect()
= default;

bool LevelSelect::init()
{
    return true;
}

void LevelSelect::Update(float& delta_time)
{
}

void LevelSelect::ScaledUpdate(float& delta_time)
{
}

void LevelSelect::LateUpdate()
{
}

void LevelSelect::Render()
{
}

void LevelSelect::GetInput()
{
}
