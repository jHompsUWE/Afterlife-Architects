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

	Vector3 verticalMove = speed * Vector3(0, 1, 0) * (zoom / max_zoom);
	if (_GD->keyboard_state.W)
	{
		// Move UP
		target += verticalMove;
	}
	if (_GD->keyboard_state.S)
	{
		// Move DOWN
		target -= verticalMove;
	}

	Vector3 horizontalMove = speed * Vector3(1, 0, 1) * (zoom / max_zoom);
	if (_GD->keyboard_state.A)
	{
		// Move LEFT
		target -= horizontalMove;
	}
	if (_GD->keyboard_state.D)
	{
		// Move RIGHT
		target += horizontalMove;
	}

	//Set up position of camera and target position of camera based on new position and orientation of target object
	Matrix rotCam = Matrix::CreateFromYawPitchRoll(PI/4, 0, 0);
	m_pos = target + Vector3::Transform(m_dpos, rotCam) ;

	//and then set up proj and view matrices
	m_projMat = XMMatrixOrthographicLH(4 * zoom, 3 * zoom, m_nearPlaneDistance, m_farPlaneDistance);
	m_viewMat = XMMatrixLookAtLH(m_pos, target, m_up);
	GameObject::Tick(_GD);
}

