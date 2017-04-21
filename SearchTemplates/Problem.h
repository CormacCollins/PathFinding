//
// Created by mac on 18/03/17.
//

#ifndef PATHFINDING_PROBLEM_H
#define PATHFINDING_PROBLEM_H

#include "Action.h"
#include "Node.h"

class Problem {
public:
    Node* InitialState;
    Node* GoalState;
    ActionType ProblemActions;
    int PathCost = 1;
};


#endif //PATHFINDING_PROBLEM_H
