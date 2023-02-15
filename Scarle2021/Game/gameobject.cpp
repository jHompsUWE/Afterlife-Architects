#include "pch.h"
#include "gameobject.h"
#include "GameData.h"

GameObject::GameObject()
{
	//set the Gameobject to the origin with no rotation and unit scaling 
	m_pos = Vector3::Zero;
	m_pitch = 0.0f;
	m_yaw = 0.0f;
	m_roll = 0.0f;
	m_scale = Vector3::One;

	m_worldMat = Matrix::Identity;
	m_fudge = Matrix::Identity;
}

GameObject::~GameObject()
{

}

void GameObject::Tick(GameData* _GD)
{
	if (m_physicsOn)
	{
		Vector3 newVel = m_vel + _GD->m_dt * (m_acc - m_drag*m_vel);
		Vector3 newPos = m_pos + _GD->m_dt * m_vel;

		m_vel = newVel;
		m_pos = newPos;
	}

	//build up the world matrix depending on the new position of the GameObject
	//the assumption is that this class will be inherited by the class that ACTUALLY changes this
	Matrix  scaleMat = Matrix::CreateScale(m_scale);
	m_rotMat = Matrix::CreateFromYawPitchRoll(m_yaw, m_pitch, m_roll); //possible not the best way of doing this!
	Matrix  transMat = Matrix::CreateTranslation(m_pos);

	m_worldMat = m_fudge * scaleMat * m_rotMat * transMat;

	//zero acceleration ready for the next time round
	m_acc = Vector3::Zero;
}