#include "a-star.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_set>

bool operator<(const Node &x, const Node &y) {
	if (x.f_value != y.f_value)
		return x.f_value < y.f_value;

	return x.f_value < y.f_value;
}
// aStar constructor 
aStar::aStar(std::vector<int> startval, std::vector<int> endval, int kWidthElements, int kHeightElements){


    }

void aStar::run(){

    //     expanded_map = map;
    // way_map = map;
    // _endNode = endval;

    // int g = 0;
    // Node _startNode(startval,endval,g, {0,0});
    // _openList.push_back(_startNode); 
                                               
    // // expandNode(_pathNodes[0], map);     
    
    // while(_openList.size()>0){
    //   std::cout << "---open_list---"<<std::endl;
    //     for (auto i : _openList) 
    //         // std::cout << "("<<i.position[0]<< "," <<i.position[1]<<")"<< i.g_value<<' '<<i.h_value<< " "; 
    //         // std::cout << "prev_node"<<"("<<i.previous_Node->position[0]<< "," <<i.previous_Node->position[1]<<")"<< " "; 
    //         std::cout << "("<<i.position[0]<< "," <<i.position[1]<<") "<<"prev_node "<<"("<<i.prev_Pos[0]<< "," <<i.prev_Pos[1]<<")"<< " ";
    //     std::cout <<std::endl;
    //     std::cout << "---open_list end---"<<std::endl;

    //     // increase cost for every iteration
    //     g++;
    //     // push new nodes back on to _openlist 
    //     _pathNodes.push_back(_openList[0]); 
    //     expandNode(_openList[0], expanded_map, g,_endNode);
        
        
      
    //     // reverse the list and pop the last element(the element used for expanding neighbors)
    //     std::reverse(_openList.begin(), _openList.end());
    //     _openList.pop_back();
    //     //sort using f value with overloaded < operator
    //     std::sort(_openList.begin(), _openList.end());

    //     printCurrentMap(expanded_map);

    //     if (_openList[0].position == _endNode)
    //         break;

    // } 

    // aStar::constructWay();                                   

};

void aStar::printCurrentMap(std::vector <std::vector <int>>& map){

    for(auto i = 0; i<map.size();i++){
        for(auto p = 0; p< map[0].size(); p ++){
            std::cout << map[i][p] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


void aStar::constructWay(){

    std::vector <std::vector <int>> exploredway_map = way_map;

    std::cout <<_pathNodes.back().position[0] <<" "<< _pathNodes.back().position[1] <<std::endl;
    std::vector <int> last_pos = _pathNodes.back().position;
    for(auto i = _pathNodes.size()-1; i>0;--i){
        if(_pathNodes[i].position==last_pos){
            std::cout <<_pathNodes[i].position[0] <<" "<< _pathNodes[i].position[1] <<std::endl;
            exploredway_map[_pathNodes[i].position[0]][_pathNodes[i].position[1]] = 6;
            last_pos = _pathNodes[i].prev_Pos;
        }


    }
    printCurrentMap(exploredway_map);
    



}


// checks all possible neighbors and adds them to the openlist 
void aStar::expandNode(Node node, std::vector <std::vector <int>>& map, int g, std::vector<int> _endNode){

    expanded_map[node.position[0]][node.position[1]] = 1;

    if(node.position[0]>0 && !expanded_map[node.position[0]-1][node.position[1]]){
        _openList.push_back(Node( {node.position[0]-1,node.position[1]}, _endNode, g, node.position));
        // std::cout << "expanded up"<< std::endl;
    }

    // expand downward              y-value plus 1 
    if(node.position[0]<map.size()-1 && !expanded_map[node.position[0]+1][node.position[1]]){
        _openList.push_back(Node( {node.position[0]+1,node.position[1]}, _endNode, g, node.position));
        // std::cout << "expanded down"<< std::endl;
    }

    // expand left                                      x-value minus 1 
    if(node.position[1]>0 && !expanded_map[node.position[0]][node.position[1]-1]){
        _openList.push_back(Node( {node.position[0],node.position[1]-1}, _endNode, g, node.position));
        // std::cout << "expanded left"<< std::endl;
    }

    // expand right                                      x-value plus 1 
    if(node.position[1]<map[0].size()-1 && !expanded_map[node.position[0]][node.position[1]+1]){
        _openList.push_back(Node( {node.position[0],node.position[1]+1}, _endNode, g, node.position));
        // std::cout << "expanded right"<< std::endl;
    }

}
