//
// Created by mac on 1/04/17.
//

#ifndef PATHFINDING_PATH_H
#define PATHFINDING_PATH_H


#include "Node.h"

class Path {
public:
    Node* pathNode;
    ActionType pathAction;
    Path(Node* node, ActionType action);
    Path(Node* node);
    Path();
};


#endif //PATHFINDING_PATH_H
