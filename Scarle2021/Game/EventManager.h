#pragma once

#include "Event.h"
#include "gamedata.h"

namespace AL
{
	class EventManager
	{
	public:
		//Deleted copy constructor and assignment operator
		EventManager(const EventManager&) = delete;
		EventManager& operator=(const EventManager&) = delete;

		//Gets singleton instance
		static EventManager& Get();
		
		//Static public functions, accessible via ::

		//Public functions, accessible via Get() or via singleton instance
		void PollMouse(Mouse::State mouse);
		void PollKeyboard(Keyboard::State keyboard);
		void PollGamepad(GamePad::State gamepad);
		
	private:
		//Private constructor and de-constructor
		EventManager();
		~EventManager();

		//Internal Functions

		//Data
	};
}

