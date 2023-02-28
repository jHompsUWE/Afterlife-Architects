#pragma once
#include "UIWindow.h"
class AdvisorWindow
{
public:

    AdvisorWindow(Vector2 _windowPosition, ID3D11Device* _d3dDevice,
        std::string _text,std::string _filepath,Vector2 _setScale);
    
    ~AdvisorWindow();
    
    void update(GameData* _gameData, Vector2& _mousePosition);
    void render(DrawData2D* _drawData);

    void set_postion(Vector2& _new_pos);
    void set_scale(Vector2& _newScale);
	
    Vector2& getPosition();
    Vector2& getButtonRes();
	
    void reSize(std::pair<int*, int*> game_res);
    bool is_visible = true;
    
private:
    
    //mouse pointer inside window
    bool isInside(Vector2& point) const;
    bool toggle_click = false;
    Vector2 old_mouse_pos{0,0};
    
    ImageGO2D* windowBackGround = nullptr;
  
    //vector of buttons 
    std::vector<Button*> buttons;
    std::vector<TextGO2D*> text_vec;
    std::vector<ImageGO2D*> image_vec;
 
    //vectors
    Vector2 window_res {0,0};
    Vector2 window_pos {0,0};
};

