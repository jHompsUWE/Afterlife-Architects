#pragma once

namespace AL
{
	struct Input
	{
		enum Action
		{
			unknown = 0, //Keyboard not handled
			input_up,
			input_down,
			input_left,
			input_right
		};
	};
}