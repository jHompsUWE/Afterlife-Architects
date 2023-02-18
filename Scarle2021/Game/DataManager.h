#pragma once

//Main Scarle data containers 
#include "GameData.h"
#include "DrawData.h"
#include "DrawData2D.h"
#include "../DirectXTK/Inc/Effects.h"

/**
 * \brief This Singleton delivers the pointers to the main directX components
 * everywhere in the code base.
 *
 * Example of syntax to gather game data:
 * DataManager::GetGD();
 */
class DataManager
{
public:
    //Deleted copy constructor
    DataManager(const DataManager&) = delete;
    //Delete assignment operator
    DataManager& operator=(const DataManager&) = delete;

    //Create and gets instance
    static DataManager& Get()
    {
        static DataManager instance;
        return instance;
    }

    //Getters
    //Static, can be called via :: 
    static float& GetAR() {return Get().aspect_ratio;}
    static GameData* GetGD() {return Get().game_data;}
    static DrawData* GetDD() {return Get().draw_data;}
    static DrawData2D* GetDD2D() {return Get().draw_data2D;}
    static ID3D11Device1* GetD3DDevice() {return Get().d3d_device;}
    static ID3D11DeviceContext1* GetD3DContext() {return Get().d3d_context;}
    static IEffectFactory* GetEF() {return Get().effect_factory;}
    
    
    /**
     * \brief Populates all the pointers. do once at initialization
     * \param _aspect_ratio Float value of the aspect ration
     * \param _game_data Pointer to game data
     * \param _draw_data Pointer to draw data
     * \param _draw_data2D Pointer to draw data2D
     * \param _d3d_device Pointer to the d3d device
     * \param _d3d_context Pointer to the d3d context
     * \param _effect_factory Pointer to the effect factory
     */
    void PopulatePointers(float _aspect_ratio, GameData* _game_data, DrawData* _draw_data, 
        DrawData2D* _draw_data2D, ID3D11Device1* _d3d_device, ID3D11DeviceContext1* _d3d_context, 
        IEffectFactory* _effect_factory)
    {
        aspect_ratio = _aspect_ratio;
        game_data = _game_data;
        draw_data = _draw_data;
        draw_data2D = _draw_data2D;
        d3d_device = _d3d_device;
        d3d_context = _d3d_context;
        effect_factory = _effect_factory;
    }

private:
    //Private constructor
    DataManager() = default;

    //Scarle pointers
    float aspect_ratio = 0;
    GameData* game_data = nullptr;
    DrawData* draw_data = nullptr;
    DrawData2D* draw_data2D = nullptr;
    ID3D11Device1* d3d_device = nullptr;
    ID3D11DeviceContext1* d3d_context = nullptr;
    IEffectFactory* effect_factory = nullptr;
};
