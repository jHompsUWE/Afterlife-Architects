#include "pch.h"
#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far)
	
{
	
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
