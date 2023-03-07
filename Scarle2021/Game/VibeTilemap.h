#pragma once
#include "VibeTile.h"
#include <vector>

class VibeTilemap
{
public:
	VibeTilemap(ID3D11Device* GD, int _size, Vector3 _start);
	~VibeTilemap();

	void Draw(DrawData* _DD);

	void VibeChange(Vector3 tile_pos, int vibe_diff, int tile_size);

protected:
	std::vector<std::vector<std::unique_ptr<VibeTile>>> vibe_tilemap;
	float size;
	Vector3 start;

private:
};

