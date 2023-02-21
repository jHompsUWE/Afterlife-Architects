#pragma once
#include "UIButtonInterFace.h"


class Button : public UIButtonInterFace
{
public:
	Button(Vector2 _buttonPosition, ID3D11Device* _d3dDevice,std::string _text,std::string _filepath,AfterlifeEvent _event);
	Button(Vector2 _buttonPosition, ID3D11Device* _d3dDevice,std::string _filepath,AfterlifeEvent _event);
	~Button() override;

	void update(GameData* _gameData, Vector2& _mousePosition)override;
	void render(DrawData2D* _drawData)override;

	void setPostion(Vector2& _new_pos) override;
	Vector2 getPosition() override;
	Vector2 getWindowRes() override;

private:

	//mouse pointer inside button
	bool isInside(Vector2& point) const;
};

