#pragma once
#include <unordered_map>
#include "GameData.h"

enum AfterlifeEvent
{
	none,
	number_1,
	number_2,
	number_3,
	number_4,
	number_5,
	number_6,
	number_7,
	number_8,
	number_9,
	number_0,
	input_up,
	input_down,
	input_left,
	input_right,
	input_E
};

class EventManager
{
public:
	//Deleted copy/assignment operators
	EventManager(const EventManager&) = delete;
	EventManager& operator=(const EventManager&) = default;

	//Create class and instance
	static EventManager& Get();

	//Static public functions
	static void GenerateEvent(AfterlifeEvent _event);
	static void ReadInput(GameData* game_data);
	static std::list<AfterlifeEvent>& GetEventList();

private:
	//Private constructor
	EventManager() = default;
	~EventManager() = default;

	//Internal functions
	void IGenerateEvent(AfterlifeEvent _event);
	void IReadInput(GameData* game_data);
	void MapInputToEvent(const bool& pressed, AfterlifeEvent event);
	
	//Event queue & input state
	std::list<AfterlifeEvent> event_list{};
	std::unordered_map<AfterlifeEvent, bool> input_state{};
};
