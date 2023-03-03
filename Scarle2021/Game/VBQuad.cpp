#include "pch.h"
#include "VBQuad.h"
#include "Helper.h"

#define DESTROY( x ) if( x ){ x->Release(); x = nullptr;}

VBQuad::VBQuad(ID3D11Device* GD, float width, float height): d11_device(GD)
{
	SetPhysicsOn(false);

	int num_verts = 6;
	m_numPrims = 2;
	m_vertices = new myVertex[num_verts];
	WORD* indices = new WORD[num_verts];

	for (int i = 0; i < num_verts; i++)
	{
		indices[i] = (WORD)i;
	}

	int vert = 0;
	m_vertices[vert].texCoord = Vector2(0.0f, 0.0f);
	m_vertices[vert].Color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	m_vertices[vert++].Pos = Vector3(0.0f, 0.0f, height);

	m_vertices[vert].texCoord = Vector2(1.0f, 0.0f);
	m_vertices[vert].Color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	m_vertices[vert++].Pos = Vector3(width, 0.0f, height);

	m_vertices[vert].texCoord = Vector2(0.0f, 1.0f);
	m_vertices[vert].Color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	m_vertices[vert++].Pos = Vector3(0.0f, 0.0f, 0.0f);

	m_vertices[vert].texCoord = Vector2(1.0f, 0.0f);
	m_vertices[vert].Color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	m_vertices[vert++].Pos = Vector3(width, 0.0f, height);

	m_vertices[vert].texCoord = Vector2(0.0f, 1.0f);
	m_vertices[vert].Color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	m_vertices[vert++].Pos = Vector3(0.0f, 0.0f, 0.0f);

	m_vertices[vert].texCoord = Vector2(1.0f, 1.0f);
	m_vertices[vert].Color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	m_vertices[vert++].Pos = Vector3(width, 0.0f, 0.0f);

	for (UINT i = 0; i < m_numPrims; i++)
	{
		WORD V1 = (WORD)(3 * i);
		WORD V2 = V1 + 1;
		WORD V3 = V1 + 2;

		//build normals
		Vector3 norm;
		Vector3 vec1 = m_vertices[V1].Pos - m_vertices[V2].Pos;
		Vector3 vec2 = m_vertices[V3].Pos - m_vertices[V2].Pos;
		norm = vec1.Cross(vec2);
		norm.Normalize();

		m_vertices[V1].Norm = norm;
		m_vertices[V2].Norm = norm;
		m_vertices[V3].Norm = norm;
	}

	BuildIB(d11_device, indices);
	BuildVB(d11_device, num_verts, m_vertices);

	delete[] indices;
	delete[] m_vertices;
	m_vertices = nullptr;
}

VBQuad::~VBQuad()
{
	delete m_vertices;
}

/// <summary>
/// Changes the texture of the quad
/// </summary>
/// <param name="textureName">Name of the texture without the data type (ex: Tile_Blue, NOT Tile_Blue.png)</param>
void VBQuad::SetTexture(std::string textureName)
{
	std::string fullfilename = "../Assets/";
	fullfilename += textureName;
	fullfilename += ".dds";

	DESTROY(m_pTextureRV);

	HRESULT hr = CreateDDSTextureFromFile(d11_device, Helper::charToWChar(fullfilename.c_str()), nullptr, &m_pTextureRV);
	assert(hr == S_OK);
}

/// <summary>
/// Rebuilds the quad with the set color
/// </summary>
/// <param name="color">Color of the quad</param>
void VBQuad::SetColor(Color color)
{
	SetPhysicsOn(false);

	int num_verts = 6;
	m_numPrims = 2;
	m_vertices = new myVertex[num_verts];
	WORD* indices = new WORD[num_verts];

	for (int i = 0; i < num_verts; i++)
	{
		indices[i] = (WORD)i;
	}

	int vert = 0;
	m_vertices[vert].texCoord = Vector2(0.0f, 0.0f);
	m_vertices[vert].Color = color;
	m_vertices[vert++].Pos = Vector3(0.0f, 0.0f, 1.0f);

	m_vertices[vert].texCoord = Vector2(1.0f, 0.0f);
	m_vertices[vert].Color = color;
	m_vertices[vert++].Pos = Vector3(1.0f, 0.0f, 1.0f);

	m_vertices[vert].texCoord = Vector2(0.0f, 1.0f);
	m_vertices[vert].Color = color;
	m_vertices[vert++].Pos = Vector3(0.0f, 0.0f, 0.0f);

	m_vertices[vert].texCoord = Vector2(1.0f, 0.0f);
	m_vertices[vert].Color = color;
	m_vertices[vert++].Pos = Vector3(1.0f, 0.0f, 1.0f);

	m_vertices[vert].texCoord = Vector2(0.0f, 1.0f);
	m_vertices[vert].Color = color;
	m_vertices[vert++].Pos = Vector3(0.0f, 0.0f, 0.0f);

	m_vertices[vert].texCoord = Vector2(1.0f, 1.0f);
	m_vertices[vert].Color = color;
	m_vertices[vert++].Pos = Vector3(1.0f, 0.0f, 0.0f);

	for (UINT i = 0; i < m_numPrims; i++)
	{
		WORD V1 = (WORD)(3 * i);
		WORD V2 = V1 + 1;
		WORD V3 = V1 + 2;

		//build normals
		Vector3 norm;
		Vector3 vec1 = m_vertices[V1].Pos - m_vertices[V2].Pos;
		Vector3 vec2 = m_vertices[V3].Pos - m_vertices[V2].Pos;
		norm = vec1.Cross(vec2);
		norm.Normalize();

		m_vertices[V1].Norm = norm;
		m_vertices[V2].Norm = norm;
		m_vertices[V3].Norm = norm;
	}

	BuildIB(d11_device, indices);
	BuildVB(d11_device, num_verts, m_vertices);

	delete[] indices;
	delete[] m_vertices;
	m_vertices = nullptr;
}
