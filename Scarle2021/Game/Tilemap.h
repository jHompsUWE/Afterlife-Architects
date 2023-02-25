#pragma once
#include "Tile.h"
#include <list>
#include <memory>
#include <iostream>
#include <math.h>
#include <vector>

class Tilemap
{
public:
	Tilemap(ID3D11Device* GD, int _size);
	~Tilemap();

	void Tick(GameData* game_data);
	void Draw(DrawData* _DD);

	void BoxFill(std::string texture, Vector3 start, Vector3 end);
	void SetTile(Vector3 tile_pos, std::string texture);

protected:

private:
	std::vector<std::vector<std::unique_ptr<Tile>>> tilemap;
	float size;
};

