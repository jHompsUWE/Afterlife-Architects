#include "pch.h"
#include "Tilemap.h"

Tilemap::Tilemap(ID3D11Device* GD, int size)
{
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			tile_list.emplace_back(std::make_unique<Tile>(GD, Vector3(x, 0, y), "Tile_Red"));
		}
	}
}

Tilemap::~Tilemap()
{
	//tile_list.clear();
}

void Tilemap::Tick(GameData* game_data)
{
	for (auto& tile : tile_list)
	{
		tile->Tick(game_data);
	}
}

void Tilemap::Draw(DrawData* _DD)
{
	for (auto& tile : tile_list)
	{
		tile->Draw(_DD);
	}
}

void Tilemap::ChangeAllTexture(std::string texture)
{
	for (auto& tile : tile_list)
	{
		tile->SetTexture(texture);
	}
}
