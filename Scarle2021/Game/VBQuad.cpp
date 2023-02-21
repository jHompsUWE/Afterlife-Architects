#include "pch.h"
#include "VBQuad.h"
#include "Helper.h"

VBQuad::VBQuad(ID3D11Device* GD, std::string textureName): d11_device(GD)
{
	SetTexture(textureName);

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
	m_vertices[vert++].Pos = Vector3(-1.0f, 1.0f, 0.0f);

	m_vertices[vert].texCoord = Vector2(1.0f, 0.0f);
	m_vertices[vert].Color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	m_vertices[vert++].Pos = Vector3(1.0f, 1.0f, 0.0f);

	m_vertices[vert].texCoord = Vector2(0.0f, 1.0f);
	m_vertices[vert].Color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	m_vertices[vert++].Pos = Vector3(-1.0f, -1.0f, 0.0f);

	m_vertices[vert].texCoord = Vector2(1.0f, 0.0f);
	m_vertices[vert].Color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	m_vertices[vert++].Pos = Vector3(1.0f, 1.0f, 0.0f);

	m_vertices[vert].texCoord = Vector2(0.0f, 1.0f);
	m_vertices[vert].Color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	m_vertices[vert++].Pos = Vector3(-1.0f, -1.0f, 0.0f);

	m_vertices[vert].texCoord = Vector2(1.0f, 1.0f);
	m_vertices[vert].Color = Color(1.0f, 1.0f, 1.0f, 1.0f);
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

	BuildIB(d11_device, indices);
	BuildVB(d11_device, num_verts, m_vertices);

	delete[] indices;
	delete[] m_vertices;
	m_vertices = nullptr;

	// Raster state
	D3D11_RASTERIZER_DESC rasterDesc;
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_NONE;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = true;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	HRESULT hr = d11_device->CreateRasterizerState(&rasterDesc, &m_pRasterState);

	ID3DBlob* pPixelShaderBuffer = NULL;
	hr = CompileShaderFromFile(Helper::charToWChar("../Assets/shader.fx"), "PS2", "ps_4_0_level_9_1", &pPixelShaderBuffer);
	d11_device->CreatePixelShader(pPixelShaderBuffer->GetBufferPointer(), pPixelShaderBuffer->GetBufferSize(), NULL, &m_pPixelShader);
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

	HRESULT hr = CreateDDSTextureFromFile(d11_device, Helper::charToWChar(fullfilename.c_str()), nullptr, &m_pTextureRV);
	assert(hr == S_OK);
}
