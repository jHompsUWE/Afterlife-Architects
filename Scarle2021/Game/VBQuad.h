#pragma once

#include "VBGO.h"
#include "vertex.h"
#include "DDSTextureLoader.h"

class VBQuad : public VBGO
{
public:
	VBQuad(ID3D11Device* GD, std::string textureName);
	virtual ~VBQuad();

	void SetTexture(std::string textureName);

protected:
	myVertex* m_vertices = nullptr;

private:
	ID3D11Device* d11_device = nullptr;
};

