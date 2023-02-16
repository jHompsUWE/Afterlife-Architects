#ifndef _DRAW_STATE_H_
#define _DRAW_STATE_H_

//=================================================================
//Data to be passed by game to all Game Objects via Draw 
//=================================================================

#include "CommonStates.h"

using namespace DirectX;

class Camera;
class Light;

struct DrawData
{
	ID3D11DeviceContext* pd3d_immediate_context;
	CommonStates* common_states;
	Camera* main_camera;
	Light* main_light;
};

#endif
