 #include "menu.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "sdl_util.h"
#include <string>


void Menu::Update() {
    
    
    //running turns to false by user request (starting a new game)
    // running = controller.HandleMenuInput(ObstacleList, state);
    renderer.RenderCheckeredBoard(ObstacleList, start, finish);
}

void Menu::Run() {

    while(true) {
    LimitStates();
    GetMouseSelection();
    renderer.RenderCheckeredBoard(ObstacleList, start, finish);

    // start simulation - break out of infinite loop
    if(state == start_sim)
        break;
    }
}

// Using this to avoid invalid states
void Menu::LimitStates() {
    if (state < 0)
        exit(0);
    else if (state > start_sim)
        state = start_sim;
}

void Menu::GetMouseSelection() {
    
    switch(state){
        case start_select:
            controller.HandleMenuInput(start, state);
            break;

        case end_select:
            controller.HandleMenuInput(finish, state);
            break;

        case obstacle_select:
            controller.HandleMenuInput(ObstacleList, state);
            break;
    }
}



 
