#include "simulation.h"
#include <iostream>
#include "SDL.h"
#include "sdl_util.h"

bool operator<(const Node &x, const Node &y) {
	if (x.f_value != y.f_value)
		return x.f_value < y.f_value;

	return x.f_value < y.f_value;
}

void Simulation::Run(const SDL_Point &start,const SDL_Point &end, const std::vector<SDL_Point> &obstaclelist) {

    AddObstacles(obstaclelist);

    int g = 0;
    Node _startNode(start,end,g, {0,0});
    _openList.push_back(_startNode); 

    while(_openList.size()>0){
    //   std::cout << "---open_list---"<<std::endl;
    //     for (auto i : _openList) 
    //         std::cout << "("<<i.position[0]<< "," <<i.position[1]<<")"<< i.g_value<<' '<<i.h_value<< " "; 
    //         std::cout << "prev_node"<<"("<<i.previous_Node->position[0]<< "," <<i.previous_Node->position[1]<<")"<< " "; 
    //         std::cout << "("<<i.position.x<< "," <<i.position.y <<") "<<"prev_node "<<"("<<i.prev_Pos.x<< "," <<i.prev_Pos.y<<")"<< " ";
    //     std::cout <<std::endl;
    //     std::cout << "---open_list end---"<<std::endl;

        // increase cost for every iteration
        g++;
        // push new nodes back on to _openlist 
        _ExpandedNodes.push_back(_openList[0]); 
        ExpandNode(_openList[0], map, g, end);
        
        
      
        // reverse the list and pop the last element(the element used for expanding neighbors)
        std::reverse(_openList.begin(), _openList.end());
        _openList.pop_back();

        //sort using f value with overloaded < operator
        std::sort(_openList.begin(), _openList.end());

        // PrintCurrentMap(map);

        if (_openList[0].position == end) {
            _ExpandedNodes.push_back(_openList[0]);
            break;
        }
            

    }
    ConstructWay(); 


    while(true){


        renderer.RenderFinalBoard(obstaclelist, start, end, _pathNodes);
        controller.HandleSimInput();
    }
}

void Simulation::PrintCurrentMap(std::vector <std::vector <node_type>>& map){

    for(auto i = 0; i<map.size();i++){
        for(auto p = 0; p< map[0].size(); p ++){
            std::cout << map[i][p] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Simulation::ConstructWay(){

    std::vector <std::vector <node_type>> exploredway_map = map;

    // std::cout <<_ExpandedNodes.back().position[0] <<" "<< _ExpandedNodes.back().position[1] <<std::endl;
    SDL_Point last_pos = _ExpandedNodes.back().position;

    for(auto i = _ExpandedNodes.size()-1; i>0;--i){

        if(_ExpandedNodes[i].position==last_pos){
            // std::cout <<_ExpandedNodes[i].position[0] <<" "<< _ExpandedNodes[i].position[1] <<std::endl;
            exploredway_map[_ExpandedNodes[i].position.y][_ExpandedNodes[i].position.x] = way;

            SDL_Point e {_ExpandedNodes[i].position.x,_ExpandedNodes[i].position.y};

            _pathNodes.push_back(e);
            last_pos = _ExpandedNodes[i].prev_Pos;
        }


    }
    PrintCurrentMap(exploredway_map);

    

}

// checks all possible neighbors and adds them to the openlist 
void Simulation::ExpandNode(Node node,  std::vector <std::vector <node_type>>& map, int g, SDL_Point _endNode){

    // set current position as expanded (discovered)
    map[node.position.y][node.position.x] = expanded;

    if((node.position.y > 0) && (map[node.position.y-1][node.position.x] == empty)){
        _openList.push_back(Node( {node.position.x, node.position.y - 1}, _endNode, g, node.position));
        // std::cout << "expanded up"<< std::endl;
    }

    // // expand downward              y-value plus 1 
    if((node.position.y < map.size()-1) && (map[node.position.y+1][node.position.x] == empty)){
        _openList.push_back(Node( {node.position.x, node.position.y + 1}, _endNode, g, node.position));
        // std::cout << "expanded down"<< std::endl;
    }

    // expand left                                      x-value minus 1 
    if((node.position.x > 0) && (map[node.position.y][node.position.x - 1] == empty)){
        _openList.push_back(Node( {node.position.x - 1, node.position.y}, _endNode, g, node.position));
        // std::cout << "expanded left"<< std::endl;
    }

    // expand right                                      x-value plus 1 
    if((node.position.x < map[0].size()-1) && (map[node.position.y][node.position.x + 1] == empty)){
        _openList.push_back(Node( {node.position.x + 1,node.position.y}, _endNode, g, node.position));
        // std::cout << "expanded right"<< std::endl;
    }

}

// this creates a map from the obstacle positions which also later shows expanded positions
void Simulation::AddObstacles(const std::vector<SDL_Point> &obstaclelist) {

    for(auto i : obstaclelist)
        map[i.y][i.x] = obstacle; 

}