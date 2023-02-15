#include "pch.h"
#include <iostream>
#include <fstream>
#include "fileVBGO.h"
#include "helper.h"
#include "DDSTextureLoader.h"
#include "vertex.h"
#include <DirectXColors.h>

using namespace DirectX;
using namespace std;

FileVBGO::FileVBGO(string _fileName, ID3D11Device* _GD)
{
	string useFileName = "../Models/" + _fileName + ".txt";
	//open file
	ifstream meshFile;
	meshFile.open(useFileName);

	//what data does this file give
	m_texCoords = false;
	m_colour = false;

	char texOrColour;
	meshFile >> texOrColour;

	if (texOrColour == 'T')
	{
		m_texCoords = true;
		//get texture fileName
		char  texFileName[256];
		meshFile >> texFileName;

		string fullfilename = "../Assets/";
		fullfilename += texFileName;
		fullfilename += ".dds";

		//load texture 
		HRESULT hr = CreateDDSTextureFromFile(_GD, Helper::charToWChar(fullfilename.c_str()), nullptr, &m_pTextureRV);	
		assert(hr == S_OK);
	}
	else
	{
		m_colour = true;
	}

	//get number of vertices
	int numVerts = 0;
	meshFile >> numVerts;
	myVertex* vertices = new myVertex[numVerts];

	//load verts
	int dummy;
	for (int i = 0; i< numVerts; i++)
	{
		meshFile >> dummy >> vertices[i].Pos.x >> vertices[i].Pos.y >> vertices[i].Pos.z;

		if (m_texCoords)
		{
			meshFile >> vertices[i].texCoord.x >> vertices[i].texCoord.y;
			vertices[i].Color = Color(1.0f, 1.0f, 1.0f, 1.0f);
		}

		if (m_colour)
		{
			float R, G, B, A;
			meshFile >> R >> G >> B >> A;
			vertices[i].Color = Color(R, G, B, A);
			vertices[i].texCoord = Vector2::One;
		}
	}

	//load indices
	meshFile >> m_numPrims;
	WORD* indices = new WORD[3 * m_numPrims];
	for (unsigned int i = 0; i<m_numPrims; i++)
	{
		WORD V1, V2, V3;
		meshFile >> dummy >> V1 >> V2 >> V3;

		indices[3 * i] = V1;
		indices[3 * i + 1] = V2;
		indices[3 * i + 2] = V3;

		//build normals
		Vector3 norm;
		Vector3 vec1 = vertices[V1].Pos - vertices[V2].Pos;
		Vector3 vec2 = vertices[V3].Pos - vertices[V2].Pos;
		norm = vec1.Cross(vec2);
		norm.Normalize();

		vertices[V1].Norm = norm;
		vertices[V2].Norm = norm;
		vertices[V3].Norm = norm;
	}

	BuildIB(_GD, indices);
	BuildVB(_GD, numVerts, vertices);

	//tidy up
	meshFile.close();
	delete[] vertices;
}

FileVBGO::~FileVBGO()
{

}