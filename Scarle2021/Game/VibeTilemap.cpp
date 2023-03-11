#include "pch.h"
#include "VibeTilemap.h"

VibeTilemap::VibeTilemap(ID3D11Device* GD, std::shared_ptr<TextureManager> _texture_manager, int _size, Vector3 _start):
	size(_size), start(_start)
{
	for (int x = 0; x < size; x++)
	{
		vibe_tilemap.emplace_back();
		for (int y = 0; y < size; y++)
		{
			vibe_tilemap[x].emplace_back(std::make_unique<VibeTile>(GD, _texture_manager->GetTextureZone(Vibe), start + Vector3(x, 0, y), Vibe));
			vibe_tilemap[x][y]->UpdateWorldMatrix();
		}
	}
}

VibeTilemap::~VibeTilemap()
{
}

void VibeTilemap::Draw(DrawData* _DD)
{
	for (auto& x : vibe_tilemap)
	{
		for (auto& y : x)
		{
			y->Draw(_DD);
		}
	}
}

/// <summary>
/// Change tilemap's vibes system at certain tile position at a certain scale and value
/// </summary>
/// <param name="tile_pos">The starting position/structure origin</param>
/// <param name="vibe_diff">The delta of the vibe</param>
/// <param name="tile_size">The size of the area to be changed</param>
void VibeTilemap::VibeChange(Vector3 tile_pos, int vibe_diff, int tile_size)
{
	for (int x = 0; x < tile_size; x++)
	{
		for (int z = 0; z < tile_size; z++)
		{
			vibe_tilemap[tile_pos.x + x][tile_pos.z + z]->ChangeVibe(vibe_diff);
		}
	}

	if (tile_pos.x > 0)
	{
		for (int z = 0; z < tile_size; z++)
		{
			vibe_tilemap[tile_pos.x - 1][tile_pos.z + z]->ChangeVibe(vibe_diff);
		}
	}
	if (tile_pos.x < size - tile_size)
	{
		for (int z = 0; z < tile_size; z++)
		{
			vibe_tilemap[tile_pos.x + tile_size][tile_pos.z + z]->ChangeVibe(vibe_diff);
		}
	}

	if (tile_pos.z > 0)
	{
		for (int x = 0; x < tile_size; x++)
		{
			vibe_tilemap[tile_pos.x + x][tile_pos.z - 1]->ChangeVibe(vibe_diff);
		}
	}
	if (tile_pos.z < size - tile_size)
	{
		for (int x = 0; x < tile_size; x++)
		{
			vibe_tilemap[tile_pos.x + x][tile_pos.z + tile_size]->ChangeVibe(vibe_diff);
		}
	}
}
