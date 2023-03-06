#pragma once

#include "gamedata.h"
#include "Event.h"
#include "Observable.h"
#include "Observer.h"

#include <unordered_map>


namespace AL
{
	class EventManager : public IObservable<IEventReceiver>
	{
	public:
		//Deleted copy constructor and assignment operator
		EventManager(const EventManager&) = delete;
		EventManager& operator=(const EventManager&) = delete;

		//Gets singleton instance
		static EventManager& Get();
		
		//Static public functions, accessible via ::
		static void AddEventReceiver(IEventReceiver* observer);
		static void RemoveEventReceiver(IEventReceiver* observer);

		//Public functions, accessible via Get() or via singleton instance
		void PollKeyboard(Keyboard::State keyboard);
		void PollMouse(Mouse::State mouse);
		void PollGamepad(GamePad::State gamepad);
		
	private:
		//Private constructor and de-constructor
		EventManager();
		~EventManager() override;

		//Internal Functions
		void BroadcastData() override;

		//Key mapping
		void MapEntryToInputEvent(bool state, Input::Action action, bool repeat = false);
		void MapEntryToCursorEvent(bool state, Cursor::Action action, bool repeat = false);
		
		//Key mapping data
		std::unordered_map<Input::Action, bool> input_to_action_map{};
		std::unordered_map<Cursor::Action, bool> cursor_to_action_map{};

		//events?
		std::vector<Event> event_list{};
	};
}

