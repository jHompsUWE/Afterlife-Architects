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
	Matrix rotCam = Matrix::CreateFromYawPitchRoll(m_targetObject->GetYaw(), 0.0f, 0.0f);
	m_target = m_targetObject->GetPos();
	m_pos = m_target + Vector3::Transform(m_dpos, rotCam) ;

	//and then set up proj and view matrices
	Camera::Tick(_GD);
}

