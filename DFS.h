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
#include "SimpleTimer.h"
#include <future>

///Depth First Search
///Inherits basic traits from 'SearchType'
///Includes Problem & StateList(Node*'s)
class DFS : public SearchType {
private:
    int iterations = 0;
    int const ITERATION_MAX = 10;
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
    Path* PopFrontier();

    void PushFrontier(std::vector<Path*> newFrontier);

    void PushFrontier(Path* newFrontier);

    //Takes problem and can invoke its 'Goal Test'
    //Using its state root node and goals state
    //Returns true for if goal reached and returns solution path
    bool GoalTest(Problem& problem, Node* node);

    SolutionResponse* DepthSeach(Problem& problem, Path* newPath);

    virtual SolutionResponse Search(Problem& problem, Node* nodeSearch) override;

    void PushPath(Path* path);

    void PopPath();

};


#endif //PATHFINDING_DFS_H
