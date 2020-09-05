#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <vector>
#include "SDL.h"
#include "enum_h.h"

class Menu; 
class Square;

class Controller {
 public:
  Controller(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {}
  // void HandleInput(bool &running, Snake &snake) const;
  void HandleMenuInput(std::vector <SDL_Point> &obstacles, State &state);
  void HandleMenuInput(SDL_Point &node, State &state);
  void HandleSimInput();

 private:

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif