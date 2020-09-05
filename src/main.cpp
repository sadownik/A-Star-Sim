#include <iostream>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "menu.h"
#include "simulation.h"


  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{16};
  constexpr std::size_t kGridHeight{16};

int main() {
    // Obstacle obstacle(kGridWidth, kGridHeight);

    Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
    // Screen properties are given for controller as well for mouse input calculation.
    Controller controller(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
    // Creation of a Menu object for obstacle selection.
    Menu menu(renderer, controller);

    Simulation sim(renderer, controller, kGridWidth, kGridHeight);

    menu.Run();
    sim.Run(menu.GetStartNode(), menu.GetEndNode(), menu.GetObstacles());



    return 0;
}