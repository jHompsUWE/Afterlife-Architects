#include "pch.h"
#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(float _width, float _height, Vector3 _up, Vector3 _target)
	: projection_matrix(DirectX::XMMatrixOrthographicLH(_width, _height, -1.0f, 1.0f))//near and far set to -1 and 1
{
	width = _width;
	height = _height;

	target = _target;
	up = _up;
}

OrthographicCamera::~OrthographicCamera()
{

}

void OrthographicCamera::Tick(GameData* _GD)
{
	//projection_matrix = Matrix::CreateOrthographic(width, height, -1.0f, 1.0f);
	//view_matrix = Matrix::CreateLookAt(_position, target, up);
	GameObject::Tick(_GD);
}

void OrthographicCamera::Draw(DrawData* _DD)
{
	_DD;
	//standard camera doesn't draw ANYTHING
}

void OrthographicCamera::RecalculateViewMatrix()
{
	//atrix transform = DirectX::XMMatrixTranslationFromVector(Vector4(_position));

	//view_matrix = DirectX::XMMatrixInverse(transform);

	//view_projection_matrix = projection_matrix * view_matrix;

}
