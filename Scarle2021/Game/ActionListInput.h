#pragma once

namespace AL
{
	struct Input
	{
		enum Action
		{
			unknown = 0, //Keyboard not handled
			build_houses,
			show_vibes,
			place_zone_green
		};
	};
}