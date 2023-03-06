#include "pch.h"
#include "Button.h"
#include <iostream>

#include "DataManager.h"


Button::Button(Vector2 _buttonPosition, ID3D11Device*
               _d3dDevice,std::string _text,std::string _filepath,
               AfterlifeEvent _event,Vector2 _setScale):UIButtonInterFace(_event)
{
	//setup for button background
	buttonBackGround = new ImageGO2D(_filepath, _d3dDevice);
	buttonBackGround->SetOrigin(Vector2(0, 0));
	//buttonBackGround->SetScale(Vector2(_setScale));

	//sets res
	button_res = Vector2(buttonBackGround->GetRes().x
		* buttonBackGround->GetScale().x, buttonBackGround->GetRes().y
		* buttonBackGround->GetScale().y);
	
	button_pos = _buttonPosition - button_res/2;
	buttonBackGround->SetPos(button_pos);

	//setup button text
	buttonText = new TextGO2D(_text);
	buttonText->SetColour(Color((float*)&Colors::Black));
	buttonText->SetPos(Vector2(button_pos.x,button_pos.y));
	buttonText->SetScale(Vector2(_setScale));
	
}

Button::Button(Vector2 _buttonPosition, ID3D11Device*
	_d3dDevice,std::string _filepath,
	AfterlifeEvent _event,Vector2 _setScale):UIButtonInterFace(_event)
{
	//setup for button background
	buttonBackGround = new ImageGO2D(_filepath, _d3dDevice);
	buttonBackGround->SetOrigin(Vector2(0, 0));
	buttonBackGround->SetScale(_setScale);
	//sets res
	button_res = Vector2(buttonBackGround->GetRes().x
		* buttonBackGround->GetScale().x, buttonBackGround->GetRes().y
		* buttonBackGround->GetScale().y);
	
	button_pos = _buttonPosition - button_res/2;
	buttonBackGround->SetPos(button_pos);
}

Button::~Button()
{
	delete buttonBackGround;
	delete buttonText;
}

void Button::update(GameData* _gameData, Vector2& _mousePosition)
{
	buttonBackGround->Tick(_gameData);
	
	if(buttonText != nullptr)
	{
		buttonText->Tick(_gameData);
	}
	
	if(isInside(_mousePosition))
	{
		if(DataManager::GetGD()->mouse_state.leftButton)
		{
			EventManager::GenerateEvent(al_event);
		}
	}
}

void Button::render(DrawData2D* _drawData)
{
	buttonBackGround->Draw(_drawData);
	
	if(buttonText != nullptr)
	{
		buttonText->Draw(_drawData);
	}
}

void Button::setPostion(Vector2 _buttonPosition)
{
	// WIP
	button_pos = _buttonPosition;
	buttonBackGround->SetPos(_buttonPosition);
	
	if(buttonText != nullptr)
	{
		buttonText->SetPos(_buttonPosition);
	}
	
}

void Button::setScale(Vector2& _newScale)
{
	//_newScale = Vector2(0,0);
}

 Vector2& Button::getPosition()
{
	// TODO: insert return statement here
	return button_pos;
}

Vector2& Button::getButtonRes()
{
	// TODO: insert return statement here
	return button_res;
}

void Button::reSize(Vector2 game_res)
{
	//resizes background and text
	auto& resize_scale = buttonBackGround->ReSize(game_res.x, game_res.y);
	if(buttonText != nullptr)
	{
		buttonText->ReSize(game_res.x, game_res.y);
	}

	//Re-scale position and scale accordingly to make button work in UI 
	button_pos = button_pos * resize_scale;
	button_res = button_res * resize_scale;
}

bool Button::isInside(Vector2& point) const
{
	if(point.x >= button_pos.x && point.x <= (button_pos.x + button_res.x) &&
	   point.y >= button_pos.y && point.y <= (button_pos.y + button_res.y))
	   	return true;
    
	return false;
}
