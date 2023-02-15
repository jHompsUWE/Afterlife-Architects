#pragma once
#include "gameobject.h"
#include <GeometricPrimitive.h>

//uses systems described here: https://github.com/microsoft/DirectXTK/wiki/GeometricPrimitive
//to create a range of basic geometric shapes.

enum GPGO_TYPE
{
	GPGO_BOX,
	GPGO_CONE,
	GPGO_CUBE,
	GPGO_CYLINDER,
	GPGO_DODECAHEDRON,
	GPGO_GEOSPHERE,
	GPGO_ICOSAHEDRON,
	GPGO_OCTAHEDRON,
	GPGO_SPHERE,
	GPGO_TEAPOT,
	GPGO_TETRAHEDRON,
	GPGO_TORUS
};

class GPGO :    public GameObject
{
public:
	GPGO(ID3D11DeviceContext* _pd3dImmediateContext,GPGO_TYPE _type, float* _colour = (float*)&Colors::AntiqueWhite, float* _params = nullptr);
	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData* _DD);

	GPGO_TYPE GetType() { return m_type; }

	Color GetColour() { return m_colour; }
	void SetColour(Color _colour) { m_colour = _colour; }

protected:
	std::unique_ptr<GeometricPrimitive> shape;
	Color m_colour;
	GPGO_TYPE m_type;

};

