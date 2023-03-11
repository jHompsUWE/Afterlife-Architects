#pragma once

namespace AL
{
	struct Cursor
	{
        enum Action
        {
            unknown = 0, //Not handled
            scroll_up,
            scroll_down,
            button_input1,
            button_input2
        };
	};
}