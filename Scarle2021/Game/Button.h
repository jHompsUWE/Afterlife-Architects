#pragma once
#include <iostream>
#include <ostream>

#include "DataManager.h"
#include "UIButtonInterFace.h"

template<typename Action1, typename Action2>
class Button : public UIButtonInterFace, public IEventReceiver
{
public:
	Button(Vector2 _buttonPosition, ID3D11Device* _d3dDevice,std::string
	_text,std::string _filepath,AL::EventType _event, Action1 _action1, Action2 _action2 ,Vector2 _setScale)
		: UIButtonInterFace(_event), action_1(_action1), action_2(_action2)
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

		AL::NewEventManager::AddEventReceiver(this);
	};
	
	Button(Vector2 _buttonPosition, ID3D11Device* _d3dDevice,std::string
	_filepath,AL::EventType _event, Action1 _action1, Action2 _action2, Vector2 _setScale)
		: UIButtonInterFace(_event), action_1(_action1), action_2(_action2)
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

		AL::NewEventManager::AddEventReceiver(this);
	}
	
	~Button() override
	{
		AL::NewEventManager::RemoveEventReceiver(this);
		
		delete buttonBackGround;
		delete buttonText;
	}

	void ReceiveEvents(const AL::Event& al_event) override
	{
		switch (al_event.type)
		{
		case AL::event_cursor_move:
			//Only when the cursor is moved update position
			mouse_pos = Vector2{(float)al_event.cursor_moved.pos_x, (float)al_event.cursor_moved.pos_y};
			break;
			
		case AL::event_cursor_interact:

			//Checks if the button specified is being pressed
			if(al_event.cursor_interact.action == AL::Cursor::button_input1)
			{
				//If the button has been released, continue
				if(al_event.cursor_interact.active == false)
				{
					//Mouse pos is inside button? carry our action
					if(isInside(mouse_pos))
					{
						//Specific behaviour for specific events
						switch (saved_event)
						{
						case AL::event_sound_start:
							//AL::NewEventManager::Get().GenerateEventSoundStart(action_1, action_2, false);
							break;
					
						case AL::event_sound_stop:
							//AL::NewEventManager::Get().GenerateEventSoundStop(action_1);
							break;
					
						case AL::event_ui:
							AL::NewEventManager::Get().GenerateInterfaceEvent((AL::UI::Action)action_1);
							break;
					
						case AL::event_build_sys:

							switch ((AL::BuildSys::Section)action_1)
							{
								case AL::BuildSys::unknown:
									break;

								case AL::BuildSys::structure:
									
									AL::NewEventManager::Get().GenerateBuildSysEvent(AL::BuildSys::Section::structure,
									(StructureType)action_2, (ZoneType)action_2);
									break;

								case AL::BuildSys::zone:
									
									AL::NewEventManager::Get().GenerateBuildSysEvent(AL::BuildSys::Section::zone,
									(StructureType)action_2, (ZoneType)action_2);
									break;

						default:
							break;
							}
					
						case AL::event_game:
							AL::NewEventManager::Get().GenerateGameEvent((AL::Game::Action)action_1);
							break;
					
						default:
							break;
						}
			
					}
				}
			}
			
			break;

		default:
			break;
		}
	}

	void update(GameData* _gameData) override
	{
		buttonBackGround->Tick(_gameData);
	
		if(buttonText != nullptr)
		{
			buttonText->Tick(_gameData);
		}
	}
	
	void render(DrawData2D* _drawData) override
	{
		buttonBackGround->Draw(_drawData);
	
		if(buttonText != nullptr)
		{
			buttonText->Draw(_drawData);
		}
	}
	
	void setPostion(Vector2 _new_pos) override
	{
		// WIP
		button_pos = _new_pos;
		buttonBackGround->SetPos(_new_pos);
	
		if(buttonText != nullptr)
		{
			buttonText->SetPos(_new_pos);
		}
	}
	
	
	void setScale(Vector2& _newScale) override
	{
		//_newScale = Vector2(0,0);
	}
	
	Vector2& getPosition() override
	{
		// TODO: insert return statement here
		return button_pos;
	}
	
	Vector2& getButtonRes() override
	{
		// TODO: insert return statement here
		return button_res;
	}
	
	void reSize(Vector2 game_res) override
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

private:

	//mouse pointer inside button
	bool isInside(Vector2& point) const
	{
		if(point.x >= button_pos.x && point.x <= (button_pos.x + button_res.x) &&
			   point.y >= button_pos.y && point.y <= (button_pos.y + button_res.y))
			   	return true;
    
		return false;
	}

	Vector2 mouse_pos {0,0};
	
	Action1 action_1 = NULL;
	Action2 action_2 = NULL;
};




