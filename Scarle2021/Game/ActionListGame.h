#pragma once

namespace AL
{
	struct Game
	{
		enum Action
		{
			unknown = 0, //Not handled
			select_green,
			select_red,
			select_yellow,
			select_purple
		};
	};
}