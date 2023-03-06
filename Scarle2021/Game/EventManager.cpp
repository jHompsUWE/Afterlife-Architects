#include "pch.h"
#include "EventManager.h"

namespace AL
{
	//Default private constructor, no need to initialize inherited class
	EventManager::EventManager() = default;
	
	//Default private de-constructor
	EventManager::~EventManager() = default;
	
	/**
	 * \return Instance of EventManager
	 */
	EventManager& EventManager::Get()
	{
		static EventManager instance;
		return instance;
	}

	// Static ----------------------------------------------------------------------------------------------------------
	
	/**
	 * \param observer to be subscribed to receive events
	 */
	void EventManager::AddEventReceiver(IEventReceiver* observer)
	{
		Get().AddObserver(observer);
	}

	/**
	 * \param observer to be unsubscribed from receiving events
	 */
	void EventManager::RemoveEventReceiver(IEventReceiver* observer)
	{
		Get().RemoveObserver(observer);
	}

	// Input Mapping ---------------------------------------------------------------------------------------------------

	/**
	 * \brief To map keyboard entries to events
	 * \param keyboard keyboard state in this current frame
	 */
	void EventManager::PollKeyboard(Keyboard::State keyboard)
	{
		MapEntryToInputEvent(keyboard.A, Input::input_up);
	}
	
	/**
	 * \brief to map mouse entries to events
	 * \param mouse mouse state in this current frame
	 */
	void EventManager::PollMouse(Mouse::State mouse)
	{
		MapEntryToCursorEvent(mouse.leftButton, Cursor::button_input1);
	}

	/**
	 * \brief to map gamepad entries to events
	 * \param gamepad gamepad state in this current frame
	 */
	void EventManager::PollGamepad(GamePad::State gamepad)
	{
		if(gamepad.IsConnected())
		{
			MapEntryToInputEvent(gamepad.IsAPressed(), Input::input_left);
		}
	}

	// Private ---------------------------------------------------------------------------------------------------------
	
	void EventManager::BroadcastData()
	{
	}

	// Key Mapping Handlers --------------------------------------------------------------------------------------------

	void EventManager::MapEntryToInputEvent(bool state, Input::Action action, bool repeat)
	{
		//If the input is set as repeat, generate an input event each poll action while
		//the button is being pressed
		if(repeat)
		{
			if(state)
			{
				//generate event with the repeated action here
				event_list.emplace_back(event_input);
				event_list.back().input.action = action;
				event_list.back().input.active = true;
			}
			return;
		}
		
		if(state)
		{
			if(!input_to_action_map[action])
			{
				input_to_action_map[action] = true;
				//generate event with the pressed action here
				event_list.emplace_back(event_input);
				event_list.back().input.action = action;
				event_list.back().input.active = true;
			}
		}
		else
		{
			if(input_to_action_map[action])
			{
				input_to_action_map[action] = false;
				//generate event with the released action here
				event_list.emplace_back(event_input);
				event_list.back().input.action = action;
				event_list.back().input.active = false;
			}
		}
	}

	void EventManager::MapEntryToCursorEvent(bool state, Cursor::Action action, bool repeat)
	{
		//If the input is set as repeat, generate an input event each poll action while
		//the button is being pressed
		if(repeat)
		{
			if(state)
			{
				//generate event with the repeated action here
				event_list.emplace_back(event_cursor_interact);
				event_list.back().cursor_interact.action = action;
				event_list.back().cursor_interact.active = true;
			}
			return;
		}
		
		if(state)
		{
			if(!cursor_to_action_map[action])
			{
				cursor_to_action_map[action] = true;
				//generate event with the pressed action here
				event_list.emplace_back(event_cursor_interact);
				event_list.back().cursor_interact.action = action;
				event_list.back().cursor_interact.active = true;
			}
		}
		else
		{
			if(cursor_to_action_map[action])
			{
				cursor_to_action_map[action] = false;
				//generate event with the released action here
				event_list.emplace_back(event_cursor_interact);
				event_list.back().cursor_interact.action = action;
				event_list.back().cursor_interact.active = false;
			}
		}
	}
}
