#include "pch.h"
#include "OrthographicCamera.h"
#include <iostream>

OrthographicCamera::OrthographicCamera(int win_x, int win_y)
	
{
	_win_x = win_x;
	_win_y = win_y;
	//camera_position = Vector3(4, 10, 0);
}

OrthographicCamera::~OrthographicCamera()
{

}

void OrthographicCamera::Tick(GameData* _GD)
{
	Input(_GD);
	MouseInput(_GD, _win_x, _win_y);
	RecalculateProjViewPos();
	GameObject::Tick(_GD);
}

void OrthographicCamera::Draw(DrawData* _DD)
{
	_DD;
	//standard camera doesn't draw ANYTHING
}

void OrthographicCamera::Input(GameData* _GD)
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


	if (_GD->mouse_state.scrollWheelValue < scroll_value)
	{
		scroll_value = _GD->mouse_state.scrollWheelValue;
		
		ZoomIn();

		zoom_value += 0.1f;
	}
	if (_GD->mouse_state.scrollWheelValue > scroll_value)
	{
		scroll_value = _GD->mouse_state.scrollWheelValue;
		
		ZoomOut();
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

void OrthographicCamera::MoveUp()
{
	camera_target += vertical_movement;
	std::cout << "Up" << std::endl;
}

void OrthographicCamera::MoveDown()
{
	camera_target -= vertical_movement;
	std::cout << "Down" << std::endl;
}

void OrthographicCamera::MoveLeft()
{
	camera_target -= horizontal_movement;
	std::cout << "Left" << std::endl;
}

void OrthographicCamera::MoveRight()
{
	camera_target += horizontal_movement;
	std::cout << "Right" << std::endl;
}

void OrthographicCamera::ZoomIn()
{
	if (zoom_value > zoom_max)
	{
		zoom_value = zoom_max;
	}

	zoom_value += 0.1f;
}

void OrthographicCamera::ZoomOut()
{
	if (zoom_value < zoom_min)
	{
		zoom_value = zoom_min;
	}

	zoom_value -= 0.1f;
}

void OrthographicCamera::RecalculateProjViewPos()
{
	camera_position = camera_target + camera_constraint;
	projection_matrix = XMMatrixOrthographicLH(camera_height * zoom_value, camera_width * zoom_value,
		near_plane * zoom_value, far_plane * zoom_value);
	view_matrix = XMMatrixLookAtLH(camera_position, camera_target, camera_up);
}
