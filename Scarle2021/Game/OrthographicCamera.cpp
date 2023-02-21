#include "pch.h"
#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(float camera_width, float camera_height, float near, float far,
	XMVECTOR camera_position, XMVECTOR camera_target, XMVECTOR camera_up)
	
{
	
}

OrthographicCamera::~OrthographicCamera()
{

}

void OrthographicCamera::Tick(GameData* _GD)
{
	GameObject::Tick(_GD);

	view_matrix = XMMatrixLookAtLH(camera_position, camera_target, camera_up);
	world_view_projection_matrix = projection_matrix * view_matrix;
}

void OrthographicCamera::Draw(DrawData* _DD)
{
	_DD;
	//standard camera doesn't draw ANYTHING
}

void OrthographicCamera::CameraLeft()
{
	camera_position += XMVectorSet(-camera_speed, 0.0f, 0.0f, 0.0f);
}

void OrthographicCamera::CameraRight()
{
	camera_position += XMVectorSet(camera_speed, 0.0f, 0.0f, 0.0f);
}

void OrthographicCamera::CameraUp()
{
	camera_position += XMVectorSet(0.0f, camera_speed, 0.0f, 0.0f);
}

void OrthographicCamera::CameraDown()
{
	camera_position += XMVectorSet(0.0f, -camera_speed, 0.0f, 0.0f);
}

void OrthographicCamera::RecalculateViewMatrix()
{
}
