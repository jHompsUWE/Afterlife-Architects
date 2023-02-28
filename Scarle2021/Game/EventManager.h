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
	input_E,
	input_right,
	game_resized,
	enter_main_menu,
	enter_game_play,
	enter_level_select,
	window_1_green,
	window_2_yellow,
	window_3_orange,
	window_4_brown,
	window_5_pink,
	window_6_red,
	window_7_blue,
	window_8_multicolour,
	window_9_gate,
	window_10_roads,
	window_11_karam_station,
	window_12_karma_tracks,
	window_13_topias,
	window_14_training_centre,
	window_15_ports,
	window_16_siphons_banks,
	window_17_special_buildings,
	window_18_omnibolges_and_love_domes,
	window_19_limbo_structures,
	window_20_delete_structures,
	window_21_zoom_in,
	window_22_zoom_out,
	play_sound_theme1,
	play_sound_theme2,
	play_sound_theme3,
	play_sound_theme4,
	play_sound_theme5,
	play_sound_theme6,
	play_sound_theme7,
	play_sound_bank,
	play_sound_click,
	play_sound_click2,
	play_sound_demolish1,
	play_sound_demolish2,
	play_sound_demolish3,
	play_sound_explo1,
	play_sound_falseclick,
	play_sound_gateheaven,
	play_sound_gatehell,
	play_sound_instituteheaven,
	play_sound_institutehell,
	play_sound_limbos,
	play_sound_nightambiencesimple_02,
	play_sound_port,
	play_sound_specialbuildingheaven,
	play_sound_specialbuildinghell,
	play_sound_station,
	play_sound_topiaheaven,
	play_sound_topiahell,
	dialogue_1
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
