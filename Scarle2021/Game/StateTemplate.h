#pragma once
#include "ScarlePointers.h"

/**
 * \brief This is an interface where all the
 * Game States inherit from
 */
class StateTemplate
{
public:
    explicit StateTemplate() = default;
    virtual ~StateTemplate() = default;

    // Init
    virtual bool init() = 0;

    // Updates
    virtual void Update() = 0;
    virtual void ScaledUpdate() = 0;
    virtual void LateUpdate() = 0;

    // M&K input queue
    virtual void GetInput() = 0;

protected:
    //Data pointer
    GameData* game_data{};
};
