#pragma once
#include <vector>
#include <memory>
#include <iostream>

#include <DDSTextureLoader.h>
#include <SimpleMath.h>
#include "Helper.h"

#include "ZoneType.h"
#include "StructureType.h"
#include "PlaneType.h"

class TextureManager
{
public:
	TextureManager(ID3D11Device* GD);
	~TextureManager();

	ID3D11ShaderResourceView* GetTextureZone(ZoneType zone);
	ID3D11ShaderResourceView* GetTextureStructure(StructureType structure, PlaneType plane);

	DirectX::SimpleMath::Vector2 GetSizeStructure(StructureType structure, PlaneType plane);

protected:

private:
	void AddTextureZone(ID3D11Device* GD, std::string file_name);
	void AddTextureStructure(ID3D11Device* GD, std::string file_name, PlaneType plane);

	std::vector<ID3D11ShaderResourceView*> texture_zone; // Vector that holds the texture for zones
	std::vector<ID3D11ShaderResourceView*> texture_heaven_structure; // Vector that holds the texture for Heaven structures
	std::vector<ID3D11ShaderResourceView*> texture_hell_structure; // Vector that holds the texture for Hell structures
};

