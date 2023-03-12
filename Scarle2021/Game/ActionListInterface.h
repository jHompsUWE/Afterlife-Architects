#pragma once

namespace AL
{
	struct UI
	{
		enum Action
		{
			unknown = 0, //Not handled
			resize_ui,
			window_gate,
			window_karma_station,
			window_topias,
			window_training_centre,
			window_ports,
			window_siphon,
			window_special_buildings,
			window_omnibolges_love_domes,
			window_limbo_structures,
			window_delete_structures,
			window_advisors,
			window_soulview,
			button_zoom_in,
			button_zoom_out,
			adv_option1,
			adv_option2,
			adv_option3,
			adv_option4,
			adv_option5
		};
	};
}