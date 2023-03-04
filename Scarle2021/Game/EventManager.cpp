#include "pch.h"
#include "EventManager.h"

namespace AL
{
	//Default private constructor
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

	void EventManager::PollMouse(Mouse::State mouse)
	{
	}

	void EventManager::PollKeyboard(Keyboard::State keyboard)
	{
	}

	void EventManager::PollGamepad(GamePad::State gamepad)
	{
	}
}
