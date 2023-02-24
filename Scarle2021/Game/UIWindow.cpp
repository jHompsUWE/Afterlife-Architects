#include "pch.h"
#include "UIWindow.h"
#include <iostream>
#include "DataManager.h"

UIWindow::UIWindow(Vector2 _windowPosition, ID3D11Device* _d3dDevice,
    std::string _text, std::string _filepath,Vector2 _setScale)
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
    window_pos = _windowPosition - window_res/2;
    windowBackGround->SetPos(window_pos);

    //setup button text
    text_vec.push_back(new TextGO2D("Heaven Gate\n""Cost 100 Credits"));
    text_vec.back()->SetColour(Color((float*)&Colors::Black));
    text_vec.back()->SetPos(Vector2(window_pos.x+ 30,window_pos.y+ 130));
    text_vec.back()->SetScale(Vector2(0.3,0.3));

    text_vec.push_back(new TextGO2D("Hell Gate\n""Cost 100 Credits"));
    text_vec.back()->SetColour(Color((float*)&Colors::Black));
    text_vec.back()->SetPos(Vector2(window_pos.x+ 140,window_pos.y+ 130));
    text_vec.back()->SetScale(Vector2(0.3,0.3));
 
    text_vec.push_back(new TextGO2D(_text));
    text_vec.back()->SetColour(Color((float*)&Colors::Black));
    text_vec.back()->SetPos(window_pos);
    text_vec.back()->SetScale(Vector2(_setScale));
    
    text_vec.push_back(new TextGO2D(_text));
    text_vec.back()->SetColour(Color((float*)&Colors::Black));
    text_vec.back()->SetPos(window_pos);
    text_vec.back()->SetScale(Vector2(_setScale));
    

    //window buttons.....................
    buttons.push_back(new Button(Vector2(window_pos.x+80,window_pos.y+50),
        DataManager::GetD3DDevice(),"Gate_T1_Heaven_3x3",
        test_window,Vector2(1,1)));
    
    buttons.push_back(new Button(Vector2(window_pos.x+180,window_pos.y+50),
        DataManager::GetD3DDevice(),"Gate_T1_Hell_3x3",
        test_window,Vector2(1,1)));
    
}

UIWindow::UIWindow(Vector2 _windowPosition, ID3D11Device* _d3dDevice,
    std::string _filepath, Vector2 _setScale)
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
    window_pos = _windowPosition - window_res/2;
    windowBackGround->SetPos(window_pos);
}

UIWindow::~UIWindow()
{
    //deletes pointers
    for (auto button : buttons)
    {
        delete button;        
    }
    delete windowBackGround;

    for (auto text : text_vec)
    {
        delete text;
    }
}

void UIWindow::update(GameData* _gameData, Vector2& _mousePosition)
{
    
    //updates buttons
    for (const auto& button : buttons)
    {
        button->update(_gameData,_mousePosition);
    }
 
    //window background
    windowBackGround->Tick(_gameData);

    //updates texts
    for (const auto& text : text_vec)
    {
        if(text != nullptr)
        {
            text->Tick(_gameData);
        }
	
    }
    
    //checks if mouse inside UI window 
    if(isInside(_mousePosition))
    {

        //if clicked
        if(DataManager::GetGD()->mouse_state.leftButton)
        {
            toggle_click = true;
        }
        else
        {
            toggle_click = false;
        }
    }
    else
    {
        toggle_click = false;
    }


    //if clicked updates pos and scale for window drag  
    if (toggle_click)
    {

        //new pos on click and drag 
        const Vector2 offset = old_mouse_pos - _mousePosition;
        windowBackGround->SetPos(windowBackGround->GetPos()-offset);
        window_pos = windowBackGround->GetPos();


        //text pos
        for (const auto& text : text_vec)
        {
            text->SetPos(text->GetPos() - offset);
        }


        //button pos
        for (auto& button : buttons)
        {
            Vector2 const button_pos = button->getPosition();
            button->setPostion(button_pos - offset);
            
        }
    }
    old_mouse_pos = _mousePosition;
}

void UIWindow::render(DrawData2D* _drawData)
{
    windowBackGround->Draw(_drawData);
    
    //renders buttons
    for (const auto& button : buttons)
    {
        button->render(_drawData);
    }
    // renders texts
    for (const auto& text : text_vec)
    {
        if(text != nullptr)
        {
            text->Draw(_drawData);
        }
    }
}

void UIWindow::setPostion(Vector2& _new_pos)
{
    window_pos = _new_pos;
}

void UIWindow::setScale(Vector2& _newScale)
{
    
}

Vector2& UIWindow::getPosition()
{
    return window_pos;
}

Vector2& UIWindow::getButtonRes()
{
    return window_res;
}

void UIWindow::reSize(std::pair<int*, int*> game_res)
{
    //stores getRes
    auto& resize = DataManager::GetRES();

    //reScales background
    window_res *= windowBackGround->ReSize(resize.first,resize.second);
    
    // resize buttons of UI window
    for (const auto& button : buttons)
    {
        button->reSize(resize);
    }
    for (auto text : text_vec)
    {
        text->ReSize(resize.first,resize.second);
    }
}

bool UIWindow::isInside(Vector2& point) const
{

    //checks bounding box of UI window
    if(point.x >= window_pos.x && point.x <= (window_pos.x + window_res.x) &&
       point.y >= window_pos.y && point.y <= (window_pos.y + window_res.y))
           return true;
    
    return false;
}
