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

	if (_GD->keyboard_state.W)
	{
		CameraForward(0.1f);
	}

	if (_GD->keyboard_state.S)
	{
		CameraBackward(0.1f);
	}

	if (_GD->mouse_state.scrollWheelValue < scroll_value)
	{
		scroll_value = _GD->mouse_state.scrollWheelValue;
		zoom_value += 0.1f;

		Zoom(zoom_value);
	}
	if (_GD->mouse_state.scrollWheelValue > scroll_value)
	{
		scroll_value = _GD->mouse_state.scrollWheelValue;
		zoom_value -= 0.1f;

		Zoom(zoom_value);
	}
}

void OrthographicCamera::Draw(DrawData* _DD)
{
	_DD;
	//standard camera doesn't draw ANYTHING
}

void OrthographicCamera::UpdateProjectionMatrix()
{
	projection_matrix = XMMatrixOrthographicLH(camera_height * zoom_value, camera_width * zoom_value,
		near_plane * zoom_value, far_plane * zoom_value);
}

void OrthographicCamera::CameraForward(float distance)
{
	XMVECTOR movement = XMVectorMultiply(forward, XMVectorReplicate(distance));
	camera_position = XMVectorAdd(camera_position, movement);
	camera_target = XMVectorAdd(camera_target, movement);
	view_matrix = XMMatrixLookAtLH(camera_position, camera_target, camera_up);

	std::cout << "Camera Forward" << std::endl;
}

void OrthographicCamera::CameraBackward(float distance)
{
	CameraForward(-distance);

	std::cout << "Camera Backward" << std::endl;
}

void OrthographicCamera::Zoom(float amount)
{
	if (amount < zoom_min)
	{
		amount = zoom_min;
	}

	if (amount > zoom_max)
	{
		amount = zoom_max;
	}

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
