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
    windowText = new TextGO2D(_text);
    windowText->SetColour(Color((float*)&Colors::Black));
    windowText->SetPos(window_pos);
    windowText->SetScale(Vector2(_setScale));
    

    //window buttons todo

    //test window
    button_one = new Button(Vector2(window_pos.x+80,window_pos.y+50),
        DataManager::GetD3DDevice(),"Gate_T1_Heaven_3x3",
        test_window,Vector2(1,1));
    
    button_two = new Button(Vector2(window_pos.x+180,window_pos.y+50),
        DataManager::GetD3DDevice(),"Gate_T1_Hell_3x3",
        test_window,Vector2(1,1));
    
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
    delete windowBackGround;
    delete windowText;
}

void UIWindow::update(GameData* _gameData, Vector2& _mousePosition)
{
    
    //update window
    button_one->update(_gameData,_mousePosition);
    button_two->update(_gameData,_mousePosition);
    
    windowBackGround->Tick(_gameData);
	
    if(windowText != nullptr)
    {
        windowText->Tick(_gameData);
    }
	
    if(isInside(_mousePosition))
    {
        if(DataManager::GetGD()->mouse_state.leftButton)
        {
            std::cout<<"clicked"<<std::endl;
        }
    }
}

void UIWindow::render(DrawData2D* _drawData)
{
    windowBackGround->Draw(_drawData);
	
    if(windowText != nullptr)
    {
        windowText->Draw(_drawData);
    }
    
    //renders window
    button_one->render(_drawData);
    button_two->render(_drawData);
}

void UIWindow::setPostion(Vector2& _new_pos)
{
    
}

void UIWindow::setScale(Vector2& _newScale)
{
    
}

Vector2& UIWindow::getPosition()
{
    return window_res;
}

Vector2& UIWindow::getButtonRes()
{
    return window_pos;
}

void UIWindow::reSize(std::pair<int*, int*> game_res)
{
}

bool UIWindow::isInside(Vector2& point) const
{
    if(point.x >= window_pos.x && point.x <= (window_pos.x + window_res.x) &&
       point.y >= window_pos.y && point.y <= (window_pos.y + window_res.y))
           return true;
    
    return false;
}
