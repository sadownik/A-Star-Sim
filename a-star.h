#ifndef ASTAR_H
#define ASTAR_H

#include<vector>
#include <algorithm>

class Node{
    public:
        std::vector<int> position;
        bool is_expanded; 
        int g_value;
        int h_value;
        int f_value;
        Node * previous_Node;
        std::vector <int> prev_Pos;

        Node(std::vector <int> pos,std::vector <int> &target, int g, std::vector <int> prev_node): position(pos), g_value(g), prev_Pos(prev_node){
            calc_heuristic(target);
            calc_fval();
        };

    private:

        void calc_heuristic(std::vector <int> &target){
        h_value = std::abs(target[0] - position[0]) + std::abs(target[1] - position[1]);
        }

        void calc_fval(){ f_value = h_value + g_value;}

};




class aStar {
    public:
        aStar(std::vector<int> startval, std::vector<int> endval, int kWidthElements, int kHeightElements);
        void run();
        
    private:
        std::vector <Node> _openList;
        std::vector <Node> _pathNodes;
        // checks all possible neighbors and adds them to the openlist 
        void expandNode(Node node,std::vector <std::vector <int>>& map, int g,std::vector<int> _endNode);
        
        void printCurrentMap(std::vector <std::vector <int>>& map);
        void constructWay();
        std::vector<int> _currentNode;
        std::vector<int> _endNode;
        std::vector <std::vector <int>> expanded_map;
        std::vector <std::vector <int>> way_map;

};  

#endif