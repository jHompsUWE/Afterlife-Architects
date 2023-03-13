#pragma once
#include "UIWindow.h"
#include "NewEventManager.h"

class AdvisorWindow : public IEventReceiver
{
public:

    AdvisorWindow(Vector2 _windowPosition, ID3D11Device* _d3dDevice,
        std::string _text,std::string _filepath,Vector2 _setScale);
    
    ~AdvisorWindow() override;
    
    void update(GameData* _gameData, Vector2& _mousePosition);
    void render(DrawData2D* _drawData);
    void ReceiveEvents(const AL::Event& al_event) override;

    void set_postion(Vector2& _new_pos);
    void set_scale(Vector2& _newScale);

    void set_text(string new_string);
    void set_aria_image(string filename);
    void set_jasper_image(string filename);
    void set_option_box(int box_num, int indicator, string title);
	
    Vector2& getPosition();
    Vector2& getButtonRes();
	
    void reSize(Vector2 game_res);
    bool is_visible = false;
    
private:
    
    //mouse pointer inside window
    bool isInside(Vector2& point) const;
    bool toggle_click = false;
    Vector2 mouse_pos {0,0};
    Vector2 old_mouse_pos{0,0};
    
    ImageGO2D* windowBackGround = nullptr;
  
    //vector of buttons 
    std::vector<UIButtonInterFace*> buttons;
    std::vector<TextGO2D*> text_vec;
    std::vector<ImageGO2D*> image_vec_ar;
    std::vector<ImageGO2D*> image_vec_ja;
    std::vector<ImageGO2D*> indicators_ar;
    std::vector<ImageGO2D*> indicators_ja;
    bool show_ind_ar[5];
    bool show_ind_ja[5];
 
    //vectors
    Vector2 window_res {0,0};
    Vector2 window_pos {0,0};

    //filenames for adivsor images
    string advisor_filenames_ar[13] = { "ArA", "ArE", "ArL", "ArM", "ArO", "ArS", "ArBlink1", "ArBlink2", "ArBlink3", "ArTongue1", "ArTongue2", "ArTongue3", "ArIdle1"};
    string advisor_filenames_ja[12] = { "JaA", "JaC", "JaE", "JaH", "JaM", "JaY", "JaBlink1", "JaBlink2", "JaBlink3", "JaWings1", "JaWings2", "JaIdle1"};
    int pointed_image_ar = 12;
    int pointed_image_ja = 11;
};

