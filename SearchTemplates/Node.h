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
    Node* Parent;
    int PathCost;
    int Depth;
    int goalCost;
};


#endif //PATHFINDING_NODE_H
