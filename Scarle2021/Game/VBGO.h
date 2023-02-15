#ifndef _VB_GO_H_
#define _VB_GO_H_
#include "gameobject.h"
#include "ConstantBuffer.h"

//=================================================================
//the base Game Object drawn using a Vertex and Index Buffer
//all of the main aspects of drawing it have a default which is pointed to by a static pointer
//this is only used if the version for this object is not set to nullptr
//=================================================================

class VBGO :public GameObject
{
public:
	VBGO();
	virtual ~VBGO();

	virtual void Tick(GameData* _GD) override;
	virtual void Draw(DrawData* _DD) override;

	//set up and then destroy all static default render stuff for VBGOs
	static void Init(ID3D11Device* _GD);//Graphics Device NOT GameData
	static void CleanUp();

	//Update static const buffer required for deafult rendering
	static void UpdateConstantBuffer(DrawData* _DD);

protected:

	//Direct X information for the model for this GameObject
	ID3D11Buffer* m_VertexBuffer;
	ID3D11Buffer* m_IndexBuffer;
	DXGI_FORMAT m_IndexFormat = DXGI_FORMAT_R16_UINT;
	UINT m_numPrims;

	//vertex topology in VB
	D3D_PRIMITIVE_TOPOLOGY m_topology;

	//default vertexshader
	static ID3D11VertexShader*     s_pVertexShader;
	//default vertex layout
	static ID3D11InputLayout*      s_pVertexLayout;
	//default pixelshader
	static ID3D11PixelShader*      s_pPixelShader;
	//default texture (white square)
	static ID3D11ShaderResourceView* s_pTextureRV;
	//deafult const buffer
	static ID3D11Buffer*           s_pConstantBuffer;	//GPU side
	static ConstantBuffer*			s_pCB;				//CPU side
	//default sampler
	static ID3D11SamplerState*		s_pSampler;
	//default raster state
	static ID3D11RasterizerState*  s_pRasterState;

	//my vertexshader
	ID3D11VertexShader*     m_pVertexShader;
	//my vertex layout
	ID3D11InputLayout*      m_pVertexLayout;
	//my pixelshader
	ID3D11PixelShader*      m_pPixelShader;
	//my texture
	ID3D11ShaderResourceView* m_pTextureRV;
	//my const buffer
	ID3D11Buffer*           m_pConstantBuffer; //GPU side
	void*					m_pCB;//CPU side
								  //my sampler
	ID3D11SamplerState*		m_pSampler;
	//my raster state
	ID3D11RasterizerState*  m_pRasterState;

	//once populated build an Index Buffer
	void BuildIB(ID3D11Device* _GD, void* _indices);

	//once populated build a Vertex Buffer
	void BuildVB(ID3D11Device* _GD, int _numVerts, void* _vertices);

	static HRESULT CompileShaderFromFile(WCHAR* _szFileName, LPCSTR _szEntryPoint, LPCSTR _szShaderModel, ID3DBlob** _ppBlobOut);


};

#endif
