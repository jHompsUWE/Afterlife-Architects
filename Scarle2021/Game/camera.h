#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "gameobject.h"

//=================================================================
//Base Camera Class
//=================================================================

struct GameData;

class Camera : public GameObject
{
public:
	Camera(float _fieldOfView, float _aspectRatio, float _nearPlaneDistance, float _farPlaneDistance, Vector3 _up = Vector3::Up, Vector3 _target = Vector3::Zero);
	~Camera();

	virtual void Tick(GameData* _GD) override;

	virtual void Draw(DrawData* _DD) override;

	//Getters
	Matrix GetProj() { return m_projMat; }
	Matrix GetView() { return m_viewMat; }

	//Setters

protected:

	//Principle transforms/matrices for this camera
	Matrix m_projMat;
	Matrix m_viewMat;

	//parameters for setting up a camera
	float m_fieldOfView;
	float m_aspectRatio;
	float m_nearPlaneDistance;
	float m_farPlaneDistance;

	Vector3 m_target;
	Vector3 m_up;

};


#endif