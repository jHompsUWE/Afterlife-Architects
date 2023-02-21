#pragma once

#include "VBGO.h"
#include "vertex.h"

class VBQuad : public VBGO
{
public:
	VBQuad() {};
	virtual ~VBQuad() {};

	void init(ID3D11Device* GD);

protected:
	myVertex* m_vertices = nullptr;
};

