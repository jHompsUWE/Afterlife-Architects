#include "pch.h"
#include "GameOver.h"
#include "AStarPathfinding.h"

GameOver::GameOver()
= default;

GameOver::~GameOver()
= default;

bool GameOver::init()
{
    //Test pathfinding ------------------------------------
    //THIS SHOULD NOT BE HERE AND ITS JUST A DEMONSTRATION OF PATHFINDING

    //Creates a cost map
    std::vector<std::vector<int>> cost_map;

    //How big is the map?
    int map_x = 25;
    int map_y = 25;

    //This is just the scaled resolution of each tile, so they don't get rendered overlapped
    Vector2 offset {25,25};
    
    //Initiates the cost vector, and sets by deafult all the cost tiles to 0
    for(int x = 0; x < map_x; x++)
    {
        cost_map.emplace_back(std::vector<int>());
        for(int y = 0; y < map_y; y++)
        {
            //deafult cost set to 0
            cost_map[x].emplace_back(0);

            //Creates a tile array 
            ImageGO2D* tile = new ImageGO2D("Tile_Green", DataManager::GetD3DDevice());
            tile->SetPos(Vector2(x * 25,y * 25) + offset);
            tile->SetScale(Vector2(0.25f, 0.25f));
            on_screen_tiles.push_back(tile);
        }
    }

    //To the test the pathfinding abilities, generates 150 non-pathfindalbe random points
    for (int i = 0; i < 150; ++i)
    {
        int x = rand() % map_x;
        int y = rand() % map_y;

        //higher cost than cost value specified in construct node sheet to have an obstacle
        cost_map[x][y] = 10;

        //Draws a red tile over each non-pathfindable tile
        delete on_screen_tiles[x * map_x + y];
        on_screen_tiles[x * map_x + y] = new ImageGO2D("Tile_Red", DataManager::GetD3DDevice());
        on_screen_tiles[x * map_x + y]->SetPos(Vector2(x * 25,y * 25) + offset);
        on_screen_tiles[x * map_x + y]->SetScale(Vector2(0.25f, 0.25f));
    }

    //Instantiates pathfinding
    AStarPathfinding pathfinding;
    //Construct node-sheet. THIS CAN BE DONE ONLY ONCE, unless the cost map changes
    pathfinding.ConstructNodeSheet(cost_map, 5);

    //Start and end pathfinding points
    std::pair<int, int> start = {0, 0};
    std::pair<int, int> end = {24, 24};

    //Gets the path
    const auto path= pathfinding.resolvePath(start, end);

    //If it is nullptr the path is unvalid 
    if(path != nullptr)
    {
        //If it is valid change all the tiles of the path to purple 
        for (const auto& point : *path)
        {
            on_screen_tiles[point.first * map_x + point.second] = new ImageGO2D("Tile_Purple", DataManager::GetD3DDevice());
            on_screen_tiles[point.first * map_x + point.second]->SetPos(Vector2(point.first * 25,point.second * 25) + offset);
            on_screen_tiles[point.first * map_x + point.second]->SetScale(Vector2(0.25f, 0.25f));
        }
    }
    else
    {
        std::cout << "pathfinding is not possible in this current map iteration" << std::endl;
    }
    
    return true;
}

void GameOver::Update(GameData* game_data)
{
    for (auto& obj : on_screen_tiles)
    {
        obj->Tick(game_data);
    }
}

void GameOver::ScaledUpdate(GameData* game_data, float& scaled_dt)
{
}

void GameOver::LateUpdate(GameData* game_data)
{
}

void GameOver::GetEvents(const AL::Event& al_event)
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
