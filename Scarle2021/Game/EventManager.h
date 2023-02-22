#pragma once
#include <unordered_map>
#include "GameData.h"

enum AfterlifeEvent
{
	none,
	input_up,
	input_down,
	input_left,
	input_right,
	play_sound_theme1,
	play_sound_theme2,
	play_sound_theme3,
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
