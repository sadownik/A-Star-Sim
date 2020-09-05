#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "obstacle.h"


class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Obstacle const obstacle, SDL_Point const &food);
  void RenderCheckeredBoard(std::vector <SDL_Point> const &obstacles, SDL_Point const &start, SDL_Point const &finish);
  void RenderFinalBoard(std::vector <SDL_Point> const &obstacles, SDL_Point const &start, SDL_Point const &finish,std::vector <SDL_Point> const &_pathnodes);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif