#include "pch.h"
#include "VBSnail.h"
#include "vertex.h"
#include <iostream>
#include <fstream>
#include "gamedata.h"
#include "Helper.h"

using namespace std;

VBSnail::VBSnail(ID3D11Device* _GD, std::string _filename, int _sections, float _scale, float _rot, float _step, Color _col1, Color _col2)
{
	m_fudge = Matrix::CreateTranslation(-3.0f,-3.0f, 0.0f);
	int width = 0;

	string useFilename = "../Models/" + _filename + ".txt";

	//load line
	ifstream lineFile;
	lineFile.open(useFilename);
	lineFile >> width;

	Vector2* baseLine = new Vector2[width];

	for (int i = 0; i < width; i++)
	{
		lineFile >> baseLine[i].x >> baseLine[i].y;
	}
	
	m_numPrims = 2 * (width - 1) * (_sections - 1);
	int numVerts = 3 * m_numPrims;
	myVertex* vertices = new myVertex[numVerts];
	WORD* indices = new WORD[numVerts];

	//as using the standard VB shader set the tex-coords somewhere safe
	for (int i = 0; i<numVerts; i++)
	{
		indices[i] = (WORD)i;
		vertices[i].texCoord = Vector2::One;
	}	
	
	//build base transform
	Matrix rotTrans = Matrix::CreateRotationY(_rot);
	Matrix stepTrans = Matrix::CreateTranslation(0.0f, _step, 0.0f);
	Matrix scaleTrans = Matrix::CreateScale(_scale);
	Matrix baseTrans = scaleTrans *rotTrans * stepTrans;

	//build array of transforms to rotate,scale and translate baseline around the shell
	Matrix* transforms = new Matrix[_sections];
	transforms[0] = Matrix::Identity;
	for (int i = 1; i < _sections; i++)
	{
		transforms[i] = transforms[i - 1] * baseTrans;
	}

	//build the vertices using these transforms and the line
	//two trinagles for each point scale, turn ad step up
	int vert = 0;
	Vector3 calcPos;
	//transform up the steps
	for (int i = 0; i < (_sections - 1) ; i++)
	{
		for (int j = 0 ; j < (width -1); j++)
		{
			vertices[vert].Color = Color::Lerp(_col1, _col2, (float)i / (float)_sections);
			//vertices[vert++].Pos = Vector3((float)i, (float)j, 0.0f);
			calcPos = Vector3(baseLine[j].x, baseLine[j].y, 0.0f);
			vertices[vert++].Pos = Vector3::Transform(calcPos, transforms[i]);

			vertices[vert].Color = Color::Lerp(_col1, _col2, (float)(i + 1) / (float)_sections);
			calcPos = Vector3(baseLine[j].x, baseLine[j].y, 0.0f);
			vertices[vert++].Pos = Vector3::Transform(calcPos, transforms[i+1]);
			//vertices[vert++].Pos = Vector3((float)(i + 1), (float)j, 0.0f);

			vertices[vert].Color = Color::Lerp(_col1, _col2, (float)i / (float)_sections);
			//vertices[vert++].Pos = Vector3((float)i, (float)(j + 1), 0.0f);
			calcPos = Vector3(baseLine[j+1].x, baseLine[j+1].y, 0.0f);
			vertices[vert++].Pos = Vector3::Transform(calcPos, transforms[i]);
			
			vertices[vert].Color = Color::Lerp(_col1, _col2, (float)(i + 1) / (float)_sections);
			//vertices[vert++].Pos = Vector3((float)(i + 1), (float)j, 0.0f);
			calcPos = Vector3(baseLine[j].x, baseLine[j].y, 0.0f);
			vertices[vert++].Pos = Vector3::Transform(calcPos, transforms[i+1]);

			vertices[vert].Color = Color::Lerp(_col1, _col2, (float)(i + 1) / (float)_sections);
			//vertices[vert++].Pos = Vector3((float)(i + 1), (float)(j + 1), 0.0f);
			calcPos = Vector3(baseLine[j+1].x, baseLine[j+1].y, 0.0f);
			vertices[vert++].Pos = Vector3::Transform(calcPos, transforms[i + 1]);

			vertices[vert].Color = Color::Lerp(_col1, _col2, (float)i / (float)_sections);
			//vertices[vert++].Pos = Vector3((float)i, (float)(j + 1), 0.0f);
			calcPos = Vector3(baseLine[j+1].x, baseLine[j+1].y, 0.0f);
			vertices[vert++].Pos = Vector3::Transform(calcPos, transforms[i]);

		}
	}

	//calculate the normals for the basic lighting in the base shader
	for (UINT i = 0; i<m_numPrims; i++)
	{
		WORD V1 = (WORD)(3 * i);
		WORD V2 = V1 + 1;
		WORD V3 = V1 + 2;

		//build normals
		Vector3 norm;
		Vector3 vec1 = vertices[V1].Pos - vertices[V2].Pos;
		Vector3 vec2 = vertices[V3].Pos - vertices[V2].Pos;
		norm = vec2.Cross(vec1);
		norm.Normalize();

		vertices[V1].Norm = norm;
		vertices[V2].Norm = norm;
		vertices[V3].Norm = norm;
	}


	BuildIB(_GD, indices);
	BuildVB(_GD, numVerts, vertices);

	delete[] vertices; //these are all no longer needed as this is now in the Vertex Buffer
	delete[] transforms;
	delete[] indices;
	delete[] baseLine;

	//Setup Raster State
	//we need to see both side of the shell if its empty
	//so set rasterDesc.CullMode = D3D11_CULL_NONE; 
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

	// Create the rasterizer state from the description we just filled out.
	HRESULT hr = _GD->CreateRasterizerState(&rasterDesc, &m_pRasterState);

	//use the 2 sided version
	ID3DBlob* pPixelShaderBuffer = NULL;
	hr = CompileShaderFromFile(Helper::charToWChar("../Assets/shader.fx"), "PS2", "ps_4_0_level_9_1", &pPixelShaderBuffer);
	_GD->CreatePixelShader(pPixelShaderBuffer->GetBufferPointer(), pPixelShaderBuffer->GetBufferSize(), NULL, &m_pPixelShader);
}



void VBSnail::Tick(GameData* _GD)
{
	//m_pitch += _GD->m_dt;
	//m_yaw -= _GD->m_dt;
	//m_roll += 0.5f * _GD->m_dt;
	VBGO::Tick(_GD);
}