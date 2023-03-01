#pragma once

#include "ActionListCursor.h"
#include "ActionListInput.h"
#include "ActionListInterface.h"
#include "ActionListGame.h"
#include "ActionListPacket.h"
#include "GameState.h"

namespace AL
{
    class Event
    {
    public:

        /**
         * \brief Event for actions related to input such as button presses
         * \var action = action to process 
         * \var active = is action currently on (toggle)
         */
        struct InputEvent
        {
            Input::Action action = Input::Action::unknown;
            bool active = NULL;
        };
        
        /**
         * \brief Event linked to the use of the cursor
         * \var action = action to process 
         * \var active = if the action should be handled as a start or finish of this event
         * \var pos_x, pos_y = click location
         */
        struct CursorEventClick
        {
            Cursor::Action action = Cursor::Action::unknown;
            bool active = NULL;
            int pos_x = NULL;
            int pos_y = NULL;
        };

        /**
         * \brief Event linked to scrolling with the cursor
         * \var action = action to process 
         * \var ticks = how much scrolling should be applied
         */
        struct CursorEventScroll
        {
            Scroll::Action action = Scroll::Action::unknown;
            float ticks = NULL;
        };
        
        /**
         * \brief Event to start to play a sound
         * \var filename = filename as seen in the asset pipeline, no file extension
         * \var volume
         * \var bool = will it loop?
         */
        struct SoundEventStart
        {
            std::string filename = nullptr;
            float volume = NULL;
            bool loop = NULL;
        };

        /**
         * \brief Event to a sound from playing
         * \var filename = filename as seen in the asset pipeline, no file extension
         */
        struct SoundEventStop
        {
            std::string filename = nullptr;
        };

        /**
         * \brief Event to redirect an action to the UI
         */
        struct InterfaceEvent
        {
            UI::Action action = UI::Action::unknown;
        };
        
        /**
         * \brief Event to redirect an action to the game
         */
        struct GameEvent
        {
            Game::Action action = Game::Action::unknown;
        };

        struct PacketEvent
        {
            Packet::Action action = Packet::Action::unknown;

            void* var_a = nullptr;
            void* var_b = nullptr;
            void* var_c = nullptr;
            void* var_d = nullptr;

            ~PacketEvent()
            {
                if(var_a != nullptr)
                {
                    free(var_a);
                }
                if(var_b != nullptr)
                {
                    free(var_b);
                }
                if(var_c != nullptr)
                {
                    free(var_c);
                }
                if(var_d != nullptr)
                {
                    free(var_d);
                }
            }
        };

        //What kind of general event is this
        enum EventType
        {
            input_event,
            cursor_event,
            ui_event,
            game_event
        };
        EventType type;

        //Game State targeted by the Event
        GameState target;

        //Linking structs to keywords
        union
        {
            InputEvent input;
            CursorEventClick cursor_click;
            CursorEventScroll cursor_scroll;
            SoundEventStart sound_start;
            SoundEventStop sound_stop;
            InterfaceEvent ui;
            GameEvent game;
            PacketEvent packet;
        };
    };
}
