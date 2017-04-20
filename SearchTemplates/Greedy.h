//
// Created by mac on 14/04/17.
//

#ifndef PATHFINDING_GREEDY_H
#define PATHFINDING_GREEDY_H


#include "SearchType.h"
#include "Astar.h"

class Greedy : public Astar {
    //Astar inheritence
public:
    Greedy(std::vector<std::vector<Node*>> states,
    Problem& problem) : Astar(states, problem) {
        deadEnds = std::vector<Node*>();
    }

    //override A* search (not sotring paths)
    SolutionResponse Search(Problem& problem, Node *nodeSearch) override;
private:
    //Just changin Astar heuristic is all that needs to differ for greedy best first
    Path* HeuristicFunction(std::vector<Path*>& path);
    std::vector<Node*> deadEnds;
    //Expand current node return path list
    std::vector<Path*> GreedyExpandNode(Node* currentNode, Problem& problem);
    Path* PopFrontier();

};


#endif //PATHFINDING_GREEDY_H
