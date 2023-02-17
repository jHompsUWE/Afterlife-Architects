#pragma once

#include "gameobject.h"
class OrthographicCamera : public GameObject
{
public:
	//near and far values exist as well, -1 for near value and 1 for far are default
	//which is fine for an orthographic camera

	OrthographicCamera(float width, float height, Vector3 _up = Vector3::Up, Vector3 _target = Vector3::Zero);
	~OrthographicCamera();

	virtual void Tick(GameData* _GD) override;

	virtual void Draw(DrawData* _DD) override;

	//Getters
	Matrix GetProj() { return projection_matrix; }
	Matrix GetView() { return view_matrix; }

	void SetPosition(const Vector3& position) { _position = position; void RecalculateViewMatrix(); }
	const Vector3& GetPosition() const { return _position; }

	//not including rotation here, seems unnecessary for project

	const Matrix& GetProjectionMatrix() const { return projection_matrix; }
	const Matrix& GetViewMatrix() const { return view_matrix; }
	const Matrix& GetViewProjectionMatrix() const { return view_projection_matrix; }

private:
	void RecalculateViewMatrix();

	float width;
	float height;

protected:
	Matrix projection_matrix;
	Matrix view_matrix;
	Matrix view_projection_matrix;

	Vector3 _position;

	Vector3 target;
	Vector3 up;
};

