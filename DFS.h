//
// Created by mac on 23/03/17.
//

#ifndef PATHFINDING_DFS_H
#define PATHFINDING_DFS_H



#include "SearchTemplates/SearchType.h"
#include <tuple>
#include "SearchTemplates/SolutionResponse.h"
#include "Parser.h"

///Depth First Search
///Inherits basic traits from 'SearchType'
///Includes Problem & StateList(Node*'s)
class DFS : public SearchType {
public:

    // ------------------------------------
    //Properties inherited from 'SearchType.h'

    //Problem CurrentProblem;
    //std::vector<std::vector<Node*>> stateList;
    //std::vector<Node*> frontier;
    //std::vector<ActionType> Path;

    // ------------------------------------

    //Debuggin renderer
    void RenderCurrentMap(Node* currentPosition,  Problem problem);

    //Default constructor from Parent
    DFS(std::vector<std::vector<Node*>> states,
        Problem& problem) : SearchType(states, problem) {}
    //get child from node
    Node* GetChild(Node* node, ActionType action);

    //Find node in state
    Node* StateLookUp(Node* node, std::tuple<int,int> instruction);

    //check for empty frontier
    bool FrontierIsEmpty();

    //Get top of frontier queue
    //DFS = LIFO
    Node* PopFrontier();
    void PushFrontier(std::vector<Node*> newFrontier);
    void PushFrontier(Node* newFrontier);

    //Takes problem and can invoke its 'Goal Test'
    //Using its state root node and goals state
    //Returns true for if goal reached and returns solution path
    bool GoalTest(Problem& problem, Node* node);

    //Expand current node
    std::vector<Node*> ExpandNode(Node* currentNode, Problem problem);

    SolutionResponse& DepthSearch(Problem &problem, Node *nodeSearch);
    SolutionResponse& Search(Problem &problem, Node *nodeSearch);
    std::vector<ActionType> pathAction;
    bool IsInPath(Node* node);
};


#endif //PATHFINDING_DFS_H
