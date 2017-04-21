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

// -------------------------------------- //
// Parent class for All search algorithms
// -------------------------------------- //

class SearchType {
protected:

    //Used for time out feature
    int iterations = 0;

    //Search problem
    Problem CurrentProblem;

    //NxM state of constructed Node*
    std::vector<std::vector<Node*>> stateList;

    //Nodes and the accompanying action to reach them from parent
    std::vector<Path*> frontier;

    //Route taken is stored as we go
    std::vector<Path*> exploredPath;

    //Used after search as output containing the 'best' path with directions
    std::vector<Path*> trimmedPath;

    //Stored string representations of state - original visualizing now stored for interpretation by GUI
    std::vector<std::vector<std::string>> stringPathVec = std::vector<std::vector<std::string>>();

public:

    SearchType() {};


    //Construct search with given state map and problem
    SearchType(std::vector<std::vector<Node*>> states, Problem& problem){
        stateList = states;
        CurrentProblem = problem;
        exploredPath = std::vector<Path*>();
    }

    //get child from a node via a given action
    Node* GetActionChild(Node *node, ActionType action);

    //Find node in state map - takes instruction that is determined by graph 'direction' i.e. LEFT
    Node* StateLookUp(Node* node, std::tuple<int,int> instruction);

    //Gets children from a node (returns both the child Node and it's accompanying Direction
    virtual std::vector<Path*> ExpandNode(Node* currentNode, Problem& problem);

    //To prevent loops when searching a given path - checks our explored Path for a given node
    bool IsInCurrentPath(Node *node);

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

    //Generic Search to be overriden by all children
    virtual SolutionResponse Search(Problem& problem, Node *nodeSearch);

    //Return the trimmedPath
    std::vector<Path*> GetTrimmedPath();

    //Return the fully explored path
    std::vector<Path*> GetExploredPath();

    //Reset class for new state search
    void Reset();

    // -------- GUI RELATED FUNCTIONS --------- //

    //Access to states for GUI
    virtual std::vector<std::vector<std::string>>& GetStringPath();

    //Saves string representation of map for GUI
    virtual void RenderCurrentMap(Node* currentPosition,  Problem& problem);

};




#endif //PATHFINDING_SEARCHTYPE_H
