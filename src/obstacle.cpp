#include "obstacle.h"

bool Obstacle::CheckForCollision(int x, int y) {
   for(auto i = 0; i<obstacle_positions.size(); i++){
  
  // std::cout << head_cell.x << " " << head_cell.y << std::endl;
    if(obstacle_positions[i].x==x && obstacle_positions[i].y==y ){
      return true;
    }
  }
  return false;
  
}

void Obstacle::UpdatePositions(std::vector <SDL_Point> &obstacle_pos) {
  obstacle_positions = obstacle_pos;
}

std::vector <SDL_Point> Obstacle::GetObstaclePostions() const {
  return obstacle_positions;
}