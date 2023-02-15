#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

//=================================================================
//Base Game Object Class
//=================================================================

#include "CommonStates.h"
#include "SimpleMath.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

class Camera;
struct ID3D11DeviceContext;
struct GameData;
struct DrawData;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData* _DD) = 0;

	//getters
	Vector3		GetPos() { return m_pos; }
	Vector3		GetScale() { return m_scale; }

	float		GetPitch() { return m_pitch; }
	float		GetYaw() { return m_yaw; }
	float		GetRoll() { return m_roll; }

	bool		IsPhysicsOn() { return m_physicsOn; }
	float		GetDrag() { return m_drag; }

	//setters
	void		SetPos(Vector3 _pos) { m_pos = _pos; }

	void		SetScale(float _scale) { m_scale = _scale * Vector3::One; }
	void		SetScale(float _x, float _y, float _z) { m_scale = Vector3(_x, _y, _z); }
	void		SetScale(Vector3 _scale) { m_scale = _scale; }

	void		SetPitch(float _pitch) { m_pitch = _pitch; }
	void		SetYaw(float _yaw) { m_yaw = _yaw; }
	void		SetRoll(float _roll) { m_roll = _roll; }
	void		SetPitchYawRoll(float _pitch, float _yaw, float _roll) { m_pitch = _pitch; m_yaw = _yaw; m_roll = _roll; }

	void		SetPhysicsOn(bool _physics) { m_physicsOn = _physics; }
	void		TogglePhysics() { m_physicsOn = !m_physicsOn; }
	void		SetDrag(float _drag) { m_drag = _drag; }


protected:

	//World transform/matrix of this GO and it components
	Matrix m_worldMat;
	Matrix m_rotMat;
	Matrix m_fudge;
	Vector3 m_pos;
	float m_pitch, m_yaw, m_roll;
	Vector3 m_scale;

	//very basic physics
	bool m_physicsOn = false;
	float m_drag = 0.0f;
	Vector3 m_vel = Vector3::Zero;
	Vector3 m_acc = Vector3::Zero;
};

#endif