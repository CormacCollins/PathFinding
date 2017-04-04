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

    //TODO
    //Transition model function - given a state we need to return the next given state
    //e.g. check available position moves i.e. Left Right and have their corresponding return states given the state prior to the action
};


#endif //PATHFINDING_PROBLEM_H
