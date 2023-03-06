#include "pch.h"
#include "Tile.h"


Tile::Tile(ID3D11Device* GD, Vector3 _tile_pos, ZoneType zone_type): tile_pos(_tile_pos), type(zone_type)
{
	quad = new VBQuad(GD, 1, 1);
	quad->SetTexture(GetTextureOfType(type));
	quad->SetPos(tile_pos);

	vibe_quad = new VBQuad(GD, 1, 1);
	vibe_quad->SetTexture("Tile_Vibes");
	vibe_quad->SetPos(tile_pos);

	is_occupied = false;
}

Tile::~Tile()
{
	delete quad;
	delete vibe_quad;
}

void Tile::Tick()
{
	vibe_quad->UpdateWorldMatrix();
	quad->UpdateWorldMatrix();
}

void Tile::Draw(DrawData* _DD, bool show_vibe)
{
	if (show_vibe)
	{
		vibe_quad->Draw(_DD);
	}
	else
	{
		quad->Draw(_DD);
	}
}

Vector3 Tile::GetTilePos()
{
	return tile_pos;
}

void Tile::SetTexture(ZoneType zone_type)
{
	type = zone_type;
	quad->SetTexture(GetTextureOfType(zone_type));
}

/// <summary>
/// Gets the name of the texture file based on the ZoneType
/// </summary>
/// <param name="type">ZoneType</param>
/// <returns>std::string of the texture name</returns>
std::string Tile::GetTextureOfType(ZoneType type)
{
	switch (type)
	{
	case Void:
		return "Tile_Void";

	case Green:
		return "Tile_Green";

	case Yellow:
		return "Tile_Yellow";

	case Orange:
		return "Tile_Orange";

	case Brown:
		return "Tile_Brown";

	case Purple:
		return "Tile_Purple";

	case Red:
		return "Tile_Red";

	case Blue:
		return "Tile_Blue";

	case Inactive_Green:
		return "Tile_Inactive_Green";

	case Inactive_Yellow:
		return "Tile_Inactive_Yellow";

	case Inactive_Orange:
		return "Tile_Inactive_Orange";

	case Inactive_Brown:
		return "Tile_Inactive_Brown";

	case Inactive_Purple:
		return "Tile_Inactive_Purple";

	case Inactive_Red:
		return "Tile_Inactive_Red";

	case Inactive_Blue:
		return "Tile_Inactive_Blue";

	case Structure:
		return "Tile_Structure";

	case Rock:
		return "Tile_Rock";

	case Water:
		return "Tile_Water";

	case Lava:
		return "Tile_Lava";
	}
}

/// <summary>
/// Changes individual tile colour and vibe value
/// </summary>
/// <param name="vibe_diff"></param>
void Tile::ChangeVibe(int vibe_diff)
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
	new_color.x = (255.0f - (temp_int * colour_scaling))/255.0f;
	new_color.y = (255.0f - (temp_int * colour_scaling))/255.0f;
	new_color.z = (255.0f - (temp_int * colour_scaling))/255.0f;

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
	vibe_quad->SetColor(new_color);
}
