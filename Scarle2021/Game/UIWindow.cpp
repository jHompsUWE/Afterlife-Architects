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
    window_text_1 = new TextGO2D("Heaven Gate\n""Cost 100 Credits");
    window_text_1->SetColour(Color((float*)&Colors::Black));
    window_text_1->SetPos(Vector2(window_pos.x+ 30,window_pos.y+ 130));
    window_text_1->SetScale(Vector2(0.3,0.3));

    window_text_2 = new TextGO2D("Hell Gate\n""Cost 100 Credits");
    window_text_2->SetColour(Color((float*)&Colors::Black));
    window_text_2->SetPos(Vector2(window_pos.x+ 140,window_pos.y+ 130));
    window_text_2->SetScale(Vector2(0.3,0.3));
 
    window_text_3 = new TextGO2D(_text);
    window_text_3->SetColour(Color((float*)&Colors::Black));
    window_text_3->SetPos(window_pos);
    window_text_3->SetScale(Vector2(_setScale));
    
    window_text_4 = new TextGO2D(_text);
    window_text_4->SetColour(Color((float*)&Colors::Black));
    window_text_4->SetPos(window_pos);
    window_text_4->SetScale(Vector2(_setScale));
    

    //window buttons todo

    //test window
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
    for (auto button : buttons)
    {
        delete button;        
    }
    delete windowBackGround;
    
    delete window_text_1;
    delete window_text_2;
    delete window_text_3;
    delete window_text_4;
}

void UIWindow::update(GameData* _gameData, Vector2& _mousePosition)
{

    //updates buttons
    for (auto& button : buttons)
    {
        button->update(_gameData,_mousePosition);
    }
 
    
    windowBackGround->Tick(_gameData);
	
    if(window_text_1 != nullptr)
    {
        window_text_1->Tick(_gameData);
        window_text_2->Tick(_gameData);
        window_text_3->Tick(_gameData);
        window_text_4->Tick(_gameData);
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
    
    //renders buttons
    for (auto& button : buttons)
    {
        button->render(_drawData);
    }
    
    if(window_text_1 != nullptr)
    {
        window_text_1->Draw(_drawData);
        window_text_2->Draw(_drawData);
        //window_text_3->Draw(_drawData);
        //window_text_4->Draw(_drawData);
    }
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
    for (auto& button : buttons)
    {
        button->reSize(DataManager::GetRES());
    }
}

bool UIWindow::isInside(Vector2& point) const
{
    if(point.x >= window_pos.x && point.x <= (window_pos.x + window_res.x) &&
       point.y >= window_pos.y && point.y <= (window_pos.y + window_res.y))
           return true;
    
    return false;
}
