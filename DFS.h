//
// Created by mac on 23/03/17.
//

#ifndef PATHFINDING_DFS_H
#define PATHFINDING_DFS_H

#include "SearchTemplates/SearchType.h"
#include <tuple>
#include "SearchTemplates/SolutionResponse.h"
#include "Parser.h"
#include "SearchTemplates/Path.h"

///Depth First Search
///Inherits basic traits from 'SearchType'
///Includes Problem & StateList(Node*'s)
class DFS : public SearchType {
public:

    // ------------------------------------
    // Inherits all generic path finding traits from 'SearchType'
    // Properties:
    //         currentProblem, stateList, frontier, exploredPath
    // Functions Includes:
    //         GetActionChild, StateLookUp, ExpandNode, RenderCurrentMap,
    //         GetAction, IsInCurrentPath
    // ------------------------------------

    //Default constructor from Parent
    DFS(std::vector<std::vector<Node*>> states,
        Problem& problem) : SearchType(states, problem) {}

    //Get top of frontier queue
    //DFS = LIFO
    Node* PopFrontier();

    void PushFrontier(std::vector<Node*> newFrontier);

    void PushFrontier(Node* newFrontier);

    //Takes problem and can invoke its 'Goal Test'
    //Using its state root node and goals state
    //Returns true for if goal reached and returns solution path
    bool GoalTest(Problem& problem, Node* node);

    SolutionResponse* DepthSeach(Problem& problem, Node* nodeSearch);

    virtual SolutionResponse Search(Problem& problem, Node* nodeSearch) override;

    void PushPath(Node* node, ActionType journeyAction);

    void PopPath();

};


#endif //PATHFINDING_DFS_H
