//
// Created by mac on 8/04/17.
//

#ifndef PATHFINDING_ASTAR_H
#define PATHFINDING_ASTAR_H


#include "SearchType.h"

//f (n) = g(n) + h(n)

class Astar : SearchType {
private:
    int currentLowestCostFunction;
    Node* lowestCostNode;

public:

    Astar(std::vector<std::vector<Node*>> states,
    Problem& problem) : SearchType(states, problem) {}

    //Get top of frontier queue
    //DFS = LIFO
    Node* PopFrontier();

    void PushFrontier(std::vector<Node*> newFrontier);

    void PushFrontier(Node* newFrontier);

    //Main search function - (recursive)
    SolutionResponse Search(Problem& problem, Node *nodeSearch);

    //Heuristic function
    Node* HeuristicFunction();

};


#endif //PATHFINDING_ASTAR_H
