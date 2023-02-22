#include "pch.h"
#include "TPSCamera.h"
#include "GameData.h"

TPSCamera::TPSCamera(float _fieldOfView, float _aspectRatio, float _nearPlaneDistance, float _farPlaneDistance, GameObject* _target, Vector3 _up, Vector3 _dpos)
	:Camera(_fieldOfView, _aspectRatio, _nearPlaneDistance, _farPlaneDistance, _up)
{
	m_targetObject = _target;
	m_dpos = _dpos;
}

TPSCamera::~TPSCamera()
{

}

void TPSCamera::Tick(GameData* _GD)
{
	//Set up position of camera and target position of camera based on new position and orientation of target object
	Matrix rotCam = Matrix::CreateFromYawPitchRoll(45 * PI/180, 0, 0);
	m_target = m_targetObject->GetPos();
	m_pos = m_target + Vector3::Transform(m_dpos, rotCam) ;

	//and then set up proj and view matrices
	m_projMat = XMMatrixOrthographicLH(40, 30, m_nearPlaneDistance, m_farPlaneDistance);
	//m_projMat = XMMatrixOrthographicOffCenterLH(left, right, bottom, top, m_nearPlaneDistance, m_farPlaneDistance);
	m_viewMat = XMMatrixLookAtLH(m_pos, m_target, m_up);
	GameObject::Tick(_GD);

	//Camera::Tick(_GD);
}

