#pragma once

//Struct for a tilenode
struct TileNode
{
    //Stores information necessary of the node to be
    //handled in pathfinding
    bool is_obstacle = false;
    bool is_visited = false;
    float global_goal {0};
    float local_goal {0};
    int x {0};
    int y {0};

    //this is to be bumped up to 8 to have transversal connections,
    //Of course, then code inside the CPP files has to be changed accordingly
    TileNode* tile_neighbours[4];
    TileNode* parent = nullptr;
};

