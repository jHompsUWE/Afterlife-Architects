#include "pch.h"
#include "OrthographicCamera.h"
#include "GameData.h"
#include <iostream>

OrthographicCamera::OrthographicCamera(float _near_plane, float _far_plane, Vector3 _offset) :
	near_plane(_near_plane), far_plane(_far_plane), offset(_offset)
{
	//win_x = _win_x;
	//win_x = _win_y;
}

OrthographicCamera::~OrthographicCamera()
{

}

void OrthographicCamera::Tick(GameData* _GD)
{
	// Calculate movement vectors here so it has access to delta time
	vertical_move = camera_speed * Vector3(1, 0, 1) * (zoom_value / zoom_max) * _GD->delta_time;
	horizontal_move = camera_speed * Vector3(1, 0, -1) * (zoom_value / zoom_max) * _GD->delta_time;

	ReadInput(_GD);
	//MouseInput(_GD, win_x, win_y);
	RecalculateProjViewPos();
	GameObject::Tick(_GD);
}

/// <summary>
/// CHANGE THIS TO NEW EVENT SYSTEM WHEN DONE
/// </summary>
/// <param name="_GD"></param>
void OrthographicCamera::ReadInput(GameData* _GD)
{
	if (_GD->keyboard_state.W)
	{
		MoveUp();
	}

	if (_GD->keyboard_state.S)
	{
		MoveDown();
	}

	if (_GD->keyboard_state.A)
	{
		MoveLeft();
	}

	if (_GD->keyboard_state.D)
	{
		MoveRight();
	}

	// Compare current scroll value with last scroll value
	if (_GD->mouse_state.scrollWheelValue < last_scroll_value)
	{
		// Mouse scrolled down
		last_scroll_value = _GD->mouse_state.scrollWheelValue;
		ZoomOut();
	}
	else if (_GD->mouse_state.scrollWheelValue > last_scroll_value)
	{
		// Mouse scrolled up
		last_scroll_value = _GD->mouse_state.scrollWheelValue;
		ZoomIn();
	}
}

void OrthographicCamera::MouseInput(GameData* _GD, int win_x, int win_y)
{
	if (_GD->mouse_state.x > win_x - boundary)
	{
		MoveRight();
	}
	if (_GD->mouse_state.x < boundary)
	{
		MoveLeft();
	}

	if (_GD->mouse_state.y > win_y - boundary)
	{
		MoveDown();
	}
	if (_GD->mouse_state.y < boundary)
	{
		MoveUp();
	}
}

/// <summary>
/// Moves camera up
/// </summary>
void OrthographicCamera::MoveUp()
{
	camera_target += vertical_move;
}

/// <summary>
/// Moves camera down
/// </summary>
void OrthographicCamera::MoveDown()
{
	camera_target -= vertical_move;
}

/// <summary>
/// Moves camera left
/// </summary>
void OrthographicCamera::MoveLeft()
{
	camera_target -= horizontal_move;
}

/// <summary>
/// Moves camera right
/// </summary>
void OrthographicCamera::MoveRight()
{
	camera_target += horizontal_move;
}

/// <summary>
/// Zooms camera in, clamped by zoom_in
/// </summary>
void OrthographicCamera::ZoomIn()
{
	zoom_value -= 1.0f;
	if (zoom_value < zoom_min)
	{
		zoom_value = zoom_min;
	}
}

/// <summary>
/// Zooms camera out, clamped by zoom_max
/// </summary>
void OrthographicCamera::ZoomOut()
{
	zoom_value += 1.0f;
	if (zoom_value > zoom_max)
	{
		zoom_value = zoom_max;
	}
}

/// <summary>
/// Updates the position of camera, projection and view matrices
/// </summary>
void OrthographicCamera::RecalculateProjViewPos()
{
	// Set position of cam at an offset of m_dpos from target
	m_pos = camera_target + offset;

	// Setup projection and view matrices
	// Window is 1080x720 so make projection matrix in 3:2 ratio
	projection_matrix = XMMatrixOrthographicLH(3 * zoom_value, 2 * zoom_value, near_plane, far_plane);
	view_matrix = XMMatrixLookAtLH(m_pos, camera_target, up);
}

/// <summary>
/// Get the normalized directional vector of the camera
/// </summary>
/// <returns>Vector3 normalized directional vector of the camera</returns>
Vector3 OrthographicCamera::GetDirection()
{
	Vector3 cam_to_target = Vector3(camera_target.x - m_pos.x, camera_target.y - m_pos.y, camera_target.z - m_pos.z);

	float magnitude = sqrt(pow(cam_to_target.x, 2) + pow(cam_to_target.y, 2) + pow(cam_to_target.z, 2));

	return Vector3(cam_to_target.x / magnitude, cam_to_target.y / magnitude, cam_to_target.z / magnitude);
}
