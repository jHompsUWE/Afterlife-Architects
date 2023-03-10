#include "pch.h"
#include "GameOver.h"
#include "AStarPathfinding.h"

//TODO::REMOVE THIS
#include <random>

#include "MapAssembler.h"
#include "PlaneAssembler.h"

GameOver::GameOver()
= default;

GameOver::~GameOver()
= default;

bool GameOver::init()
{
    //Test pathfinding ------------------------------------
    //THIS SHOULD NOT BE HERE AND ITS JUST A DEMONSTRATION OF PATHFINDING

    

    // //To the test the pathfinding abilities, generates 150 non-pathfindalbe random points
    // for (int i = 0; i < 150; ++i)
    // {
    //     int x = rand() % map_x;
    //     int y = rand() % map_y;
    //
    //     //higher cost than cost value specified in construct node sheet to have an obstacle
    //     cost_map[x][y] = 10;
    //
    //     //Draws a red tile over each non-pathfindable tile
    //     delete on_screen_tiles[x * map_x + y];
    //     on_screen_tiles[x * map_x + y] = new ImageGO2D("Tile_Red", DataManager::GetD3DDevice());
    //     on_screen_tiles[x * map_x + y]->SetPos(Vector2(x * 25,y * 25) + offset);
    //     on_screen_tiles[x * map_x + y]->SetScale(Vector2(0.25f, 0.25f));
    // }

    //Instantiates pathfinding
    //AStarPathfinding pathfinding;
    //Construct node-sheet. THIS CAN BE DONE ONLY ONCE, unless the cost map changes
    //pathfinding.ConstructNodeSheet(cost_map, 5);

    //Start and end pathfinding points
    //std::pair<int, int> start = {0, 0};
    //std::pair<int, int> end = {24, 24};

    //Gets the path
    //const auto path= pathfinding.resolvePath(start, end);

    // //If it is nullptr the path is unvalid 
    // if(path != nullptr)
    // {
    //     //If it is valid change all the tiles of the path to purple 
    //     for (const auto& point : *path)
    //     {
    //         on_screen_tiles[point.first * map_x + point.second] = new ImageGO2D("Tile_Purple", DataManager::GetD3DDevice());
    //         on_screen_tiles[point.first * map_x + point.second]->SetPos(Vector2(point.first * 25,point.second * 25) + offset);
    //         on_screen_tiles[point.first * map_x + point.second]->SetScale(Vector2(0.25f, 0.25f));
    //     }
    // }
    // else
    // {
    //     std::cout << "pathfinding is not possible in this current map iteration" << std::endl;
    // }

    //Map gen test iteration

    // Generate Perlin noise at sample points
    // for (float y = 0; y < 10; y += 0.1)
    // {
    //     for (float x = 0; x < 10; x += 0.1)
    //     {
    //         float noise = 0;
    //         float amplitude = 1;
    //         float frequency = 1;
    //         float persistence = 0.5;
    //         float total_amplitude = 0;
    //
    //         for (int i = 0; i < 4; i++)
    //         {
    //             noise += amplitude * PerlinNoise::GenerateNoise(x * frequency, y * frequency);
    //             total_amplitude += amplitude;
    //             amplitude *= persistence;
    //             frequency *= 2;
    //         }
    //
    //         float result = noise / total_amplitude;
    //
    //         // Do something with noise value
    //
    //         //Makes a console representation of the noise
    //         char c = ' ';
    //         if (result > 0.8) c = '@';
    //         else if (result > 0.6) c = '#';
    //         else if (result > 0.4) c = 'x';
    //         else if (result > 0.2) c = '-';
    //         std::cout << c;
    //     }
    //     std::cout << std::endl;
    // }
    
    std::srand(std::time(nullptr));
    
    return true;
}

void GameOver::Update(GameData* game_data)
{
    for (auto& obj : on_screen_tiles)
    {
        obj->Tick(game_data);
    }
    
    if(game_data->keyboard_state.Enter )
    {
        if(pressed != true)
        {
            pressed = true;
            int seed = (std::rand() % 1000000) + 10000;
            regenPerlin(seed);
        }
    }
    else
    {
        pressed = false;
    }
}

void GameOver::ScaledUpdate(GameData* game_data, float& scaled_dt)
{
}

void GameOver::LateUpdate(GameData* game_data)
{
}

void GameOver::regenPerlin(int seed)
{
    for (auto tile : on_screen_tiles)
    {
        delete tile;
    }
    on_screen_tiles.clear();
    
    std::cout << "Generating" << std::endl;
    
    Vector2 offset {5,5};

    //This generates the position of the resurrect station, so calling it once and then
    //generating the planes will make them share the position
    PlaneAssembler::RefreshResSeed();

    //This will generate a std::vector of Vector3, where x and y are the tile coordinates and Y the tile type
    // 0 is void
    // 1 is rock
    // 2 is river
    // 3 is res station
    const auto noise_map_vec = PlaneAssembler::GeneratePlaneAsVector3();
    
    //PlaneAssembler::SetResSeed(567);
    //const auto noise_map_vec = PlaneAssembler::GeneratePlaneAsVector3(567);

    for (const auto& element : noise_map_vec)
    {
        int x = element.x;
        int y = element.y;
        int tile = element.z;
        
        if(tile == 0)
        {
            ImageGO2D* tile = new ImageGO2D("Tile_Void", DataManager::GetD3DDevice());
            tile->SetPos(Vector2(x * 5,y * 5) + offset);
            tile->SetScale(Vector2(0.05f, 0.05f));
            on_screen_tiles.push_back(tile);
        }
        else if(tile == 1)
        {
            ImageGO2D* tile = new ImageGO2D("Tile_Rock", DataManager::GetD3DDevice());
            tile->SetPos(Vector2(x * 5,y * 5) + offset);
            tile->SetScale(Vector2(0.05f, 0.05f));
            on_screen_tiles.push_back(tile);
        }
        else if(tile == 2)
        {
            ImageGO2D* tile = new ImageGO2D("Tile_Water", DataManager::GetD3DDevice());
            tile->SetPos(Vector2(x * 5,y * 5) + offset);
            tile->SetScale(Vector2(0.05f, 0.05f));
            on_screen_tiles.push_back(tile);
        }
        else
        {
            ImageGO2D* tile = new ImageGO2D("Tile_Purple", DataManager::GetD3DDevice());
            tile->SetPos(Vector2(x * 5,y * 5) + offset);
            tile->SetScale(Vector2(0.05f, 0.05f));
            on_screen_tiles.push_back(tile);
        }
    }

    std::cout << "Generated" << std::endl;

}

void GameOver::GetEvents(std::list<AfterlifeEvent>& event_list)
{
}

void GameOver::Render2D(DrawData2D* draw_data2D)
{
    for (auto& obj : on_screen_tiles)
    {
        obj->Draw(draw_data2D);
    }
}

void GameOver::Render3D(DrawData* draw_data)
{
}



