//
// Created by mac on 2/04/17.
//

#ifndef PATHFINDING_BFS_H
#define PATHFINDING_BFS_H


#include "SearchType.h"

class BFS : public SearchType {
public:
    BFS(std::vector<std::vector<Node*>> states,
        Problem& problem) : SearchType(states, problem) {}

    //Get top of frontier queue
    //DFS = LIFO
    Node* PopFrontier();

    void PushFrontier(std::vector<Node*> newFrontier);

    void PushFrontier(Node* newFrontier);

    SolutionResponse BreadthFirstSearch(Problem& problem, Node* nodeSearch);

    //SolutionResponse Search(Problem& problem, Node* nodeSearch);


    void PopPath();

    SolutionResponse Search(Problem& problem, Node* nodeSearch) override;


};


#endif //PATHFINDING_BFS_H
