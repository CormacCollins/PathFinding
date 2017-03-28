//
// Created by mac on 25/03/17.
//

#ifndef PATHFINDING_SEARCHTYPE_H
#define PATHFINDING_SEARCHTYPE_H

#include "Node.h"
#include "Problem.h"
#include <vector>
#include <tuple>
#include "../Parser.h"

class SearchType {
private:
    std::vector<Node> _frontier;
public:
    //Construct search with given problem
    SearchType(std::vector<std::vector<Node*>> states, Problem& problem){
        stateList = states;
        CurrentProblem = problem;
    }

    Problem CurrentProblem;
    std::vector<std::vector<Node*>> stateList;
    //Nodes and the accompanying action to reach them from parent
    std::vector<Node*> frontier;

    //Route taken is stored as we go
    std::vector<Node*> Path;


};


#endif //PATHFINDING_SEARCHTYPE_H
