#pragma once

#include "TileNode.h"
#include <vector>

class AStarPathfinding
{
public:
    AStarPathfinding() = default;
    ~AStarPathfinding() = default;

    //pathfinding
    bool ConstructNodeSheet(std::vector<std::vector<int>> cost_map, const int cost_value);
    std::vector<std::pair<int,int>>* resolvePath(const std::pair<int, int> start,
                                                 const std::pair<int, int> end);
    
private:
    //Distance between two tiles
    static float findDistance(TileNode* tile_a, TileNode* tile_b);

    //Pathfinding data
    std::vector<std::pair<int, int>> path{};
    std::vector<TileNode> tiles{};
    //Saves map size
    int map_x {0};
    int map_y {0};
};

