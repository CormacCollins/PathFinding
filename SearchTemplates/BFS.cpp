//
// Created by mac on 2/04/17.
//

#include "BFS.h"

//How to add to single path for only successful route

SolutionResponse BFS::BreadthFirstSearch(Problem& problem, Node* searchNode){

    //Return list from each child expansion
    std::vector<Path> children;
    //Nodes we will retrieve from the children Pth return type
    std::vector<Node*> childrenNodes;
    //To be returned solution
    SolutionResponse* solution;

    //Goal check
    if (GoalTest(problem, searchNode)){
        solution = new SolutionResponse(currentPath, "success");
        return *solution;
    }

    //Push first children onto frontier
    children = ExpandNode(searchNode, problem);

    if(children.empty()){
        PopPath();
        std::cerr << "Could not find solution - empty child";
        solution = new SolutionResponse("failed");
        return *solution;
    }

    //Extract Nodes form children path
    for(Path& p : children){
        childrenNodes.push_back(p.pathNode);
    }

    //Add path to frontier
    PushFrontier(childrenNodes);

    //Add to correct path
    PushPath(searchNode, GetAction(children, searchNode));

    RenderCurrentMap(searchNode, problem);
    BreadthFirstSearch(problem, PopFrontier());

};

Node* BFS::PopFrontier() {
    Node* removeNode = frontier[0];
    frontier.erase(frontier.begin());
    return removeNode;
}

//Multi-node push
void BFS::PushFrontier(std::vector<Node*> newFrontier) {
    //Add node/action pairs to frontier
    for(auto n : newFrontier){
        frontier.push_back(n);
    }
}

//Single node push
void BFS::PushFrontier(Node* newFrontier) {
    //Add node/action pairs to frontier
    frontier.push_back(newFrontier);
}

bool BFS::GoalTest(Problem& problem, Node* node) {
    return problem.GoalState == node;
}



void BFS::PushPath(Node* node, ActionType journeyAction) {
    currentPath.push_back(Path(node, journeyAction));
}

void BFS::PopPath() {
    currentPath.pop_back();
}