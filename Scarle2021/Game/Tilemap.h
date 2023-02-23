#pragma once
#include "Tile.h"
#include <list>
#include <memory>
#include <iostream>

class Tilemap
{
public:
	Tilemap(ID3D11Device* GD, int size);
	~Tilemap();

	void Tick(GameData* game_data);
	void Draw(DrawData* _DD);

	void ChangeAllTexture(std::string texture);

protected:

private:
	std::list<std::unique_ptr<Tile>> tile_list;
};

