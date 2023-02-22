#include "pch.h"
#include "OrthographicCamera.h"
#include <iostream>

OrthographicCamera::OrthographicCamera()
	
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

void OrthographicCamera::UpdateProjectionMatrix()
{
	projection_matrix = XMMatrixOrthographicLH(camera_height * zoom_factor, camera_width * zoom_factor,
		near_plane * zoom_factor, far_plane * zoom_factor);
}

void OrthographicCamera::CameraForward(float distance)
{
	XMVECTOR movement = XMVectorMultiply(forward, XMVectorReplicate(distance));
	camera_position = XMVectorAdd(camera_position, movement);
	camera_target = XMVectorAdd(camera_target, movement);
	view_matrix = XMMatrixLookAtLH(camera_position, camera_target, camera_up);

	std::cout << "Camera Forwards" << std::endl;
}

void OrthographicCamera::CameraBackward(float distance)
{
	CameraForward(-distance);

	std::cout << "Camera Backwards" << std::endl;
}

void OrthographicCamera::ZoomIn(float amount)
{
	zoom_factor -= amount;
	if (zoom_factor < 0.1f)
	{
		zoom_factor = 0.1f;
	}

	UpdateProjectionMatrix();
}

void OrthographicCamera::ZoomOut(float amount)
{
	zoom_factor += amount;

	UpdateProjectionMatrix();
}

void OrthographicCamera::CameraRotateLeft()
{
	camera_position += XMVectorSet(-camera_speed, 0.0f, 0.0f, 0.0f);
}

void OrthographicCamera::CameraRotateRight()
{
	camera_position += XMVectorSet(camera_speed, 0.0f, 0.0f, 0.0f);
}

void OrthographicCamera::CameraRotateDown()
{
	camera_position += XMVectorSet(0.0f, camera_speed, 0.0f, 0.0f);
}

void OrthographicCamera::CameraRotateUp()
{
	camera_position += XMVectorSet(0.0f, -camera_speed, 0.0f, 0.0f);
	std::cout << "Camera Up" << std::endl;
}

void OrthographicCamera::RecalculateViewMatrix()
{
}
