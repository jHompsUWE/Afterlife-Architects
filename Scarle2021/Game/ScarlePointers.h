#pragma once

//Main Scarle data containers 
#include "GameData.h"
#include "DrawData.h"
#include "DrawData2D.h"
#include "../DirectXTK/Inc/Effects.h"

class ScarlePointers
{
public:
    //Deleted copy constructor
    ScarlePointers(const ScarlePointers&) = delete;
    //Delete assignment operator
    ScarlePointers& operator=(const ScarlePointers&) = delete;

    //Create and gets instance
    static ScarlePointers& Get()
    {
        static ScarlePointers instance;
        return instance;
    }

    //Getters
    static float& GetAR() {return Get().aspect_ratio;}
    static GameData* GetGD() {return Get().game_data;}
    static DrawData* GetDD() {return Get().draw_data;}
    static DrawData2D* GetDD2D() {return Get().draw_data2D;}
    static ID3D11Device1* GetD3DDevice() {return Get().d3d_device;}
    static ID3D11DeviceContext1* GetD3DContext() {return Get().d3d_context;}
    static IEffectFactory* GetEF() {return Get().effect_factory;}
    
    //Setter function
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
    ScarlePointers() = default;

    //Scarle pointers
    float aspect_ratio = 0;
    GameData* game_data = nullptr;
    DrawData* draw_data = nullptr;
    DrawData2D* draw_data2D = nullptr;
    ID3D11Device1* d3d_device = nullptr;
    ID3D11DeviceContext1* d3d_context = nullptr;
    IEffectFactory* effect_factory = nullptr;
};
