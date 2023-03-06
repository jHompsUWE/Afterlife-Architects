#pragma once

#include "GameData.h"
#include "ImageGO2D.h"
#include "TextGO2D.h"
#include "EventManager.h"
#include "UIButtonInterFace.h"
#include "Button.h"
#include "DataManager.h"


class UIPanel
{
public:
    UIPanel(Vector2 _panelPosition, ID3D11Device* _d3dDevice,std::string
        _filepath,Vector2 _setScale);

    ~UIPanel();

    void update(GameData* _gameData, Vector2& _mousePosition);
    void render(DrawData2D* _drawData);

    void setPostion(Vector2 _new_pos);
    void setScale(Vector2& _newScale);
	
    Vector2& getPosition();
    Vector2& getButtonRes();
	
    void reSize(Vector2 game_res);
	

private:
    //mouse pointer inside button
    bool isInsidePanel(Vector2& point) const;

    //Button vector
    std::vector<UIButtonInterFace*> buttons;
    std::vector<TextGO2D*> text;
    
    ImageGO2D* panel_back_ground = nullptr;
    //TextGO2D* panel_text = nullptr;

    //ImageGO2D* ui_panel;
    
    Vector2 panel_res {0,0};
    Vector2 panel_pos {0,0};
    Vector2 old_mouse_pos_panel {0,0};

    bool toggle_click_panel = false;
    float year = 0;
    int credits = 0;
};

