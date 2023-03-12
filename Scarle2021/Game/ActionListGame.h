#pragma once

namespace AL
{
	struct Game
	{
		enum Action
		{
			unknown = 0, //Not handled
			enter_gameplay,
			enter_main_menu,
			enter_level_select,

			quit_game
		};
	};
}