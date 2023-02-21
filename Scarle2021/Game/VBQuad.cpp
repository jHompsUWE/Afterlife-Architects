#include "pch.h"
#include "VBQuad.h"

void VBQuad::init(ID3D11Device* GD)
{
	m_vertices = new myVertex[4];
	WORD* indices = new WORD[4];

	for (int i = 0; i < 4; i++)
	{
		indices[i] = (WORD)i;
		m_vertices[i].texCoord = Vector2::One;
	}

	int vert = 0;
	m_vertices[vert].Color = Color(1.0f, 0.0f, 0.0f, 1.0f);
	m_vertices[vert++].Pos = Vector3(-1.0f, 1.0f, 0.0f);

	m_vertices[vert].Color = Color(1.0f, 0.0f, 0.0f, 1.0f);
	m_vertices[vert++].Pos = Vector3(1.0f, 1.0f, 0.0f);	

	m_vertices[vert].Color = Color(1.0f, 0.0f, 0.0f, 1.0f);
	m_vertices[vert++].Pos = Vector3(-1.0f, -1.0f, 0.0f);

	m_vertices[vert].Color = Color(1.0f, 0.0f, 0.0f, 1.0f);
	m_vertices[vert++].Pos = Vector3(1.0f, -1.0f, 0.0f);

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

	BuildIB(GD, indices);
	BuildVB(GD, 4, m_vertices);

	delete[] indices;
	delete[] m_vertices;
	m_vertices = nullptr;
}
