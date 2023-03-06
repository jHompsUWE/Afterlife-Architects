#include "pch.h"
#include "AdvisorWindow.h"
#include <iostream>

#include "DataManager.h"


AdvisorWindow::AdvisorWindow(Vector2 _windowPosition, ID3D11Device* _d3dDevice, std::string _text,
                             std::string _filepath, Vector2 _setScale)
{
    //setup for window background
    windowBackGround = new ImageGO2D(_filepath, _d3dDevice);
    windowBackGround->SetOrigin(Vector2(0, 0));
    windowBackGround->SetScale(Vector2(0.5,0.5));

    //sets window res
    window_res = Vector2(windowBackGround->GetRes().x
        * windowBackGround->GetScale().x, windowBackGround->GetRes().y
        * windowBackGround->GetScale().y);

    // sets window pos
    window_pos = _windowPosition;
    windowBackGround->SetPos(window_pos);
    
    //window buttons.....................
    buttons.push_back(new Button(Vector2(window_pos.x+66,window_pos.y+158),
        DataManager::GetD3DDevice(),"ButtonAdvisor",
        window_9_gate,Vector2(0.225,0.25)));
    
    buttons.push_back(new Button(Vector2(window_pos.x+66,window_pos.y+172),
        DataManager::GetD3DDevice(),"ButtonAdvisor",
        window_9_gate,Vector2(0.225,0.25)));
    //window buttons.....................
    buttons.push_back(new Button(Vector2(window_pos.x+66,window_pos.y+187),
        DataManager::GetD3DDevice(),"ButtonAdvisor",
        window_9_gate,Vector2(0.225,0.25)));
    
    buttons.push_back(new Button(Vector2(window_pos.x+66,window_pos.y+202),
        DataManager::GetD3DDevice(),"ButtonAdvisor",
        window_9_gate,Vector2(0.225,0.25)));
    
    buttons.push_back(new Button(Vector2(window_pos.x+66,window_pos.y+217),
        DataManager::GetD3DDevice(),"ButtonAdvisor",
        window_9_gate,Vector2(0.225,0.25)));

    //image vector
    for (int i = 0; i < 13; i++)
    {
        image_vec_ar.push_back(new ImageGO2D(advisor_filenames_ar[i], DataManager::GetD3DDevice()));
        image_vec_ar[i]->SetPos(Vector2(window_pos.x + 260, window_pos.y + 80));
        image_vec_ar[i]->SetScale(Vector2(1, 1));
    }
    for (int j = 0; j < 12; j++)
    {
        image_vec_ja.push_back(new ImageGO2D(advisor_filenames_ja[j], DataManager::GetD3DDevice()));
        image_vec_ja[j]->SetPos(Vector2(window_pos.x + 100, window_pos.y + 80));
        image_vec_ja[j]->SetScale(Vector2(1, 1));
    }
    //text vector
    text_vec.push_back(new TextGO2D("ok what the hell do i write here"));
    text_vec[0]->SetPos(Vector2(window_pos.x+120,window_pos.y+150));
    text_vec[0]->SetScale(Vector2(0.3,0.3));
}
AdvisorWindow::~AdvisorWindow()
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
    
    for (auto image : image_vec_ar)
    {
        delete image;        
    }

    for (auto image : image_vec_ja)
    {
        delete image;        
    }
}

void AdvisorWindow::update(GameData* _gameData, Vector2& _mousePosition)
{
    //updates buttons
    for (const auto& button : buttons)
    {
        button->update(_gameData,_mousePosition);
    }
    //updates image
    for (auto image_ar : image_vec_ar)
    {
        image_ar->Tick(_gameData);      
    }
    for (auto image_ja : image_vec_ja)
    {
        image_ja->Tick(_gameData);      
    }

    //updates image
    for (auto text : text_vec)
    {
        text->Tick(_gameData);      
    }
    //window background
    windowBackGround->Tick(_gameData);

    //updates texts
    for (auto& text : text_vec)
    {
        text->Tick(_gameData);
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
        
        //button pos
        for (auto& button : buttons)
        {
            Vector2 const button_pos = button->getPosition();
            button->setPostion(button_pos - offset);
        }

        //image pos
        for (auto& image : image_vec_ar)
        {
            Vector2 const button_pos = image->GetPos();
            image->SetPos(button_pos - offset);
        }
        for (auto& image : image_vec_ja)
        {
            Vector2 const button_pos = image->GetPos();
            image->SetPos(button_pos - offset);
        }
        //text pos
        for (auto& text : text_vec)
        {
            Vector2 const button_pos = text->GetPos();
            text->SetPos(button_pos - offset);
        }
    }
    old_mouse_pos = _mousePosition;
}

void AdvisorWindow::render(DrawData2D* _drawData)
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
        text->Draw(_drawData);
    }
    
    for (int i = 0; i < 13; i++)
    {
        if (i == pointed_image_ar)
        {
            image_vec_ar[i]->Draw(_drawData);
        }
    }

    for (int j = 0; j < 12; j++)
    {
        if (j == pointed_image_ja)
        {
            image_vec_ja[j]->Draw(_drawData);
        }
    }

    for (auto text : text_vec)
    {
        text->Draw(_drawData);       
    }
}

void AdvisorWindow::set_postion(Vector2& _new_pos)
{
    window_pos = _new_pos;
}

void AdvisorWindow::set_scale(Vector2& _newScale)
{
}

Vector2& AdvisorWindow::getPosition()
{
    return window_pos;
}

Vector2& AdvisorWindow::getButtonRes()
{
    return window_res;
}

void AdvisorWindow::reSize(Vector2 game_res)
{   
    auto& scale = windowBackGround->ReSize(game_res.x, game_res.y);
    //reScales background
    window_res *= scale;
    window_pos *= scale;
    
    // resize buttons of UI window
    for (const auto& button : buttons)
    {
        button->reSize(game_res);
    }
    for (auto text : text_vec)
    {
        text->ReSize(game_res.x, game_res.y);
    }
    for (auto image : image_vec_ar)
    {
        image->ReSize(game_res.x, game_res.y);
    }
    for (auto image : image_vec_ja)
    {
        image->ReSize(game_res.x, game_res.y);
    }
    for (auto text : text_vec)
    {
        text->ReSize(game_res.x, game_res.y);
    }
}

bool AdvisorWindow::isInside(Vector2& point) const
{
    //checks bounding box of UI window
    if(point.x >= window_pos.x && point.x <= (window_pos.x + window_res.x) &&
       point.y >= window_pos.y && point.y <= (window_pos.y + window_res.y))
           return true;
    
    return false;
}

void AdvisorWindow::set_aria_image(string filename)
{
    for (int i = 0; i < 13; i++)
    {
        if (advisor_filenames_ar[i] == filename)
        {
            pointed_image_ar = i;
        }
    }
}

void AdvisorWindow::set_jasper_image(string filename)
{
    for (int i = 0; i < 12 ; i ++)
    {
        if (advisor_filenames_ja[i] == filename)
        {
            pointed_image_ja = i;
        }
    }
}

void AdvisorWindow::set_text(string new_string)
{
    text_vec[0]->ChangeString(new_string);
}
