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
    int iterations = 0;
    Problem CurrentProblem;
    std::vector<std::vector<Node*>> stateList;
    //Nodes and the accompanying action to reach them from parent
    std::vector<Path*> frontier;
    //Route taken is stored as we go
    std::vector<Path*> exploredPath;
    std::vector<Path*> trimmedPath;
    std::vector<std::vector<std::string>> stringPathVec = std::vector<std::vector<std::string>>();

public:
    //Default constructor
    SearchType() {};

    virtual std::vector<std::vector<std::string>>& GetStringPath();
    //Construct search with given state map and problem
    SearchType(std::vector<std::vector<Node*>> states, Problem& problem){
        stateList = states;
        CurrentProblem = problem;
        exploredPath = std::vector<Path*>();
    }

    //get child from a node via a given action
    Node* GetActionChild(Node *node, ActionType action);

    //Find node in state map
    Node* StateLookUp(Node* node, std::tuple<int,int> instruction);

    //Expand current node return path list
    virtual std::vector<Path*> ExpandNode(Node* currentNode, Problem& problem);

    //renderer
    virtual void RenderCurrentMap(Node* currentPosition,  Problem& problem);

    //To prevent loops when searching a given path
    bool IsInCurrentPath(Node *node);

    //Get Nodes from current path
    std::vector<Node*> getNodes();

    //Get actions available for current node
    ActionType GetAction(std::vector<Path*> path, Node* nodeLookUp);

    //Check for empty frontier
    bool FrontierIsEmpty();

    //Add to path storage
    void PushPath(Path* path);

    //Removes redundant nodes for list containing correct path / actions to goals
    virtual std::vector<Path*> TrimPath(Problem& problem, std::vector<Path*> chosenPath); //for some algo's with special trim needs

    //Takes problem and can invoke its 'Goal Test'
    //Using its state root node and goals state
    //Returns true for if goal reached and returns solution path
    bool GoalTest(Problem& problem, Node* node);

    Path& GetPathFromNode(std::vector<Path> path, Node* nodeLookUp );

    virtual SolutionResponse Search(Problem& problem, Node *nodeSearch);

    int PathsExplored();

    std::vector<Path*> GetTrimmedPath();

    std::vector<Path*> GetExploredPath();

    //Check if a path has already been taken
    bool HasBeenExplored(Node* searchNode);

    void Reset();

};




#endif //PATHFINDING_SEARCHTYPE_H
