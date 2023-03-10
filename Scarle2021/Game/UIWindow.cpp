#include "pch.h"
#include "UIWindow.h"
#include <iostream>


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
    window_pos = _windowPosition;
    windowBackGround->SetPos(window_pos);

    //setup button text
    text_vec.push_back(new TextGO2D("Heaven Gate\n""Cost 100 Credits"));
    text_vec.back()->SetColour(Color((float*)&Colors::Black));
    text_vec.back()->SetPos(Vector2(window_pos.x+ 35,window_pos.y+ 95));
    text_vec.back()->SetScale(Vector2(0.3,0.3));

    text_vec.push_back(new TextGO2D("Heaven Gate T2\n""Cost 100 Credits"));
    text_vec.back()->SetColour(Color((float*)&Colors::Black));
    text_vec.back()->SetPos(Vector2(window_pos.x+ 140,window_pos.y+ 95));
    text_vec.back()->SetScale(Vector2(0.3,0.3));
 
    text_vec.push_back(new TextGO2D("Hell Gate\n""Cost 100 Credits"));
    text_vec.back()->SetColour(Color((float*)&Colors::Black));
    text_vec.back()->SetPos(Vector2(window_pos.x+ 35,window_pos.y+ 220));
    text_vec.back()->SetScale(Vector2(0.3,0.3));
    
    text_vec.push_back(new TextGO2D("Hell Gate T2\n""Cost 100 Credits"));
    text_vec.back()->SetColour(Color((float*)&Colors::Black));
    text_vec.back()->SetPos(Vector2(window_pos.x+ 140,window_pos.y+ 220));
    text_vec.back()->SetScale(Vector2(0.3,0.3));

    text_vec.push_back(new TextGO2D("Hell Gate T3\n""Cost 100 Credits"));
    text_vec.back()->SetColour(Color((float*)&Colors::Black));
    text_vec.back()->SetPos(Vector2(window_pos.x+ 240,window_pos.y+ 220));
    text_vec.back()->SetScale(Vector2(0.3,0.3));

    text_vec.push_back(new TextGO2D("Heaven Gate T3\n""Cost 100 Credits"));
    text_vec.back()->SetColour(Color((float*)&Colors::Black));
    text_vec.back()->SetPos(Vector2(window_pos.x+ 240,window_pos.y+ 95));
    text_vec.back()->SetScale(Vector2(0.3,0.3));
    
    //window buttons.....................
    buttons.push_back(new Button<AL::BuildSys::Section, StructureType>(Vector2(window_pos.x+80,window_pos.y+50),
        DataManager::GetD3DDevice(),"Gate_T1_Heaven_3x3",
        AL::EventType::event_build_sys,AL::BuildSys::structure, Gate_T1,Vector2(0.6,0.6)));
    
    buttons.push_back(new Button<AL::BuildSys::Section, StructureType>(Vector2(window_pos.x+180,window_pos.y+50),
        DataManager::GetD3DDevice(),"Gate_T2_Heaven_3x3",
        AL::EventType::event_build_sys,AL::BuildSys::structure, Gate_T2,Vector2(0.6,0.6)));
    
    buttons.push_back(new Button<AL::BuildSys::Section, StructureType>(Vector2(window_pos.x+80,window_pos.y+170),
        DataManager::GetD3DDevice(),"Gate_T1_Hell_3x3",
        AL::EventType::event_build_sys,AL::BuildSys::structure, Gate_T1,Vector2(0.6,0.6)));
    
    buttons.push_back(new Button<AL::BuildSys::Section, StructureType>(Vector2(window_pos.x+180,window_pos.y+170),
        DataManager::GetD3DDevice(),"Gate_T2_Hell_3x3",
        AL::EventType::event_build_sys,AL::BuildSys::structure, Gate_T2,Vector2(0.6,0.6)));
    
    buttons.push_back(new Button<AL::BuildSys::Section, StructureType>(Vector2(window_pos.x+280,window_pos.y+170),
        DataManager::GetD3DDevice(),"Gate_T3_Hell_4x4",
        AL::EventType::event_build_sys,AL::BuildSys::structure, Gate_T3,Vector2(0.5,0.5)));
    
    buttons.push_back(new Button<AL::BuildSys::Section, StructureType>(Vector2(window_pos.x+280,window_pos.y+50),
        DataManager::GetD3DDevice(),"Gate_T3_Heaven_4x4",
        AL::EventType::event_build_sys,AL::BuildSys::structure, Gate_T3,Vector2(0.5,0.5)));

    AL::NewEventManager::AddEventReceiver(this);
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
    
    AL::NewEventManager::AddEventReceiver(this);
}

UIWindow::UIWindow()
{
    AL::NewEventManager::AddEventReceiver(this);
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

    AL::NewEventManager::RemoveEventReceiver(this);
}

void UIWindow::update(GameData* _gameData, Vector2& _mousePosition)
{
    if(!is_visible) return;

    mouse_pos = _mousePosition;
    
    //updates buttons
    for (const auto& button : buttons)
    {
        button->update(_gameData);
        if(button->close_window)
        {
            setVisibility(false);
            button->close_window = false;
        }
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
    
    //if clicked updates pos and scale for window drag  
    if (toggle_click && isInside(mouse_pos))
    {

        //new pos on click and drag 
        const Vector2 offset = old_mouse_pos - mouse_pos;
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
    old_mouse_pos = mouse_pos;
}

void UIWindow::render(DrawData2D* _drawData)
{
    if(!is_visible) return;
    
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

void UIWindow::ReceiveEvents(const AL::Event& al_event)
{
    switch (al_event.type)
    {
        case AL::event_input:
            break;

    case AL::event_cursor_interact:
            //Saves the state of the action
            if(al_event.cursor_interact.action == AL::Cursor::button_input1)
            {
                toggle_click = al_event.cursor_interact.active;
            }
            break;

        default:
            break;
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

void UIWindow::reSize(Vector2 game_res)
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
}

void UIWindow::setVisibility(bool _vis)
{
    is_visible = _vis;
    for (auto button : buttons)
    {
        button->interactable = _vis;
    }
}

const bool& UIWindow::getVisibility()
{
    return is_visible;
}

bool UIWindow::isInside(Vector2& point) const
{

    //checks bounding box of UI window
    if(point.x >= window_pos.x && point.x <= (window_pos.x + window_res.x) &&
       point.y >= window_pos.y && point.y <= (window_pos.y + window_res.y))
           return true;
    
    return false;
}
