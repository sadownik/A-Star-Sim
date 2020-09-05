#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <vector>
#include "SDL.h"

class Obstacle {
  public:
    Obstacle(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height) {}
    
    // std::vector<std::vector <int>>obstacle_positions;
    //std::vector<SDL_Point> obstacle_positions;
    bool CheckForCollision(int x, int y);
    void UpdatePositions(std::vector <SDL_Point> &obstacle_pos);
    std::vector <SDL_Point> GetObstaclePostions() const;

  private:
    
    std::vector <SDL_Point> obstacle_positions;
    int grid_width;
    int grid_height;

};

#endif