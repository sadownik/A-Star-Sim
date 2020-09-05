#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <algorithm>
#include "renderer.h"
#include "controller.h"
#include "SDL.h"
// #include "enum_h.h"

enum node_type {empty, start, end_pos, obstacle, expanded, way};


class Node{
    public:
        SDL_Point position;
        bool is_expanded; 
        int g_value;
        int h_value;
        int f_value;
        // Node * previous_Node;
        SDL_Point  prev_Pos;

        Node(const SDL_Point &pos,const SDL_Point &target, int g, SDL_Point  prev_node): position(pos), g_value(g), prev_Pos(prev_node){
            calc_heuristic(target);
            calc_fval();
        };
        

    private:
        // calculates manhattan distance to target (finish)
        void calc_heuristic(SDL_Point const &target){
        h_value = std::abs(target.x - position.x) + std::abs(target.y - position.y);
        }

        void calc_fval(){ f_value = h_value + g_value;}

};

class Simulation {
    public:
    Simulation(Renderer & renderer, Controller & controller, const std::size_t grid_width, const std::size_t grid_height) 
        :
        grid_width(grid_width), 
        grid_height(grid_height),
        renderer(renderer),
        controller(controller)
         {

        // this creates a map for the expansion of the algorithm 
       	map.resize(grid_height);
	    for (int i = 0; i < grid_height; i++)
	    map[i].resize(grid_width, empty);
    }
    std::vector <SDL_Point> getPathNodes(){return _pathNodes;}
    
    void Run(const SDL_Point &start,const SDL_Point &end,const std::vector<SDL_Point> &obstaclelist);

    private:

        const std::size_t grid_width;
        const std::size_t grid_height;

        std::vector <Node> _openList;
        std::vector <Node> _ExpandedNodes;
        std::vector <SDL_Point> _pathNodes;

        Renderer renderer;
        Controller controller;


        std::vector<std::vector<node_type> > map;
        

        void AddObstacles(const std::vector<SDL_Point> &obstaclelist);
        void PrintCurrentMap(std::vector <std::vector <node_type>>& map);
        void ExpandNode(Node node, std::vector <std::vector <node_type>>& map, int g, SDL_Point _endNode);
        void ConstructWay();


};


#endif