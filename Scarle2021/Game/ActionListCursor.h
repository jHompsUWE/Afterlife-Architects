#pragma once

namespace AL
{
	struct Cursor
	{
        enum Action
        {
            unknown = 0,
            button_input1,
            button_input2
        };
	};

    struct Scroll
    {
	    enum Action
	    {
            unknown = 0,
		    scroll_up,
            scroll_down
	    };
    };
}