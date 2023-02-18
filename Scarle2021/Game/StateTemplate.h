#pragma once
#include "DataManager.h"
#include "ObjectList.h"
#include "iostream"

/**
 * \brief This is an interface where all the
 * Game States inherit from
 */
class StateTemplate
{
public:
    explicit StateTemplate(GameData* _game_data) : game_data(_game_data){};
    virtual ~StateTemplate() = default;

    // Init
    virtual bool init() = 0;

    // Updates
    virtual void Update(float& delta_time) = 0;
    virtual void ScaledUpdate(float& delta_time) = 0;
    virtual void LateUpdate() = 0;

    // Render
    virtual void Render3D() = 0;
    virtual void Render2D() = 0;
    
    // M&K input queue
    virtual void GetInput() = 0;

protected:
    //Data pointer
    GameData* game_data;
};
