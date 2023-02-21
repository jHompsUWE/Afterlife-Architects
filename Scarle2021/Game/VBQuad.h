#pragma once

#include "VBGO.h"
#include "vertex.h"
#include "DDSTextureLoader.h"

class VBQuad : public VBGO
{
public:
	VBQuad() {};
	virtual ~VBQuad() {};

	void init(ID3D11Device* GD);
	void SetTexture(ID3D11Device* GD, std::string textureName);

protected:
	myVertex* m_vertices = nullptr;
};

