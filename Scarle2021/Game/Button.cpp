#include "pch.h"
#include "Button.h"

#include <iostream>


Button::Button(Vector2 _buttonPosition, ID3D11Device*
               _d3dDevice,std::string _text,std::string _filepath,
               AfterlifeEvent _event):UIButtonInterFace(_event)
{
	//setup for button background
	
	buttonBackGround = new ImageGO2D(_filepath, _d3dDevice);
	buttonBackGround->SetOrigin(Vector2(0, 0));
	buttonBackGround->SetScale(Vector2(1.f, 1.f));

	//sets res
	button_res = Vector2(buttonBackGround->GetRes().x
		* buttonBackGround->GetScale().x, buttonBackGround->GetRes().y
		* buttonBackGround->GetScale().y);

	
	button_pos = _buttonPosition - button_res/2;
	buttonBackGround->SetPos(button_pos);

	//setup button text
	buttonText = new TextGO2D(_text);
	buttonText->SetColour(Color((float*)&Colors::Black));
	buttonText->SetPos(button_pos);	
}

Button::Button(Vector2 _buttonPosition, ID3D11Device*
	_d3dDevice,std::string _filepath,
	AfterlifeEvent _event):UIButtonInterFace(_event)
{
	//setup for button background
	
	buttonBackGround = new ImageGO2D(_filepath, _d3dDevice);
	buttonBackGround->SetOrigin(Vector2(0, 0));
	buttonBackGround->SetScale(Vector2(1.f, 1.f));

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
	
	//checks if there is a text 
	if(buttonText != nullptr)
	{
		delete buttonText;
	}
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
		EventManager::GenerateEvent(al_event);
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

void Button::setPostion(Vector2& _new_pos)
{
	// WIP
}

Vector2 Button::getPosition()
{
	// TODO: insert return statement here
	return Vector2(0,0);
}

Vector2 Button::getWindowRes()
{
	// TODO: insert return statement here
	return Vector2(0,0);
}

bool Button::isInside(Vector2& point) const
{
	if(point.x >= button_pos.x && point.x <= (button_pos.x + button_res.x) &&
	   point.y >= button_pos.y && point.y <= (button_pos.y + button_res.y))
	   	return true;
    
	return false;
}
