#pragma once

#include <deque>
#include <random>
#include <vector>

#include "AStarPathfinding.h"
#include "MapAssembler.h"
#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

class PlaneAssembler
{
public:
    //Delete copy and assignment const/operator
    PlaneAssembler(const PlaneAssembler&) = delete;
    PlaneAssembler& operator=(const PlaneAssembler&) = delete;

    static PlaneAssembler& Get()
    {
        static PlaneAssembler instance;
        return instance;
    }

    static void RefreshResSeedSt()
    {
        Get().RefreshResSeed();
    }
    
    static std::vector<std::vector<int>>* GenerateTerrainSt(int seed)
    {
        return Get().GenerateTerrain(seed);
    }
    
private:
    //Priv constructor 
    PlaneAssembler() = default;

    void RefreshResSeed()
    {
        std::srand(std::time(nullptr));
        res_seed = rand() & 100000;
    }
    
    std::vector<Vector3> AssemblePlaneAsVectors()
    {
        

        std::srand(std::time(nullptr));
        std::mt19937_64 prng((std::rand() % 1000000) + 10000);
        
        return {};
    }

    std::vector<std::vector<int>>* GenerateTerrain(int seed)
    {
        //defaults the map as correctly generated
        success = true;
        
        //inits Pseudo Random Num Gen
        std::mt19937_64 prng(seed);

        //Assembles the noise map
        auto noise_map = MapAssembler::GenerateNoiseMap(map_width, map_height, prng, octaves, map_scale,
                                                                        persistance, lacunarity, offset);

        //Terrain map initialized to 0s
        terrain_map.clear();
        terrain_map.reserve(map_height);
        for(int y = 0; y < map_height; y++)
        {
            terrain_map.emplace_back(std::vector<int>());
            terrain_map.back().reserve(map_width);

            for(int x = 0; x < map_width; x++)
            {
                terrain_map.back().emplace_back(0);
            }
        }

        //inits pathfinding
        AStarPathfinding pathfinding;
        //Creates an area equal to the map size for pathfinding to take place 
        pathfinding.ConstructNodeSheet(terrain_map, 5);

        auto river_path = GenerateRivers(pathfinding, prng, 2);

        for (const Vector2& node : river_path)
        {
            int x_node = static_cast<int>(node.x);
            int y_node = static_cast<int>(node.y);

            //River nodes get added to the terrain map
            terrain_map[x_node][y_node] = 2;

            //Cheeky way to buff up rivers, this code is ran once at start so no worry for performance
            //Buffs up the rivers if they are not next to a border 
            if (x_node > 1 && x_node < map_width - 2)
            {
                terrain_map[x_node - 1][y_node] = 2;
                terrain_map[x_node + 1][y_node] = 2;
                terrain_map[x_node - 2][y_node] = 2;
                terrain_map[x_node + 2][y_node] = 2;
            }
            if (y_node > 1 && y_node < map_height - 2)
            {
                terrain_map[x_node][y_node - 1] = 2;
                terrain_map[x_node][y_node + 1] = 2;
                terrain_map[x_node][y_node - 2] = 2;
                terrain_map[x_node][y_node + 2] = 2;
            }
        }

        //Adds a river border to the generated map
        for (int x = 0; x < map_width; x++)
        {
            terrain_map[x][0] = 2;
            terrain_map[x][map_height - 1] = 2;
        }
        for (int y = 0; y < map_height; y++)
        {
            terrain_map[0][y] = 2;
            terrain_map[map_width - 1][y] = 2;
        }

        prng = std::mt19937_64(res_seed);
        std::uniform_int_distribution<int> range_x(10, map_width - 10);
        std::uniform_int_distribution<int> range_y(10, map_height - 10);

        //genrates 4 random points for the resurrect stations
        for (int i = 0; i < resurrect_station; i++)
        {
            int value_x = range_x(prng);
            int value_y = range_y(prng);

            for (int y = 1; y < 4; y++)
            {
                for (int x = 1; x < 4; x++)
                {
                    terrain_map[value_x + x][value_y + y] = 3;
                }
            }
        }

        if(success)
        {
            //0 is void
            //1 is rock
            //2 is river
            //3 is res station
            return &terrain_map;
        }

        //Map not good all bad *explosion sound*
        return nullptr;
    }

    std::deque<Vector2> GenerateRivers(AStarPathfinding& pathfinding, std::mt19937_64& prng, int n_of_rivers)
    {
        //River path deque and list of point that compose river 
        std::deque<Vector2> river_path;
        std::vector<Vector2> all_river_points;

        for (int j = 0; j < n_of_rivers; ++j)
        {
            //Collection of points where rivers will generate from, first one is created randomly starting in the Y axis
            std::vector<Vector2> river_points(river_nodes);

            std::uniform_int_distribution<int> range(0, map_height - 15);
            river_points[0] = Vector2(0, range(prng));
            int river_points_n = river_points.size();

            int section = map_width / (river_points_n - 2);
            int value_x = 0;
            int value_y = 0;

            //Creates all the river points with a slight offset to each other
            for (int i = 1; i < river_points_n - 1; i++)
            {
                value_x = section * i;
                std::uniform_int_distribution<int> point_range((int)river_points[i - 1].y - river_offset,
                                                               (int)river_points[i - 1].y + river_offset);
                
                do
                {
                    value_y = point_range(prng);
                } 
                while (value_y < 0 && value_y > map_height);

                river_points[i] = Vector2(value_x, value_y);
            }

            
            //last point has to be manually set, will be at opposite side of the map
            value_x = map_width - 1;

            range.param(std::uniform_int_distribution<int>::param_type((int)river_points[river_points_n - 2].y - river_offset, 
                        (int)river_points[river_points_n - 2].y + river_offset));
            value_y = range(prng);
            river_points[river_points_n - 1] = Vector2(value_x, value_y);

            //50% chance of a river being mirrored
            range.param(std::uniform_int_distribution<int>::param_type(0, 20));
            
            if (range(prng) > 10)
            {
                for (int i = 0; i < river_points.size(); i++)
                {
                    auto& point = river_points[i];
                    river_points[i] = Vector2(point.y, point.x);
                }
            }

            //Connects the river points to create a river
            for (int i = 0; i < river_points_n - 1; i++)
            {
                const std::pair<int, int> start = {river_points[i].x, river_points[i].y};
                const std::pair<int, int> end = {river_points[i+1].x, river_points[i+1].y};
                
                auto temp_path = pathfinding.resolvePath(start, end);

                //if path is not valid fails the map generation
                if (temp_path == nullptr)
                {
                    success = false;
                    break;
                }

                //if it is valid, adds rivers nodes to final river path
                for(auto& node : *temp_path)
                {
                    river_path.push_back(Vector2{(float)node.first, (float)node.second});
                }
            }

            //Adds points found inside all river points 
            for (auto& point : river_points)
            {
                all_river_points.push_back(point);
            }
        }
        
        //Here i'm moving the side-river logic used in the rush alpha to see if they can maybe be implemented by the end
        //Toggle to have them or on off
        if (side_rivers_toggle)
        {
            //Here generates littler rivers starting from the main one to the side of the map
            int used_values = 0;
            int start_river_point = 0;
            int all_river_points_n = all_river_points.size();

            for (int i = 0; i < side_rivers; i++)
            {
                std::uniform_int_distribution<int> range(0, 2);
                int side = range(prng);
                
                do
                {
                    range.param(std::uniform_int_distribution<int>::param_type(1, all_river_points_n - 1));
                    start_river_point = range(prng);
                } 
                while (used_values == start_river_point); 
                
                used_values = start_river_point;

                const std::pair<int,int> side_river_start = {all_river_points[start_river_point].x, all_river_points[start_river_point].y};
                const std::pair<int,int> side_river_end = {all_river_points[start_river_point].x, (map_height - 1) * side};
            
                auto temp_path = pathfinding.resolvePath(side_river_start, side_river_end);

                //if path is not valid fails the map generation
                if (temp_path == nullptr)
                {
                    success = false;
                    break;
                }

                //if it is valid, adds rivers nodes to final river path
                for(auto& node : *temp_path)
                {
                    river_path.push_back(Vector2{(float)node.first, (float)node.second});
                }
            }
        }
        
        return river_path;
    }

    //Map gen worked correctly?
    bool success = false;

    //Generated map
    std::vector<std::vector<int>> terrain_map{};
    
    //Map size
    int map_width = 100;
    int map_height = 100;

    //Number of octaves of iteration of the noise, more is more smooth, do not use more than 10.
    int octaves = 5;

    //Scale of generated map
    float map_scale = 0.5f;
    //noise "filter" higher value means more is getting cut off
    float map_filter = 0.8f;
    //Map intensity
    float persistance = 0.65f;
    //Map lacunarity
    float lacunarity = 4.0f;
    //Octaves offset
    Vector2 offset = {0,0};

    //River nodes
    int river_nodes = 11;
    //Offset between rivers
    int river_offset = 3;

    //Secondary rivers
    bool side_rivers_toggle = false;
    int side_rivers = 2;
    int side_river_nodes = 5;

    //Res data
    int resurrect_station = 4;
    int res_seed = 0;
};
