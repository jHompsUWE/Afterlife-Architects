#include "pch.h"
#include "TPSCamera.h"
#include "GameData.h"

TPSCamera::TPSCamera(float _fieldOfView, float _aspectRatio, float _nearPlaneDistance, float _farPlaneDistance, Vector3 _up, Vector3 _dpos)
	:Camera(_fieldOfView, _aspectRatio, _nearPlaneDistance, _farPlaneDistance, _up)
{
	m_dpos = _dpos;
	target = Vector3::Zero;
}

TPSCamera::~TPSCamera()
{

}

void TPSCamera::Tick(GameData* _GD)
{
	if (_GD->mouse_state.scrollWheelValue < last_scroll_value)
	{
		// Zoom OUT
		last_scroll_value = _GD->mouse_state.scrollWheelValue;
		zoom += 1.0f;
		if (zoom > max_zoom)
		{
			zoom = max_zoom;
		}
	}
	else if (_GD->mouse_state.scrollWheelValue > last_scroll_value)
	{
		// Zoom IN
		last_scroll_value = _GD->mouse_state.scrollWheelValue;
		zoom -= 1.0f;
		if (zoom < min_zoom)
		{
			zoom = min_zoom;
		}
	}

	Vector3 verticalMove = speed * Vector3(1, 0, 1) * (zoom / max_zoom);
	if (_GD->keyboard_state.W)
	{
		// Move UP
		target -= verticalMove;
	}
	if (_GD->keyboard_state.S)
	{
		// Move DOWN
		target += verticalMove;
	}

	Vector3 horizontalMove = speed * Vector3(1, 0, -1) * (zoom / max_zoom);
	if (_GD->keyboard_state.A)
	{
		// Move LEFT
		target += horizontalMove;
	}
	if (_GD->keyboard_state.D)
	{
		// Move RIGHT
		target -= horizontalMove;
	}

	// Set position of cam at an offset of m_dpos from target
	m_pos = target + m_dpos;

	// Setup projection and view matrices
	m_projMat = XMMatrixOrthographicLH(3 * zoom, 2 * zoom, m_nearPlaneDistance, m_farPlaneDistance);
	m_viewMat = XMMatrixLookAtLH(m_pos, target, m_up);
	GameObject::Tick(_GD);
}

/// <summary>
/// Get the normalized directional vector of the camera
/// </summary>
/// <returns>Vector3 normalized directional vector of the camera</returns>
Vector3 TPSCamera::GetDirection()
{
	Vector3 cam_to_target = Vector3(target.x - m_pos.x, target.y - m_pos.y, target.z - m_pos.z);

	float magnitude = sqrt(pow(cam_to_target.x, 2) + pow(cam_to_target.y, 2) + pow(cam_to_target.z, 2));

	return Vector3(cam_to_target.x/magnitude, cam_to_target.y/magnitude, cam_to_target.z/magnitude);
}
