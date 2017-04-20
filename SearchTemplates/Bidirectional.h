//
// Created by mac on 19/04/17.
//

#ifndef PATHFINDING_BIDIRECTIONAL_H
#define PATHFINDING_BIDIRECTIONAL_H


#include "SearchType.h"

class Bidirectional : public SearchType {
private:
    int iterations = 0;
    int const ITERATION_MAX = 100;
    float currentLowestCostFunction;
    float currentInvertedCostFunction;
    std::vector<Path*> frontierFromGoal;
    //Route taken is stored as we go
    std::vector<Path*> exploredPathFromGoal;
    std::vector<Path*> trimmedPathFromGoal;
    Path* endNodeStart;
    Path* endNodeGoal;

public:
    Bidirectional(std::vector<std::vector<Node*>> states,
    Problem& problem) : SearchType(states, problem) {}

    //Get top of frontier queue
    //DFS = LIFO
    Path* PopFrontier(std::vector<Path*>& chosenFrontier);

    void PushFrontier(std::vector<Path*> newFrontier, std::vector<Path*>& chosenFrontier);

    void PushFrontier(Path* newFrontier, std::vector<Path*>& chosenFrontier);

    //Main search function
    SolutionResponse Search(Problem& problem, Node* nodeSearch);
    SolutionResponse BidirectionalSearch(Problem& problem);


    //Heuristic function
    virtual Path* HeuristicFunction();
    Path* HeuristicFunctionFromGoal(Problem problem);

    void PopFrontierNodeSpecific(Path* node, std::vector<Path*>& chosenFrontier);

    std::vector<std::vector<std::string>>& GetStringPath() override;

    bool BidirectionalGoalTest();

    std::vector<Path*> CombinePaths( std::vector<Path*>& path1,  std::vector<Path*>& path2);

    bool GoalFrontierIsEmpty();

    void PushPathSpecific(Path* path, std::vector<Path*>& chosenPath);

    std::vector<Path*> CombineTrimmedPaths(std::vector<Path*>& path1, std::vector<Path*>& path2);

    std::vector<Path*> BidirectionalTrimPath(Problem& problem, std::vector<Path*> chosenPath, Path* startPath);

    std::vector<Path*> GetExploredPathFromGoal();

    //Expand current node return path list
    std::vector<Path*> BidirectionalExpandNode(Node* currentNode, Problem& problem, std::vector<Path*> pathCheck);

    bool IsInPath(Node *node, std::vector<Path*> pathCheck);

};


#endif //PATHFINDING_BIDIRECTIONAL_H
