#include "pch.h"
#include "SoulViewWindow.h"
#include <iostream>

#include "DataManager.h"


SoulViewWindow::SoulViewWindow(Vector2 _windowPosition, ID3D11Device* _d3dDevice, std::string _text,
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
    window_pos = _windowPosition;
    windowBackGround->SetPos(window_pos);

    //text vector
    text_vec.push_back(new TextGO2D("Oscar Wilkinson"));
    text_vec[0]->SetPos(Vector2(window_pos.x + 78, window_pos.y+1.5));
    text_vec[0]->SetScale(Vector2(_setScale * 0.2));
    text_vec.push_back(new TextGO2D("Punished for Pride"));
    text_vec[1]->SetPos(Vector2(window_pos.x + 17, window_pos.y+212));
    text_vec[1]->SetScale(Vector2(_setScale * 0.2));
    text_vec.push_back(new TextGO2D("Serving for 934 years"));
    text_vec[2]->SetPos(Vector2(window_pos.x + 17, window_pos.y+223));
    text_vec[2]->SetScale(Vector2(_setScale * 0.2));
    text_vec.push_back(new TextGO2D("Believes in HAHASUMARALFism"));
    text_vec[3]->SetPos(Vector2(window_pos.x + 17, window_pos.y+234));
    text_vec[3]->SetScale(Vector2(_setScale * 0.2));
}

SoulViewWindow::~SoulViewWindow()
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

    for (auto image : image_vec)
    {
        delete image;
    }
}

void SoulViewWindow::update(GameData* _gameData, Vector2& _mousePosition)
{
    //updates buttons
    for (const auto& button : buttons)
    {
        button->update(_gameData, _mousePosition);
    }
    //updates image
    for (auto image : image_vec)
    {
        image->Tick(_gameData);
    }

    //window background
    windowBackGround->Tick(_gameData);

    //updates texts
    for (auto& text : text_vec)
    {
        text->Tick(_gameData);
    }

    //checks if mouse inside UI window 
    if (isInside(_mousePosition))
    {
        //if clicked
        if (DataManager::GetGD()->mouse_state.leftButton)
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
        windowBackGround->SetPos(windowBackGround->GetPos() - offset);
        window_pos = windowBackGround->GetPos();

        //button pos
        for (auto& button : buttons)
        {
            Vector2 const button_pos = button->getPosition();
            button->setPostion(button_pos - offset);
        }

        //image pos
        for (auto& image : image_vec)
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

void SoulViewWindow::render(DrawData2D* _drawData)
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

    for (const auto& image : image_vec)
    {
        image->Draw(_drawData);
    }
}

void SoulViewWindow::set_postion(Vector2& _new_pos)
{
    window_pos = _new_pos;
}

void SoulViewWindow::set_scale(Vector2& _newScale)
{
}

Vector2& SoulViewWindow::getPosition()
{
    return window_pos;
}

Vector2& SoulViewWindow::getButtonRes()
{
    return window_res;
}

void SoulViewWindow::reSize(Vector2 game_res)
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
    for (auto image : image_vec)
    {
        image->ReSize(game_res.x, game_res.y);
    }
}

bool SoulViewWindow::isInside(Vector2& point) const
{
    //checks bounding box of UI window
    if (point.x >= window_pos.x && point.x <= (window_pos.x + window_res.x) &&
        point.y >= window_pos.y && point.y <= (window_pos.y + window_res.y))
        return true;

    return false;
}

void SoulViewWindow::generateRandSoul()
{
    srand(std::time(nullptr));

    string temp_str;

    string temp_string = random_names[std::rand()%5];
    text_vec[0]->ChangeString(temp_string);

    srand(std::time(nullptr) * 2);
    int rand_pun_or_rew = rand()%12;
    if (rand_pun_or_rew > 6)
    {
        text_vec[1]->ChangeString("Rewarded for " + available_punishments[rand_pun_or_rew]);
    }
    else
    {
        text_vec[1]->ChangeString("Punished for " + available_punishments[rand_pun_or_rew]);
    }

    srand(std::time(nullptr) * 3);
    text_vec[2]->ChangeString("Years left at location: " + std::to_string((rand() % 950)+50));

    srand(std::time(nullptr) * 5);
    text_vec[3]->ChangeString("Believes in " + generateBelief() + "ism");
}

string SoulViewWindow::generateBelief()
{
    srand(std::time(nullptr) * 120);
    string temp_string = beliefOne[(rand() * 723) % 4] + beliefTwo[(rand() * 542) % 2] + beliefThree[(rand() * 215) % 2];
    return temp_string;
}
