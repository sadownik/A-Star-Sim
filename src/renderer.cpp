#include "renderer.h"
#include <iostream>


Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::RenderCheckeredBoard(std::vector <SDL_Point> const &obstacles, SDL_Point const &start, SDL_Point const &finish) {
  SDL_Rect block;

  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  std::string title{ "Select desired obstacles by clicking" };
  SDL_SetWindowTitle(sdl_window, title.c_str());

  // Render all squares in 2 different colors
  for(auto i = 0; i < grid_height; i ++){
    for(auto j = 0; j < grid_width; j ++){
        if ((i+j)%2) {
          SDL_SetRenderDrawColor(sdl_renderer, 0xd3, 0xd3, 0xd3, 0xFF);
        } else {
          SDL_SetRenderDrawColor(sdl_renderer, 0x69, 0x69, 0x69, 0xFF);
        }
        block.x = j * block.w;
        block.y = i * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);

    }
  }
  // render all obstacles from the obstacle list in an orange color
  for(auto &i: obstacles) {
 
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x8C, 0x00, 0xFF);
    block.x = i.x * block.w;
    block.y = i.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);    
  }

  // render start
  if(start.x >= 0 && start.y >= 0) {
    SDL_SetRenderDrawColor(sdl_renderer, 0xd6, 0x0d, 0x0d, 0xFF);
    block.x = start.x * block.w;
    block.y = start.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);    
  }

    // render finish
  if(finish.x >= 0 && finish.y >= 0) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x0d, 0xd6, 0x21, 0xFF);
    block.x = finish.x * block.w;
    block.y = finish.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);    
  }



  SDL_RenderPresent(sdl_renderer);

 }


void Renderer::RenderFinalBoard(std::vector <SDL_Point> const &obstacles, SDL_Point const &start, SDL_Point const &finish,std::vector <SDL_Point> const &_pathnodes) {
  SDL_Rect block;

  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  std::string title{ "Final Result" };
  SDL_SetWindowTitle(sdl_window, title.c_str());

  // Render all squares in 2 different colors
  for(auto i = 0; i < grid_height; i ++){
    for(auto j = 0; j < grid_width; j ++){
        if ((i+j)%2) {
          SDL_SetRenderDrawColor(sdl_renderer, 0xd3, 0xd3, 0xd3, 0xFF);
        } else {
          SDL_SetRenderDrawColor(sdl_renderer, 0x69, 0x69, 0x69, 0xFF);
        }
        block.x = j * block.w;
        block.y = i * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);

    }
  }
  // render all obstacles from the obstacle list in an orange color
  for(auto &i: obstacles) {
 
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x8C, 0x00, 0xFF);
    block.x = i.x * block.w;
    block.y = i.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);    
  }

    // render all obstacles from the obstacle list in an purple color
  for(auto &i: _pathnodes) {
 
    SDL_SetRenderDrawColor(sdl_renderer, 0x80, 0x00, 0x80, 0xFF);
    block.x = i.x * block.w;
    block.y = i.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);    
  }

  // render start
  if(start.x >= 0 && start.y >= 0) {
    SDL_SetRenderDrawColor(sdl_renderer, 0xd6, 0x0d, 0x0d, 0xFF);
    block.x = start.x * block.w;
    block.y = start.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);    
  }

    // render finish
  if(finish.x >= 0 && finish.y >= 0) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x0d, 0xd6, 0x21, 0xFF);
    block.x = finish.x * block.w;
    block.y = finish.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);    
  }



  SDL_RenderPresent(sdl_renderer);

 }