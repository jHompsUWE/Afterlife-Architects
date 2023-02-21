#pragma once

#include "gameobject.h"
class OrthographicCamera : public GameObject
{
public:
	OrthographicCamera(float camera_width, float camera_height, float near, float far, 
		XMVECTOR camera_position, XMVECTOR camera_target, XMVECTOR camera_up);
	~OrthographicCamera();

	virtual void Tick(GameData* _GD) override;

	virtual void Draw(DrawData* _DD) override;


	void CameraForward(float distance);
	void CameraBackward(float distance);
	void CameraRotateLeft();
	void CameraRotateRight();
	void CameraRotateUp();
	void CameraRotateDown();

	//Getters
	Matrix GetProj() { return projection_matrix; }
	Matrix GetView() { return view_matrix; }

	void SetPosition(const Vector3& position) { camera_position = position; void RecalculateViewMatrix(); }
	const Vector3& GetPosition() const { return camera_position; }

	//not including rotation here not necessary

	const Matrix& GetProjectionMatrix() const { return projection_matrix; }
	const Matrix& GetViewMatrix() const { return view_matrix; }
	const Matrix& GetViewProjectionMatrix() const { return world_view_projection_matrix; }

	/* camera_position = XMFLOAT3(0.0f, 0.0f, -5.0f);
	XMFLOAT3 camera_target = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 camera_up = XMFLOAT3(0.0f, 1.0f, 0.0f);*/

	XMVECTOR camera_position = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR camera_target = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR camera_up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);


private:
	void RecalculateViewMatrix();

	const float camera_speed = 0.003f;

	float width;
	float height;

	//values used for XMMatrixOrthographicOffCenterLH
	//float left = -10.0f;
	//float right = 10.0f;
	//float bottom = -10.0f;
	//float top = 10.0f;
	
	//XMMatrixOrthographicOffCenterLH creates a custom orthogonal projection, requires left right etc.
	//to be passed. Trying XMMatrixOrthographicLH, which requires 4 values passed to viewwidth, viewheight,
	//near and far

	float camera_width = 120.0f;
	float camera_height = 60.0f;
	float near_plane = 0.0f;
	float far_plane = 1.0f;

protected:
	XMMATRIX projection_matrix = XMMatrixOrthographicLH(camera_height, camera_width, near_plane, far_plane);
	XMMATRIX view_matrix = XMMatrixLookAtLH(camera_position, camera_target, camera_up);

	XMMATRIX transformation_matrix = projection_matrix * view_matrix;
	XMMATRIX world_view_projection_matrix = projection_matrix * view_matrix;

	XMVECTOR forward = XMVector3Normalize(XMVectorSubtract(camera_target, camera_position));

	//XMMATRIX view_matrix = XMMatrixIdentity();
	//Matrix projection_matrix;
	//Matrix view_matrix;
	//Matrix view_projection_matrix;
	
	//Vector3 _position;
	//Vector3 target;
	//Vector3 up;
};


