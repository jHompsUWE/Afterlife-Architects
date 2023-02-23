#pragma once
#include "Button.h"
#include "GameData.h"
#include "ImageGO2D.h"
#include "TextGO2D.h"
#include "EventManager.h"

class UIWindow
{
public:
    UIWindow(Vector2 _windowPosition, ID3D11Device* _d3dDevice,
        std::string _text,std::string _filepath,Vector2 _setScale);
    
    UIWindow(Vector2 _windowPosition, ID3D11Device* _d3dDevice,
        std::string _filepath,Vector2 _setScale);
    ~UIWindow();

    void update(GameData* _gameData, Vector2& _mousePosition);
    void render(DrawData2D* _drawData);

    void setPostion(Vector2& _new_pos) ;
    void setScale(Vector2& _newScale) ;
	
    Vector2& getPosition() ;
    Vector2& getButtonRes() ;
	
    void reSize(std::pair<int*, int*> game_res) ;

private:

    //mouse pointer inside window
    bool isInside(Vector2& point) const;
    bool toggle_click = false;
    Vector2 old_mouse_pos{0,0};
    
    ImageGO2D* windowBackGround = nullptr;
  
    //vector of buttons 
    std::vector<Button*> buttons;
    std::vector<TextGO2D*> text_vec;
    
    Vector2 window_res = {0,0};
    Vector2 window_pos = {0,0};

    enum texts_enum
    {
        text1,text2,text3,text4,
    };
};

