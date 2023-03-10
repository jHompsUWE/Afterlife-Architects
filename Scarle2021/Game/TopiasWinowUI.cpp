#include "pch.h"
#include "TopiasWindowUI.h"

TopiasWindowUI::TopiasWindowUI(Vector2 _windowPosition, ID3D11Device* _d3dDevice, std::string _text,
    std::string _filepath, Vector2 _setScale):UIWindow()
{
     //setup for window background
    windowBackGround = new ImageGO2D(_filepath, _d3dDevice);
    windowBackGround->SetOrigin(Vector2(0, 0));
    windowBackGround->SetScale(Vector2(_setScale));

    //sets window res
    window_res = Vector2(windowBackGround->GetRes().x
        * windowBackGround->GetScale().x, windowBackGround->GetRes().y
        * windowBackGround->GetScale().y);

    // sets window pos
    window_pos = _windowPosition;
    windowBackGround->SetPos(window_pos);

    //setup button text
    text_vec.push_back(new TextGO2D("Heaven Topias \n""Cost 100 Credits"));
    text_vec.back()->SetColour(Color((float*)&Colors::Black));
    text_vec.back()->SetPos(Vector2(window_pos.x+ 35,window_pos.y+ 95));
    text_vec.back()->SetScale(Vector2(0.3,0.3));

    text_vec.push_back(new TextGO2D("Heaven Topias T2\n""Cost 100 Credits"));
    text_vec.back()->SetColour(Color((float*)&Colors::Black));
    text_vec.back()->SetPos(Vector2(window_pos.x+ 140,window_pos.y+ 95));
    text_vec.back()->SetScale(Vector2(0.3,0.3));
 
    text_vec.push_back(new TextGO2D("Hell Topias\n""Cost 100 Credits"));
    text_vec.back()->SetColour(Color((float*)&Colors::Black));
    text_vec.back()->SetPos(Vector2(window_pos.x+ 35,window_pos.y+ 220));
    text_vec.back()->SetScale(Vector2(0.3,0.3));
    
    text_vec.push_back(new TextGO2D("Hell Topias T2\n""Cost 100 Credits"));
    text_vec.back()->SetColour(Color((float*)&Colors::Black));
    text_vec.back()->SetPos(Vector2(window_pos.x+ 140,window_pos.y+ 220));
    text_vec.back()->SetScale(Vector2(0.3,0.3));
    
    

    //window buttons.....................
    buttons.push_back(new Button(Vector2(window_pos.x+80,window_pos.y+50),
        DataManager::GetD3DDevice(),"Topias_T1_Heaven_4x4",
        window_9_gate,Vector2(0.4,0.4)));
    
    buttons.push_back(new Button(Vector2(window_pos.x+180,window_pos.y+50),
        DataManager::GetD3DDevice(),"Topias_T2_Heaven_4x4",
        window_9_gate,Vector2(0.4,0.4)));
    
    buttons.push_back(new Button(Vector2(window_pos.x+80,window_pos.y+170),
        DataManager::GetD3DDevice(),"Topias_T1_Hell_4x4",
        window_9_gate,Vector2(0.4,0.4)));
    
    buttons.push_back(new Button(Vector2(window_pos.x+180,window_pos.y+170),
        DataManager::GetD3DDevice(),"Topias_T2_Hell_4x4",
        window_9_gate,Vector2(0.4,0.4)));
    
}

TopiasWindowUI::~TopiasWindowUI()
{
}

void TopiasWindowUI::update(GameData* _gameData, Vector2& _mousePosition)
{
    UIWindow::update(_gameData,_mousePosition);
}

void TopiasWindowUI::render(DrawData2D* _drawData)
{
    UIWindow::render(_drawData);
}

void TopiasWindowUI::set_postion(Vector2& _new_pos)
{
    UIWindow::setPostion(_new_pos);
}

void TopiasWindowUI::setScale(Vector2& _newScale)
{
    UIWindow::setScale(_newScale);
}

Vector2& TopiasWindowUI::getPosition()
{
    return window_pos;
}

Vector2& TopiasWindowUI::getButtonRes()
{
    return window_res;
}

void TopiasWindowUI::reSize(Vector2 game_res)
{
    UIWindow::reSize(game_res);
}
