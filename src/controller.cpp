#include "controller.h"
#include <iostream>
#include "SDL.h"
#include <algorithm>
#include "sdl_util.h"


// This member function handles user input during the "menu" phase of \
the program. 
void Controller::HandleMenuInput(std::vector <SDL_Point> &obstacles, State &state) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {

        case SDLK_y:
          state = State(state+1);

          break;

        case SDLK_x:
          state = State(state-1);
          break;
      }
    }
    //If the mouse button is pressed the current location of the cursor is \
    searched within the obstacles vector. If it isn't found it is being added \
    else it is erased (unselecting the cell) providing only unique cells. 
    if (e.type == SDL_MOUSEBUTTONDOWN ) {

    SDL_Point val { e.motion.x/((long unsigned int)screen_width/grid_width), e.motion.y/((long unsigned int)screen_height/grid_height)};
    std::vector<SDL_Point>::iterator it;
    it = std::find(obstacles.begin(), obstacles.end(), val);

    if (it == obstacles.end() || obstacles.size() == 0 )
      obstacles.push_back(val);
  
    else
      obstacles.erase(it);
  
    }
  }  
}

// overloaded member function for a single point
void Controller::HandleMenuInput(SDL_Point &node, State &state) {

  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {

        case SDLK_y:
          state = State(state+1);

          break;

        case SDLK_x:
          state = State(state-1);
          break;
      }
    }

    if (e.type == SDL_MOUSEBUTTONDOWN ) {
      SDL_Point val { e.motion.x/((long unsigned int)screen_width/grid_width), e.motion.y/((long unsigned int)screen_height/grid_height)};
      if (node != val)
        node = val;
      else
        // deselect the node if clicked again
        node = {-1,-1};

    }
  }
}


void Controller::HandleSimInput() {

  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {

        case SDLK_x:
          exit(0);
          break;
      }
    }

  }
}
