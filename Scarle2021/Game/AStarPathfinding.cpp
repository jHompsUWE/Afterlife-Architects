#include "pch.h"
#include "AStarPathfinding.h"
#include <list>

//pathfinding ------------------------------------------------------------------

bool AStarPathfinding::ConstructNodeSheet(std::vector<std::vector<int>> cost_map, const int cost_value)
{
  //gets the size of the cost map
  map_y = cost_map.size();
  map_x = cost_map.begin()->size();
  
  //inits the node vector by setting all the nodes to unexplored
  //Also uses the cost map to determine if a tile is an obstacle or not
  for (int x = 0; x < map_x; ++x)
  {
    for (int y = 0; y < map_y; ++y)
    {
      //If the cost of a tile is higher than the specified cost value,
      //That tile will be considered an obstacle
      bool obstacle = true;
      if(cost_map[x][y] <= cost_value)
      {
        obstacle = false;
      }

      //Inits all the nodes
      tiles.push_back(TileNode
        {
          obstacle,
          false,
          0,
          0,
          x,
          y,
          nullptr,
          nullptr,
          nullptr,
          nullptr,
          nullptr
        });
    }
  }

  //using the cost map size generates a node sheet
  //Each node will have a pointer to its neighbours
  for (int x = 0; x < map_x; ++x)
  {
    for (int y = 0; y < map_y; ++y)
    {
      //If statements checks if that tile is not out of boundaries
      //If it is, set it as nullptr in the neighbors array

      //To check diagonally the neighbours have to be specified here, but the
      //neighbour array has to be resized to 8

      //up node
      if(y > 0)
      {
        tiles[y * map_x + x].tile_neighbours[0] =
          &tiles[(y - 1) * map_x + (x + 0)];
      }
      else
      {
        tiles[y * map_x + x].tile_neighbours[0] = nullptr;
      }

      //below node
      if(y < map_x - 1)
      {
        tiles[y * map_x + x].tile_neighbours[1] =
          &tiles.at((y + 1) * map_x + (x + 0));
      }
      else
      {
        tiles[y * map_x + x].tile_neighbours[1] = nullptr;
      }

      //left node
      if(x > 0)
      {
        tiles[y * map_x + x].tile_neighbours[2] =
          &tiles[(y - 0) * map_x + (x - 1)];
      }
      else
      {
        tiles[y * map_x + x].tile_neighbours[2] = nullptr;
      }

      //right node
      if(x < map_x -  1)
      {
        tiles[y * map_x + x].tile_neighbours[3] =
          &tiles[(y - 0) * map_x + (x + 1)];
      }
      else
      {
        tiles[y * map_x + x].tile_neighbours[3] = nullptr;
      }
    }
  }
  return true;
}

std::vector<std::pair<int,int>>* AStarPathfinding::resolvePath(
  const std::pair<int, int> start, const std::pair<int, int> end)
{
  //Locates start and end path in the node sheet 
  TileNode* tile_start = &tiles[start.second * map_x + start.first];
  TileNode* tile_end = &tiles[end.second * map_y + end.first];

  //Resets all the tile nodes for a new pathfind
  for (int x = 0; x < map_x; ++x)
  {
    for (int y = 0; y < map_y; ++y)
    {
      tiles[y * map_x + x].is_visited = false;
      tiles[y * map_x + x].global_goal = INFINITY;
      tiles[y * map_x + x].local_goal = INFINITY;
      tiles[y * map_x + x].parent = nullptr;
    }
  }

  //Setting up start node
  TileNode* tile_current = tile_start;
  tile_start->local_goal = 0.0f;
  tile_start->global_goal = findDistance(tile_start, tile_end);

  //list containing the tiles that yet have to be considered for pathfind
  std::list<TileNode*> not_tested_tiles;
  not_tested_tiles.push_back(tile_start);

  //until all the tiles have been tested or the destination has been reached
  //keep pathfinding
  while (!not_tested_tiles.empty() && tile_current != tile_end)
  {
    //Sorts the elements using their global goal
    not_tested_tiles.sort([](const TileNode* lhs, const TileNode* rhs)
                          { return lhs->global_goal < rhs->global_goal; } );

    //Pop all the visited tiles away
    while(!not_tested_tiles.empty() && not_tested_tiles.front()->is_visited)
    {
      not_tested_tiles.pop_front();
    }

    //List is empty? pathfinding is done!
    if(not_tested_tiles.empty())
    {
      break;
    }

    //Takes the current tile and sets it as visited
    tile_current = not_tested_tiles.front();
    tile_current->is_visited = true;

    //Itertes trough the parents of the current tile
    for(auto tile_neighbour : tile_current->tile_neighbours)
    {
      //Is it a valid neighbour?
      if(tile_neighbour != nullptr)
      {
        // If the parent has not been tested yet queue it for testing
        if (!tile_neighbour->is_visited && tile_neighbour->is_obstacle == 0)
        {
          not_tested_tiles.push_back(tile_neighbour);
        }

        // Finds the distance between current tile and the parent
        float possible_lower_goal =
          tile_current->local_goal + findDistance(tile_current, tile_neighbour);

        // Is the current tile closer to the target than any other tile that
        // has been looked into?
        if (possible_lower_goal < tile_neighbour->local_goal)
        {
          // Updates parent and goal
          tile_neighbour->parent     = tile_current;
          tile_neighbour->local_goal = possible_lower_goal;

          tile_neighbour->global_goal =
            tile_neighbour->local_goal + findDistance(tile_neighbour, tile_end);
        }
      }
    }
  }

  //If pathfinding was successful and a path has been found
  if (tile_end != nullptr)
  {
    //Start of the path
    TileNode * path_section = tile_end;
    path.clear();
    
    //Goes through the only left parent in each node to build the path
    //if its nullptr the path is finished
    while (path_section->parent != nullptr)
    {
      path.emplace_back(path_section->x, path_section->y);
      path_section = path_section->parent;
    }

    //Reverse the path as it is backwards
    //std::reverse(path.begin(), path.end());

    return &path;
  }
  
  return nullptr;
}

//Distance between two tiles with Pythagorean theorem
float AStarPathfinding::findDistance(TileNode* tile_a, TileNode* tile_b)
{
  return sqrtf((tile_a->x - tile_b->x)*(tile_a->x - tile_b->x) +
               (tile_a->y - tile_b->y)*(tile_a->y - tile_b->y));
}
