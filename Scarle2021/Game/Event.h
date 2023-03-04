#pragma once

#include "ActionListCursor.h"
#include "ActionListInput.h"
#include "ActionListInterface.h"
#include "ActionListGame.h"

namespace AL
{
    //Type of events
    enum EventType
    {
        unknown = 0,
        event_input,
        event_cursor_click,
        event_cursor_scroll,
        sound_event_start,
        sound_event_stop,
        event_ui,
        event_game
    };

    //Normal input event
    class Event
    {
    public:
        Event(EventType _type) : type(_type){}
        ~Event(){}
        
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
         * \var ticks = how much scrolling has taken place
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

        //What kind of general event is this
        EventType type = unknown;
        
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
        };
    };
}

