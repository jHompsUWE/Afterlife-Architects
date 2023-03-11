#include "pch.h"
#include "VibeTile.h"

VibeTile::VibeTile(ID3D11Device* GD, ID3D11ShaderResourceView* texture, Vector3 _tile_pos, ZoneType zone_type):
	Tile(GD, _tile_pos, zone_type)
{
	quad->SetTexture(texture);

	is_occupied = true;
}

VibeTile::~VibeTile()
{
}

/// <summary>
/// Changes individual tile colour and vibe value
/// </summary>
/// <param name="vibe_diff">The delta of the vibe</param>
void VibeTile::ChangeVibe(int vibe_diff)
{
	vibe_value += vibe_diff;
	// Create temporary int and colour to produce required colour
	Color new_color;
	int temp_int = vibe_value;
	// Make vibe value absolute
	if (vibe_value < 0)
	{
		temp_int = -temp_int;
	}
	// Scale colour down to 0,0,0
	new_color.x = (255.0f - (temp_int * colour_scaling)) / 255.0f;
	new_color.y = (255.0f - (temp_int * colour_scaling)) / 255.0f;
	new_color.z = (255.0f - (temp_int * colour_scaling)) / 255.0f;

	// If positive vibe, lean towards green
	if (vibe_value > 0)
	{
		new_color.y = 1;
	}
	// If negative vibe, lean towards red
	else if (vibe_value < 0)
	{
		new_color.x = 1;
	}
	quad->SetColor(new_color);
}

