#include "pch.h"
#include "GPGO.h"
#include "DrawData.h"
#include "camera.h"

GPGO::GPGO(ID3D11DeviceContext* _pd3dImmediateContext, GPGO_TYPE _type, float* _colour, float* _params):m_colour(_colour),m_type(_type)
{
	if (_params)
	{
		switch (_type)
		{
		case GPGO_BOX:
			shape = GeometricPrimitive::CreateBox(_pd3dImmediateContext, *((XMFLOAT3*)_params));
			break;
		case GPGO_CONE:
			shape = GeometricPrimitive::CreateCone(_pd3dImmediateContext,_params[0],_params[1],(size_t)_params[2]);
			break;
		case GPGO_CUBE:
			shape = GeometricPrimitive::CreateCube(_pd3dImmediateContext,_params[0]);
			break;
		case GPGO_CYLINDER:
			shape = GeometricPrimitive::CreateCylinder(_pd3dImmediateContext, _params[0], _params[1], (size_t)_params[2]);
			break;
		case GPGO_DODECAHEDRON:
			shape = GeometricPrimitive::CreateDodecahedron(_pd3dImmediateContext,_params[0]);
			break;
		case GPGO_GEOSPHERE:
			shape = GeometricPrimitive::CreateGeoSphere(_pd3dImmediateContext, _params[0], (size_t)_params[1]);
			break;
		case GPGO_ICOSAHEDRON:
			shape = GeometricPrimitive::CreateIcosahedron(_pd3dImmediateContext,_params[0]);
			break;
		case GPGO_OCTAHEDRON:
			shape = GeometricPrimitive::CreateOctahedron(_pd3dImmediateContext, _params[0]);
			break;
		case GPGO_SPHERE:
			shape = GeometricPrimitive::CreateSphere(_pd3dImmediateContext, _params[0], (size_t)_params[1]);
			break;
		case GPGO_TEAPOT:
			shape = GeometricPrimitive::CreateTeapot(_pd3dImmediateContext, _params[0], (size_t)_params[1]);
			break;
		case GPGO_TETRAHEDRON:
			shape = GeometricPrimitive::CreateTetrahedron(_pd3dImmediateContext, _params[0]);
			break;
		case GPGO_TORUS:
			shape = GeometricPrimitive::CreateTorus(_pd3dImmediateContext, _params[0], _params[1], (size_t)_params[2]);
			break;
		}
	}
	else
	{
		switch (_type)
		{
		case GPGO_BOX:
			shape = GeometricPrimitive::CreateBox(_pd3dImmediateContext, XMFLOAT3(10.0f,10.0f,10.f));
				break;
		case GPGO_CONE:
			shape = GeometricPrimitive::CreateCone(_pd3dImmediateContext);
			break;
		case GPGO_CUBE:
			shape = GeometricPrimitive::CreateCube(_pd3dImmediateContext);
			break;
		case GPGO_CYLINDER:
			shape = GeometricPrimitive::CreateCylinder(_pd3dImmediateContext);
			break;
		case GPGO_DODECAHEDRON:
			shape = GeometricPrimitive::CreateDodecahedron(_pd3dImmediateContext);
			break;
		case GPGO_GEOSPHERE:
			shape = GeometricPrimitive::CreateGeoSphere(_pd3dImmediateContext);
			break;
		case GPGO_ICOSAHEDRON:
			shape = GeometricPrimitive::CreateIcosahedron(_pd3dImmediateContext);
			break;
		case GPGO_OCTAHEDRON:
			shape = GeometricPrimitive::CreateOctahedron(_pd3dImmediateContext);
			break;
		case GPGO_SPHERE:
			shape = GeometricPrimitive::CreateSphere(_pd3dImmediateContext);
			break;
		case GPGO_TEAPOT:
			shape = GeometricPrimitive::CreateTeapot(_pd3dImmediateContext);
			break;
		case GPGO_TETRAHEDRON:
			shape = GeometricPrimitive::CreateTetrahedron(_pd3dImmediateContext);
			break;
		case GPGO_TORUS:
			shape = GeometricPrimitive::CreateTorus(_pd3dImmediateContext);
			break;
		}
		
	}
}

void GPGO::Tick(GameData* _GD)
{
	GameObject::Tick(_GD);
}

void GPGO::Draw(DrawData* _DD)
{
	shape->Draw(m_worldMat,_DD->m_cam->GetView(),_DD->m_cam->GetProj(),m_colour);
}
