#include "pch.h"
#include "GamePlay.h"

GamePlay::GamePlay()
= default;

GamePlay::~GamePlay()
{
    delete tilemap;
}

bool GamePlay::init()
{
    text = new TextGO2D("this ist GAMEPLAYYY");
    text->SetPos(Vector2(100, 10));
    text->SetColour(Color((float*)&Colors::Yellow));

    tilemap = new Tilemap(DataManager::GetD3DDevice(), 10);

    cube = new VBCube();
    cube->init(3, DataManager::GetD3DDevice());
    
    return true;
}

void GamePlay::Update(GameData* game_data)
{
    if (do_once)
    {
        do_once = false;
        // Tick tilemap once to update position
        tilemap->Tick(game_data);
    }

    cube->Tick(game_data);
}

void GamePlay::ScaledUpdate(GameData* game_data, float& scaled_dt)
{
}

void GamePlay::LateUpdate(GameData* game_data)
{
    // Update mouse position
    mouse_screen_pos.x = game_data->mouse_state.x;
    mouse_screen_pos.y = game_data->mouse_state.y;
}

void GamePlay::GetEvents(std::list<AfterlifeEvent>& event_list)
{
    for (auto& event : event_list)
    {
        if (event == input_E)
        {
            tilemap->ChangeAllTexture("Tile_Inactive_Red");
        }
    }
}

void GamePlay::Render2D(DrawData2D* draw_data2D)
{
    text->Draw(draw_data2D);
}

void GamePlay::Render3D(DrawData* draw_data)
{
    tilemap->Draw(draw_data);

    cube->Draw(draw_data);
    
    if (do_once_2)
    {
        do_once_2 = false;

        //std::cout << draw_data->main_camera->GetPos().x << std::endl;
        //std::cout << draw_data->main_camera->GetPos().y << std::endl;
        //std::cout << draw_data->main_camera->GetPos().z << std::endl;
    }

    Vector3 temp_pos = Vector3(mouse_screen_pos.x, mouse_screen_pos.y, 0);

    mouse_world_pos = XMVector3Unproject(temp_pos, 0, 0, 800, 600, 0.0f, 10000.0f, draw_data->main_camera->GetProj(),
        draw_data->main_camera->GetView(), draw_data->main_camera->GetWorldMatrix());

    cube->SetPos(mouse_world_pos);

    //std::cout << "X: " << mouse_world_pos.x << " Y: " << mouse_world_pos.y << " Z: " << mouse_world_pos.z << std::endl;
}


