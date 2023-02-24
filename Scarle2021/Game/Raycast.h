#pragma once
#include "SimpleMath.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

class Raycast
{
public:
	static Vector3 GetPosOnX(float x, Vector3 direction, Vector3 position);
	static Vector3 GetPosOnY(float y, Vector3 direction, Vector3 position);
	static Vector3 GetPosOnZ(float z, Vector3 direction, Vector3 position);
};

