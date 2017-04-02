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
#include "Path.h"
#include <vector>
#include <algorithm>
#include <search.h>
#include "Action.h"
#include <iostream>
#include <sstream>
#include "SolutionResponse.h"

//Parent class for All search algorithms

class SearchType {
protected:
    Problem CurrentProblem;
    std::vector<std::vector<Node*>> stateList;
    //Nodes and the accompanying action to reach them from parent
    std::vector<Node*> frontier;
    //Route taken is stored as we go
    std::vector<Path> currentPath;

public:
    //Construct search with given state map and problem
    SearchType(std::vector<std::vector<Node*>> states, Problem& problem){
        stateList = states;
        CurrentProblem = problem;
    }

    //get child from a node via a given action
    Node* GetActionChild(Node *node, ActionType action);

    //Find node in state map
    Node* StateLookUp(Node* node, std::tuple<int,int> instruction);

    //Expand current node return path list
    std::vector<Path> ExpandNode(Node* currentNode, Problem problem);

    //renderer
    void RenderCurrentMap(Node* currentPosition,  Problem& problem);

    //To prevent loops when searching a given path
    bool IsInCurrentPath(Node* node);

    //Get Nodes from current path
    std::vector<Node*> getNodes();

    //Get actions available for current node
    ActionType GetAction(std::vector<Path> path, Node* nodeLookUp);

    //Check for empty frontier
    bool FrontierIsEmpty();
};


#endif //PATHFINDING_SEARCHTYPE_H
