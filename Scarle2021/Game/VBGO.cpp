#include "pch.h"
#include <Windows.h>
#include <d3dcompiler.h>
#include "DDSTextureLoader.h"
#include "VBGO.h"
#include "drawdata.h"
#include "vertex.h"
#include "camera.h"
#include "light.h"
#include "Helper.h"

#define DESTROY( x ) if( x ){ x->Release(); x = nullptr;}

//the base Game Object drawn using a Vertex and Index Buffer
//all of the main aspects of drawing it have a default which is pointed to by a static pointer
//this is only used if the version for this object is not set to nullptr

using namespace DirectX;

//default vertexshader
ID3D11VertexShader*			VBGO::s_pVertexShader = nullptr;
//default vertex layout
ID3D11InputLayout*			VBGO::s_pVertexLayout = nullptr;
//default pixelshader
ID3D11PixelShader*			VBGO::s_pPixelShader = nullptr;
//default texture (white square)
ID3D11ShaderResourceView*	VBGO::s_pTextureRV = nullptr;
//deafult const buffer
//GPU side
ID3D11Buffer*				VBGO::s_pConstantBuffer = nullptr;
//CPU side	
ConstantBuffer*				VBGO::s_pCB = nullptr;
//default sampler
ID3D11SamplerState*			VBGO::s_pSampler = nullptr;
//default raster state
ID3D11RasterizerState*		VBGO::s_pRasterState = nullptr;

VBGO::VBGO()
{
	//set up Buffers
	m_VertexBuffer = NULL;
	m_IndexBuffer = NULL;
	m_numPrims = 0;

	m_pVertexShader = nullptr;
	m_pVertexLayout = nullptr;
	m_pPixelShader = nullptr;
	m_pTextureRV = nullptr;
	m_pConstantBuffer = nullptr;
	m_pCB = nullptr;
	m_pSampler = nullptr;
	m_pRasterState = nullptr;

	m_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	//NOTE WE DON'T CREATE ANYTHING HERE
	//WHATEVER INHERITS THIS WILL DO THAT
}

VBGO::~VBGO()
{
	//BUT WE DO TIDY THEM AWAY
	DESTROY(m_VertexBuffer);
	DESTROY(m_IndexBuffer);
	DESTROY(m_pVertexShader);
	DESTROY(m_pVertexLayout);
	DESTROY(m_pPixelShader);
	DESTROY(m_pTextureRV);
	DESTROY(m_pConstantBuffer);
	//if (m_pCB) delete m_pCB; delete this where created as there will know its type
	DESTROY(m_pSampler);
	DESTROY(m_pRasterState);
}

void VBGO::Tick(GameData* _GD)
{
	GameObject::Tick(_GD);
}

void VBGO::Draw(DrawData* _DD)
{
	//set raster state
	ID3D11RasterizerState* useRasterS = m_pRasterState ? m_pRasterState : s_pRasterState;
	_DD->m_pd3dImmediateContext->RSSetState(useRasterS);

	//set standard Constant Buffer to match this object
	s_pCB->world = m_worldMat.Transpose();
	s_pCB->rot = m_rotMat.Transpose();

	//Set vertex buffer
	UINT stride = sizeof(myVertex);
	UINT offset = 0;
	_DD->m_pd3dImmediateContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// Set index buffer
	_DD->m_pd3dImmediateContext->IASetIndexBuffer(m_IndexBuffer, m_IndexFormat, 0);

	//update the Constant Buffer in classes that inherit from this then push to the GPU here
	ID3D11Buffer* useCB = m_pConstantBuffer ? m_pConstantBuffer : s_pConstantBuffer;
	void* useCBData = m_pCB ? m_pCB : s_pCB;

	_DD->m_pd3dImmediateContext->UpdateSubresource(useCB, 0, NULL, useCBData, 0, 0);
	_DD->m_pd3dImmediateContext->VSSetConstantBuffers(0, 1, &useCB);
	_DD->m_pd3dImmediateContext->PSSetConstantBuffers(0, 1, &useCB);

	//unless it has it own set them to the static defaults

	//set primitive type used
	_DD->m_pd3dImmediateContext->IASetPrimitiveTopology(m_topology);

	//set  vertex layout
	//note that if you do use this you'll need to change the stride and offset above
	ID3D11InputLayout* useLayout = m_pVertexLayout ? m_pVertexLayout : s_pVertexLayout;
	_DD->m_pd3dImmediateContext->IASetInputLayout(useLayout);

	//set Vertex Shader
	ID3D11VertexShader* useVS = m_pVertexShader ? m_pVertexShader : s_pVertexShader;
	_DD->m_pd3dImmediateContext->VSSetShader(useVS, NULL, 0);

	//set Pixel Shader
	ID3D11PixelShader* usePS = m_pPixelShader ? m_pPixelShader : s_pPixelShader;
	_DD->m_pd3dImmediateContext->PSSetShader(usePS, NULL, 0);

	//set Texture
	ID3D11ShaderResourceView* useTex = m_pTextureRV ? m_pTextureRV : s_pTextureRV;
	_DD->m_pd3dImmediateContext->PSSetShaderResources(0, 1, &useTex);

	//set sampler
	ID3D11SamplerState* useSample = m_pSampler ? m_pSampler : s_pSampler;
	_DD->m_pd3dImmediateContext->PSSetSamplers(0, 1, &useSample);

	//and draw
	_DD->m_pd3dImmediateContext->DrawIndexed(3 * m_numPrims, 0, 0);//number here will need to change depending on the primative topology!
}

//--------------------------------------------------------------------------------------
// Compile the  shader
//--------------------------------------------------------------------------------------
HRESULT VBGO::CompileShaderFromFile(WCHAR* _szFileName, LPCSTR _szEntryPoint, LPCSTR _szShaderModel, ID3DBlob** _ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorBlob;
	hr = D3DCompileFromFile(_szFileName, NULL, NULL, _szEntryPoint, _szShaderModel,
		dwShaderFlags, 0, _ppBlobOut, &pErrorBlob);
	if (FAILED(hr))
	{
		if (pErrorBlob != NULL)
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
		return hr;
	}

	return S_OK;
}

void VBGO::Init(ID3D11Device* _GD)
{
	//set up all static stuff

	//default vertex shader
	ID3DBlob* pVertexShaderBuffer = NULL;
	HRESULT hr = CompileShaderFromFile(Helper::charToWChar("../Assets/shader.fx"), "VS", "vs_4_0_level_9_1", &pVertexShaderBuffer);
	_GD->CreateVertexShader(pVertexShaderBuffer->GetBufferPointer(), pVertexShaderBuffer->GetBufferSize(), NULL, &s_pVertexShader);

	//default pixelshader
	ID3DBlob* pPixelShaderBuffer = NULL;
	hr = CompileShaderFromFile(Helper::charToWChar("../Assets/shader.fx"), "PS", "ps_4_0_level_9_1", &pPixelShaderBuffer);
	_GD->CreatePixelShader(pPixelShaderBuffer->GetBufferPointer(), pPixelShaderBuffer->GetBufferSize(), NULL, &s_pPixelShader);

	//default vertex layout
	_GD->CreateInputLayout(myVertexLayout, ARRAYSIZE(myVertexLayout), pVertexShaderBuffer->GetBufferPointer(),
		pVertexShaderBuffer->GetBufferSize(), &s_pVertexLayout);

	//default texture (white square)
	hr = CreateDDSTextureFromFile(_GD, L"../Assets/white.dds", nullptr, &s_pTextureRV);

	//deafult const buffer
	//GPU side
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	hr = _GD->CreateBuffer(&bd, NULL, &s_pConstantBuffer);
	//CPU side
	s_pCB = new ConstantBuffer();
	ZeroMemory(s_pCB, sizeof(ConstantBuffer));

	//default sampler
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(SamDesc));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.MipLODBias = 0.0f;
	SamDesc.MaxAnisotropy = 1;
	SamDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	SamDesc.BorderColor[0] = SamDesc.BorderColor[1] = SamDesc.BorderColor[2] = SamDesc.BorderColor[3] = 0;
	SamDesc.MinLOD = 0;
	SamDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = _GD->CreateSamplerState(&SamDesc, &s_pSampler);

	//Setup Raster State
	D3D11_RASTERIZER_DESC rasterDesc;
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = true;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	// Create the rasterizer state from the description we just filled out.
	hr = _GD->CreateRasterizerState(&rasterDesc, &s_pRasterState);
}

void VBGO::UpdateConstantBuffer(DrawData* _DD)
{
	//you'll need your own version of this if you use a different Constant Buffer
	s_pCB->view = _DD->m_cam->GetView().Transpose();
	s_pCB->projection = _DD->m_cam->GetProj().Transpose();
	if (_DD->m_light)
	{
		s_pCB->lightCol = _DD->m_light->GetColour();
		s_pCB->lightPos = _DD->m_light->GetPos();
		s_pCB->ambientCol = _DD->m_light->GetAmbCol();
	}
}

void VBGO::CleanUp()
{
	//clear away all the static objects
	DESTROY(s_pVertexShader);
	DESTROY(s_pVertexLayout);
	DESTROY(s_pPixelShader);
	DESTROY(s_pTextureRV);
	DESTROY(s_pConstantBuffer);
	if (s_pCB)
	{
		delete s_pCB;
		s_pCB = nullptr;
	}
	DESTROY(s_pSampler);
	DESTROY(s_pRasterState);
}

void VBGO::BuildIB(ID3D11Device* _GD, void* _indices)
{
	//structures from creating buffers
	D3D11_BUFFER_DESC bd;
	D3D11_SUBRESOURCE_DATA InitData;
	HRESULT hr = S_OK;

	//build index buffer
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * 3 * m_numPrims;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = _indices;
	hr = _GD->CreateBuffer(&bd, &InitData, &m_IndexBuffer);
}

void VBGO::BuildVB(ID3D11Device* _GD, int _numVerts, void* _vertices)
{
	//structures from creating buffers
	D3D11_BUFFER_DESC bd;
	D3D11_SUBRESOURCE_DATA InitData;
	HRESULT hr = S_OK;

	//build vertex buffer
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(myVertex) * _numVerts;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = _vertices;
	hr = _GD->CreateBuffer(&bd, &InitData, &m_VertexBuffer);
}