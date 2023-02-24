#pragma once
#include "GameData.h"
#include "ImageGO2D.h"
#include "TextGO2D.h"
#include "EventManager.h"


class UIButtonInterFace
{
public:
	explicit UIButtonInterFace(AfterlifeEvent _event):al_event(_event){}
	virtual ~UIButtonInterFace() = default;

	virtual Vector2& getPosition() =0;
	virtual Vector2& getButtonRes() =0;

	virtual void update(GameData* _gameData, Vector2& _MousePostion)=0;
	virtual void render(DrawData2D* _drawData)=0;

	virtual void setPostion(Vector2 newPostition)=0;
	virtual void setScale(Vector2& newScale)=0;

	virtual void reSize(std::pair<int*, int*> game_res)=0;

protected:
	
	ImageGO2D* buttonBackGround = nullptr;
	TextGO2D* buttonText = nullptr;

	Vector2 button_res = {0,0};
	Vector2 button_pos = {0,0};

	AfterlifeEvent al_event = none;
};

