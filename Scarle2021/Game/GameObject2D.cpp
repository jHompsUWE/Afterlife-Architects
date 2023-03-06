#include "pch.h"
#include "GameObject2D.h"

#include "DataManager.h"
#include "gamedata.h"
#include "DrawData2D.h"

using namespace DirectX;

GameObject2D::GameObject2D()
{
	m_colour = Color(1.0f, 1.0f, 1.0f, 1.0f);
	m_pos = Vector2::Zero;
	m_rotation = 0.0f;
	m_scale = Vector2::One;
	start_res = Vector2(*DataManager::GetRES().first, *DataManager::GetRES().second);
}

Vector2& GameObject2D::ReSize(float window_width, float window_height)
{
	//new scale value from resolution 
	resize_scale.x = window_width / start_res.x;
	resize_scale.y = window_height / start_res.y;

	//Applies new scaling
	m_pos = m_pos * resize_scale;
	m_scale = m_scale * resize_scale;

	//Updates old saved res
	start_res.x = window_width;
	start_res.y = window_height;

	//returns scale value
	return resize_scale;
}
