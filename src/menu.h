#ifndef MENU_H
#define MENU_H

// #include "game.h"


#include <vector>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "enum_h.h"

class Menu {
    public:
        Menu(Renderer & renderer, Controller & controller):
        renderer(renderer), controller(controller) {}
        void RenderMenu();
        void Update();
        void Run();
        std::vector <SDL_Point> GetObstacles() const {return ObstacleList;};
        State GetRunningState() const {return state;}
        SDL_Point GetStartNode() const {return start;}
        SDL_Point GetEndNode() const {return finish;}



        
    private:
        void UpdateObstacles();
        void LimitStates();
        void GetMouseSelection();

        // User selectable fields, start, finish and obstacles
        // no selection means negative 1 values
        SDL_Point start {-1, -1};
        SDL_Point finish{-1, -1};
        std::vector <SDL_Point> ObstacleList;

        // menu selection stages
        State state = start_select;

        Renderer renderer;
        Controller controller;



};


#endif