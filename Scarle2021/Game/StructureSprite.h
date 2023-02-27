#pragma once
#include "VBQuad.h"

class StructureSprite : public VBQuad
{
public:
	StructureSprite(ID3D11Device* GD, Vector2 width_height, Vector3 tile_pos, std::string texture);
	~StructureSprite();

	Vector3 GetTilePos() { return pos; }

protected:

private:
	const float PI = 3.141592653589793238462643383279502884197169399375105820974944;
	Vector3 pos;

};

