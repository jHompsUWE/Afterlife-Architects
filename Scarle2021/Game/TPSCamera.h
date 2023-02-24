#ifndef _TPS_CAMERA_
#define _TPS_CAMERA_
#include "camera.h"
#include <iostream>

//=================================================================
//TPS style camera which will follow a given GameObject around _target
//=================================================================

class TPSCamera : public Camera
{
public:
	TPSCamera(float _fieldOfView, float _aspectRatio, float _nearPlaneDistance, float _farPlaneDistance, Vector3 _up, Vector3 _dpos);
	virtual ~TPSCamera();

	virtual void Tick(GameData* _GD) override;

	float GetZoom() { return zoom; }
	float GetNearZ() { return m_nearPlaneDistance; }
	float GetFarZ() { return m_farPlaneDistance; }
	Vector3 GetDirection();
	Vector3 GetTarget() { return target; }

protected:
	Vector3	m_dpos; //I'll lurk this far behind and away from it

private:
	// None of the other pi values actually work so this is the only way
	const float PI = 3.141592653589793238462643383279502884197169399375105820974944;

	// Movement
	Vector3 target;
	float speed = 0.5f;

	// Zoom
	float zoom = 10.0f;
	float min_zoom = 1.0f;
	float max_zoom = 20.0f;
	float last_scroll_value = 0.0f;
};

#endif
