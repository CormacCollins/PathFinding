//
// Created by mac on 2/04/17.
//

#ifndef PATHFINDING_BFS_H
#define PATHFINDING_BFS_H


#include "SearchType.h"

class BFS : SearchType {
public:
    BFS(std::vector<std::vector<Node*>> states,
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

    SolutionResponse BreadthFirstSearch(Problem& problem, Node* nodeSearch);

    //SolutionResponse Search(Problem& problem, Node* nodeSearch);

    void PushPath(Node* node, ActionType journeyAction);

    void PopPath();

    SolutionResponse Search(Problem& problem, Node* nodeSearch);

    //Removes redundant nodes for list containing correct path / actions to goals
    void TrimPath();
};


#endif //PATHFINDING_BFS_H
