#pragma once

#include "gamedata.h"
#include "Event.h"
#include "Observable.h"
#include "Observer.h"

#include <unordered_map>

namespace AL
{
	class NewEventManager : public IObservable<IEventReceiver>
	{
	public:
		//Deleted copy constructor and assignment operator
		NewEventManager(const NewEventManager&) = delete;
		NewEventManager& operator=(const NewEventManager&) = delete;

		//Gets singleton instance
		static NewEventManager& Get();
		
		//Static public functions, accessible via ::
		template <typename... Payload>
		static void GenerateEventSt(EventType type, const Payload&... args);
		static std::vector<Event>& GetEventListSt();
		static void AddEventReceiver(IEventReceiver* observer);
		static void RemoveEventReceiver(IEventReceiver* observer);

		//Public functions, accessible via Get() or via singleton instance
		std::vector<Event>& GetEventList();
		void FlushEventList();

		//Input polling
		void PollKeyboard(Keyboard::State keyboard);
		void PollMouse(Mouse::State mouse);
		void PollGamepad(GamePad::State gamepad);
		
	private:
		//Private constructor and de-constructor
		NewEventManager();
		~NewEventManager() override;

		//Data sharing
		void BroadcastData() override;

		//Key mapping
		void MouseMovToEvent(const Mouse::State& mouse);
		void MapEntryToEvent(bool state, Input::Action action, bool repeat = false);
		void MapEntryToEvent(bool state, Cursor::Action action, bool repeat = false);

		//This function can generate events
		template <typename... Payload>
		void GenerateEvent(EventType type, const Payload&... args);

		//The following two functions are closely linked together and provide an
		//easy way to bulk data inside events
		template<typename... Payload>
		void SetEventData(Event& event, const Payload&... args);
		template<typename T, typename... Payload>
		void SetEventData(Event& event, int& byte_offset, const T& arg, const Payload&... args);
		
		//Key mapping data
		std::unordered_map<Input::Action, bool> input_to_action_map{};
		std::unordered_map<Cursor::Action, bool> cursor_to_action_map{};

		//events
		std::vector<Event> event_list{};

		//Saves mouse pos
		int mouse_x = 0;
		int mouse_y = 0;
	};

	
}

