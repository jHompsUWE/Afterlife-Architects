#pragma once

#include "VBGO.h"
#include "vertex.h"
#include "DDSTextureLoader.h"

#include <iostream>

class VBQuad : public VBGO
{
public:
	VBQuad(ID3D11Device* GD, float width, float height);
	virtual ~VBQuad();

	void UpdateWorldMatrix();

	void SetTexture(std::string textureName);
	void SetColor(Color color);

protected:
	myVertex* m_vertices = nullptr;

private:
	ID3D11Device* d11_device = nullptr;
};

