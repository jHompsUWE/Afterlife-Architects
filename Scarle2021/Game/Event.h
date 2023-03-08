#pragma once

#include "ActionListCursor.h"
#include "ActionListInput.h"
#include "ActionListInterface.h"
#include "ActionListGame.h"
#include "ActionListBuildSys.h"

namespace AL
{
    //Type of events
    enum EventType
    {
        unknown = 0,
        event_input,
        event_cursor_move,
        event_cursor_interact,
        event_sound_start,
        event_sound_stop,
        event_ui,
        event_build_sys,
        event_game
    };

    //Normal input event
    class Event
    {
    public:
        //Explicit constructor as event type is needed for sorting
        explicit Event(EventType _type) : type(_type){}
        ~Event() = default;

        /**
         * \brief Event is fired for input entries that are mapped to this Event
         * \var action = action to process 
         * \var active = is button currently being pressed
         */
        struct InputEvent
        {
            Input::Action action = Input::Action::unknown;
            bool active = NULL;
        };

        /**
         * \brief Event is fired when the position of the cursor has changed
         */
        struct CursorEventMove
        {
            int pos_x = NULL;
            int pos_y = NULL;
        };
        
        /**
         * \brief Event is fired when a "interact" action is performed
         * \var action = action to process 
         * \var active = if the action should be handled as a start or finish of this event
         */
        struct CursorEventInteract
        {
            Cursor::Action action = Cursor::Action::unknown;
            bool active = NULL;
        };
        
        /**
         * \brief Event to start to play a sound
        * \var filename = filename as seen in the asset pipeline, no file extension, max 31 chars.
         * \var volume
         * \var loop = will it loop?
         */
        struct SoundEventStart
        {
            char filename[32] = "unknown";
            float volume = NULL;
            bool loop = NULL;
        };

        /**
         * \brief Event to a sound from playing
         * \var filename = filename as seen in the asset pipeline, no file extension, max 31 chars.
         */
        struct SoundEventStop
        {
            char filename[32] = "unknown";
        };

        /**
         * \brief Event to redirect an action to the UI
         */
        struct InterfaceEvent
        {
            UI::Action action = UI::Action::unknown;
        };

        /**
         * \brief Event to redirect an action to the UI
         */
        struct BuildSysEvent
        {
            BuildSys::Action action = BuildSys::Action::unknown;
        };
        
        /**
         * \brief Event to be redirect an action to the game
         */
        struct GameEvent
        {
            Game::Action action = Game::Action::unknown;
        };

        //What kind of general event is this
        EventType type = unknown;
        
        //Linking structs to keywords
        //A union will make it so that each element will share the same
        //memory, therefore making events lightweight
        union
        {
            InputEvent input;
            CursorEventMove cursor_moved;
            CursorEventInteract cursor_interact;
            SoundEventStart sound_start;
            SoundEventStop sound_stop;
            BuildSysEvent build_sys;
            InterfaceEvent ui;
            GameEvent game;
        };
    };
}

