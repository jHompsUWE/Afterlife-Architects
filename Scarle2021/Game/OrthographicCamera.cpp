#include "pch.h"
#include "OrthographicCamera.h"
#include "GameData.h"
#include <iostream>

#include "NewEventManager.h"

OrthographicCamera::OrthographicCamera(float _near_plane, float _far_plane, Vector3 _offset) :
	near_plane(_near_plane), far_plane(_far_plane), offset(_offset)
{
	//win_x = _win_x;
	//win_x = _win_y;

	AL::NewEventManager::AddEventReceiver(this);
}

OrthographicCamera::~OrthographicCamera()
{
	AL::NewEventManager::RemoveEventReceiver(this);
}

void OrthographicCamera::Tick(GameData* _GD)
{
	// Calculate movement vectors here so it has access to delta time
	vertical_move = camera_speed * Vector3(1, 0, 1) * (zoom_value / zoom_max) * _GD->delta_time;
	horizontal_move = camera_speed * Vector3(1, 0, -1) * (zoom_value / zoom_max) * _GD->delta_time;
	
	RecalculateProjViewPos();
	GameObject::Tick(_GD);
}

void OrthographicCamera::MouseInput(GameData* _GD, int win_x, int win_y)
{
	if (mouse_pos.x > win_x - boundary)
	{
		MoveRight();
	}
	if (mouse_pos.x < boundary)
	{
		MoveLeft();
	}

	if (mouse_pos.y > win_y - boundary)
	{
		MoveDown();
	}
	if (mouse_pos.y < boundary)
	{
		MoveUp();
	}
}

void OrthographicCamera::ReceiveEvents(const AL::Event& al_event)
{
	switch (al_event.type)
	{
	case AL::event_input:

		switch (al_event.input.action)
		{
			case AL::Input::camera_up:
				MoveUp();
				break;

			case AL::Input::camera_down:
				MoveDown();
				break;

			case AL::Input::camera_left:
				MoveLeft();
				break;

			case AL::Input::camera_right:
				MoveRight();
				break;

			default:
				break;
		}

		break;

	case AL::event_cursor_move:
		mouse_pos.x = al_event.cursor_moved.pos_x;
		mouse_pos.y = al_event.cursor_moved.pos_y;
		break;

	case AL::event_cursor_interact:

		switch (al_event.cursor_interact.action)
		{
			case AL::Cursor::scroll_up:
				ZoomIn(1);
				break;

			case AL::Cursor::scroll_down:
				ZoomOut(1);
				break;

			default:
				break;
		}
		break;

	case AL::event_ui:
		switch (al_event.ui.action)
		{
		case AL::UI::button_zoom_in:
			ZoomIn(10);
			break;
		case AL::UI::button_zoom_out:
			ZoomOut(10);
			break;
		}

	default:
		break;
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
void OrthographicCamera::ZoomIn(float magnitude)
{
	zoom_value -= magnitude;
	if (zoom_value < zoom_min)
	{
		zoom_value = zoom_min;
	}
}

/// <summary>
/// Zooms camera out, clamped by zoom_max
/// </summary>
void OrthographicCamera::ZoomOut(float magnitude)
{
	zoom_value += magnitude;
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
