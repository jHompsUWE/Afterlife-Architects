#include "pch.h"
#include "KaraStationWindow.h"

KaraStationWindow::KaraStationWindow(Vector2 _windowPosition, ID3D11Device* _d3dDevice, std::string _text,
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
    text_vec.push_back(new TextGO2D("KA_Heaven_3x3\n""Cost 100 Credits"));
    text_vec.back()->SetColour(Color((float*)&Colors::Black));
    text_vec.back()->SetPos(Vector2(window_pos.x+ 35,window_pos.y+ 95));
    text_vec.back()->SetScale(Vector2(0.3,0.3));

    text_vec.push_back(new TextGO2D("KA_Hell_3x3\n""Cost 100 Credits"));
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
    buttons.push_back(new Button(Vector2(window_pos.x+80,window_pos.y+50),
        DataManager::GetD3DDevice(),"KA_Heaven_3x3",
        window_9_gate,Vector2(0.6,0.6)));
    
    buttons.push_back(new Button(Vector2(window_pos.x+180,window_pos.y+50),
        DataManager::GetD3DDevice(),"KA_Hell_3x3",
        window_9_gate,Vector2(0.6,0.6)));
    
    buttons.push_back(new Button(Vector2(window_pos.x+80,window_pos.y+170),
        DataManager::GetD3DDevice(),"KS_Heaven_3x3",
        window_9_gate,Vector2(0.6,0.6)));
    
    buttons.push_back(new Button(Vector2(window_pos.x+180,window_pos.y+170),
        DataManager::GetD3DDevice(),"KS_Hell_3x3",
        window_9_gate,Vector2(0.6,0.6)));
    
    buttons.push_back(new Button(Vector2(window_pos.x+280,window_pos.y+170),
        DataManager::GetD3DDevice(),"KT_Heaven_1x1",
        window_9_gate,Vector2(0.5,0.5)));

    buttons.push_back(new Button(Vector2(window_pos.x+280,window_pos.y+50),
        DataManager::GetD3DDevice(),"KT_Hell_1x1",
        window_9_gate,Vector2(0.5,0.5)));
}

KaraStationWindow::~KaraStationWindow()
{
   
}

void KaraStationWindow::update(GameData* _gameData, Vector2& _mousePosition)
{
    UIWindow::update(_gameData,_mousePosition);
}

void KaraStationWindow::render(DrawData2D* _drawData)
{
    UIWindow::render(_drawData);
}

void KaraStationWindow::setScale(Vector2& _newScale)
{
    UIWindow::setScale(_newScale);
}

Vector2& KaraStationWindow::getPosition()
{
    return window_pos;
}

Vector2& KaraStationWindow::getButtonRes()
{
    return window_res;
}

void KaraStationWindow::reSize(Vector2 game_res)
{
    UIWindow::reSize(game_res);
}
