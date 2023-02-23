#pragma once

#include "gameobject.h"
#include "GameData.h"
class OrthographicCamera : public GameObject
{
public:
	OrthographicCamera();
	~OrthographicCamera();

	virtual void Tick(GameData* _GD) override;

	virtual void Draw(DrawData* _DD) override;

	Matrix GetProj() { return projection_matrix; }
	Matrix GetView() { return view_matrix; }

	void Input(GameData* _GD);

	void RecalculateProjViewPos();

private:
	float camera_speed = 0.7f;

	Vector3 camera_target;
	Vector3 camera_constraint = Vector3(10.0f, (sqrt(3) / 3) * 10, 0.0f);

	Vector3 vertical_movement = camera_speed * Vector3(0, 1, 0);
	Vector3 horizontal_movement = camera_speed / 4 * Vector3(1, 0, 1);

	float camera_width = 120.0f;
	float camera_height = 60.0f;
	float near_plane = 0.1f;
	float far_plane = 1000.0f;

	float zoom_value = 1.5f;
	float zoom_min = 0.2f;
	float zoom_max = 3.0f;

	float scroll_value = 0.0f;

protected:
	XMMATRIX projection_matrix;
	XMMATRIX view_matrix;
	XMVECTOR camera_position;
	Vector3 camera_up = Vector3::UnitY;
};


