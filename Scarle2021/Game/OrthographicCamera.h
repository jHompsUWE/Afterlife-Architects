#pragma once

#include "Gameobject.h"
#include "Observer.h"

class OrthographicCamera : public GameObject, public IEventReceiver
{
public:
	OrthographicCamera(float _near_plane, float _far_plane, Vector3 _offset);
	~OrthographicCamera() override;

	virtual void Tick(GameData* _GD) override;
	virtual void Draw(DrawData* _DD) override { ; }

	Matrix GetProj() const { return projection_matrix; }
	Matrix GetView() const { return view_matrix; }
	float GetNearZ() const { return near_plane; }
	float GetFarZ() const { return far_plane; }
	Vector3 GetDirection();
	Vector3 GetTarget() const { return camera_target; }
	
	void MouseInput(GameData* _GD, int win_x, int win_y);
	void ReceiveEvents(const AL::Event& al_event) override;

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void ZoomIn(float magintude);
	void ZoomOut(float magnitude);

	void RecalculateProjViewPos();

private:
	// Matrices for this camera
	Matrix projection_matrix{};
	Matrix view_matrix{};

	// Parameters for setting up a camera
	float near_plane;
	float far_plane;

	Vector3	offset{};
	Vector3 camera_target = Vector3::Zero;
	const Vector3 up = Vector3::UnitY;

	// Movement
	Vector2 mouse_pos {0,0};
	Vector3 vertical_move{};
	Vector3 horizontal_move{};
	float camera_speed = 100.0f;

	// Zoom
	float zoom_value = 10.0f;
	float zoom_min = 1.0f;
	float zoom_max = 40.0f;
	float last_scroll_value = 0.0f;

	int win_x{};
	int win_y{};
	int boundary = 20;
};


