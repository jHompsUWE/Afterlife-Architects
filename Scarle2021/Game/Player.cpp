#include "pch.h"
#include "Player.h"
#include <dinput.h>
#include "GameData.h"

Player::Player(string _fileName, ID3D11Device* _pd3dDevice, IEffectFactory* _EF) : CMOGO(_fileName, _pd3dDevice, _EF)
{
	//any special set up for Player goes here
	m_fudge = Matrix::CreateRotationY(XM_PI);

	m_pos.y = 10.0f;

	SetDrag(0.7);
	SetPhysicsOn(true);
}

Player::~Player()
{
	//tidy up anything I've created
}


void Player::Tick(GameData* _GD)
{
	//TURN AND FORWARD CONTROL HERE
	Vector3 forwardMove = 40.0f * Vector3::Forward;
	Matrix rotMove = Matrix::CreateRotationY(m_yaw);
	forwardMove = Vector3::Transform(forwardMove, rotMove);
	if (_GD->keyboard_state.W)
	{
		m_acc += forwardMove;
	}
	if (_GD->keyboard_state.S)
	{
		m_acc -= forwardMove;
	}
	
	//change orinetation of player
	float rotSpeed = 2.0f * _GD->delta_time;
	if (_GD->keyboard_state.A)
	{
		m_yaw += rotSpeed;
	}
	if (_GD->keyboard_state.D)
	{
		m_yaw -= rotSpeed;
	}

	//move player up and down
	if (_GD->keyboard_state.R)
	{
		m_acc.y += 40.0f;
	}

	if (_GD->keyboard_state.F)
	{
		m_acc.y -= 40.0f;
	}

	//limit motion of the player
	float length = m_pos.Length();
	float maxLength = 500.0f;
	if (length > maxLength)
	{
		m_pos.Normalize();
		m_pos *= maxLength;
		m_vel *= -0.9; //VERY simple bounce back
	}

	//apply my base behaviour
	CMOGO::Tick(_GD);
}