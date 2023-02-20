#pragma once

#include "gameobject.h"
class OrthographicCamera : public GameObject
{
public:
	OrthographicCamera(float left, float right, float bottom, float top, float near, float far);
	~OrthographicCamera();

	virtual void Tick(GameData* _GD) override;

	virtual void Draw(DrawData* _DD) override;

	//Getters
	Matrix GetProj() { return projection_matrix; }
	Matrix GetView() { return view_matrix; }

	void SetPosition(const Vector3& position) { _position = position; void RecalculateViewMatrix(); }
	const Vector3& GetPosition() const { return _position; }

	//not including rotation here not necessary

	const Matrix& GetProjectionMatrix() const { return projection_matrix; }
	const Matrix& GetViewMatrix() const { return view_matrix; }
	const Matrix& GetViewProjectionMatrix() const { return view_projection_matrix; }

	XMFLOAT3 camera_position = XMFLOAT3(0.0f, 0.0f, -5.0f);
	XMFLOAT3 camera_target = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 camera_up = XMFLOAT3(0.0f, 1.0f, 0.0f);


private:
	void RecalculateViewMatrix();

	float width;
	float height;

	//values possibly work for creating ortographic perspective
	float left = -10.0f;
	float right = 10.0f;
	float bottom = -10.0f;
	float top = 10.0f;
	float near_plane = 0.1f;
	float far_plane = 100.0f;

protected:
	XMMATRIX projection_matrix = XMMatrixOrthographicOffCenterLH(left, right, bottom, top, near_plane, far_plane);
	XMMATRIX view_matrix = XMMatrixLookAtLH(XMLoadFloat3(&camera_position), XMLoadFloat3(&camera_target), XMLoadFloat3(&camera_up));

	//XMMATRIX view_matrix = XMMatrixIdentity();
	XMMATRIX transformation_matrix = projection_matrix * view_matrix;
	//Matrix projection_matrix;
	//Matrix view_matrix;
	Matrix view_projection_matrix;

	Vector3 _position;

	Vector3 target;
	Vector3 up;
};


