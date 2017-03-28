//
// Created by mac on 18/03/17.
//

#ifndef PATHFINDING_NODE_H
#define PATHFINDING_NODE_H

#include <string>
#include <vector>
#include "Action.h"

//Node data type for search
class Node {
public:
    Node* _parent;
    std::vector<Node> _children;
    int _pathcost;
    int _depth;

    //Each node taken from root to this node
    Node* state[];
};


#endif //PATHFINDING_NODE_H
