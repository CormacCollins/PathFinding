//
// Created by mac on 8/04/17.
//

#ifndef PATHFINDING_ASTAR_H
#define PATHFINDING_ASTAR_H


#include "SearchType.h"

//f (n) = g(n) + h(n)

class Astar : public SearchType {
private:
    float currentLowestCostFunction;
    Node* lowestCostNode;

public:

    Astar(std::vector<std::vector<Node*>> states,
    Problem& problem) : SearchType(states, problem) {}

    //Get top of frontier queue
    //DFS = LIFO
    Path* PopFrontier();

    void PushFrontier(std::vector<Path*> newFrontier);

    void PushFrontier(Path* newFrontier);

    //Main search function - (recursive)
    SolutionResponse Search(Problem& problem, Node *nodeSearch);

    //Heuristic function
    Node* HeuristicFunction();

    void PopFrontierNodeSpecific(Path* node);

    std::vector<std::vector<std::string>>& GetStringPath() override;

};


#endif //PATHFINDING_ASTAR_H
