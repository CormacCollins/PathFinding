//
// Created by mac on 20/04/17.
//

#ifndef PATHFINDING_MBASTAR_H
#define PATHFINDING_MBASTAR_H


#include "Astar.h"


class MBAstar : public Astar {
private:
    int iterations = 0;
    int const ITERATION_MAX = 100;
    int const MAX_PATHS = 25;
    Node* nodeRemove = NULL;
public:
    MBAstar(std::vector<std::vector<Node*>> states,
    Problem& problem) : Astar(states, problem) {}

    //Heuristic function
    Path* HeuristicFunction(Problem problem) override;

    void RemoveWorstPathFromExplored(Problem problem);

    SolutionResponse Search(Problem& problem, Node* nodeSearch) override;

    void RenderCurrentMap(Node* currentPosition,  Problem& problem) override;

    std::vector<Path*> MBATrimPath(Problem& problem, std::vector<Path*>);

    std::vector<Path*> GetParentPath(Node* currentNode, Problem& problem, std::vector<Path*> explored);
};


#endif //PATHFINDING_MBASTAR_H
