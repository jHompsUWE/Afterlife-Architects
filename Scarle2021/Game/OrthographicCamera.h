#pragma once

#include "Gameobject.h"

class OrthographicCamera : public GameObject
{
public:
	OrthographicCamera(float _near_plane, float _far_plane, Vector3 _offset);
	~OrthographicCamera();

	virtual void Tick(GameData* _GD) override;
	virtual void Draw(DrawData* _DD) override { ; }

	Matrix GetProj() { return projection_matrix; }
	Matrix GetView() { return view_matrix; }
	float GetNearZ() { return near_plane; }
	float GetFarZ() { return far_plane; }
	Vector3 GetDirection();
	Vector3 GetTarget() { return camera_target; }

	void ReadInput(GameData* _GD);
	void MouseInput(GameData* _GD, int win_x, int win_y);

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void ZoomIn();
	void ZoomOut();

	void RecalculateProjViewPos();

protected:

private:
	// Matrices for this camera
	Matrix projection_matrix;
	Matrix view_matrix;

	// Parameters for setting up a camera
	float near_plane;
	float far_plane;

	Vector3	offset;
	Vector3 camera_target = Vector3::Zero;
	const Vector3 up = Vector3::UnitY;

	// Movement
	Vector3 vertical_move;
	Vector3 horizontal_move;
	float camera_speed = 75.0f;

	// Zoom
	float zoom_value = 10.0f;
	float zoom_min = 1.0f;
	float zoom_max = 20.0f;
	float last_scroll_value = 0.0f;

	int win_x;
	int win_y;
	int boundary = 20;
};


