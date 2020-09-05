#include "renderer.h"
#include <iostream>
#include <string>

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

// void Renderer::Render(Obstacle const obstacle, SDL_Point const &food) {
//   SDL_Rect block;
//   block.w = screen_width / grid_width;
//   block.h = screen_height / grid_height;

//   // Clear screen
//   SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
//   SDL_RenderClear(sdl_renderer);

//   // Render food
//   SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
//   block.x = food.x * block.w;
//   block.y = food.y * block.h;
//   SDL_RenderFillRect(sdl_renderer, &block);

//   // Render obstacle
//   SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0xCC, 0xFF);

//   for(auto &i: obstacle.GetObstaclePostions()){
//     block.x = i.x * block.w;
//     block.y = i.y * block.h;
//     SDL_RenderFillRect(sdl_renderer, &block);     
//   }


//   // Render snake's body
//   SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
//   for (SDL_Point const &point : snake.body) {
//     block.x = point.x * block.w;
//     block.y = point.y * block.h;
//     SDL_RenderFillRect(sdl_renderer, &block);
//   }

//   // Render snake's head
//   block.x = static_cast<int>(snake.head_x) * block.w;
//   block.y = static_cast<int>(snake.head_y) * block.h;
//   if (snake.alive) {
//     SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
//   } else {
//     SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
//   }
//   SDL_RenderFillRect(sdl_renderer, &block);


//   // Update Screen
//   SDL_RenderPresent(sdl_renderer);
// }


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

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}


void Renderer::RenderFinalBoard(std::vector <SDL_Point> const &obstacles, SDL_Point const &start, SDL_Point const &finish,std::vector <SDL_Point> const &_pathnodes) {
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