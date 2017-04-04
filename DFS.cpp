//
// Created by mac on 23/03/17.
//

#include "DFS.h"

//recursively call DepthSearch
SolutionResponse DFS::Search(Problem& problem, Node* nodeSearch) {
    return DepthSearch(problem, nodeSearch);
}

SolutionResponse DFS::DepthSearch(Problem& problem, Node* searchNode){

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

    RenderCurrentMap(searchNode, problem);
    //Push first children onto frontier
    children = ExpandNode(searchNode, problem);


    if(children.empty()){
        PopPath();
        std::cerr << "Could not find solution - empty child";
        solution = new SolutionResponse("failure");
        return *solution;
    }


    //Extract Nodes form children path
    for(Path& p : children){
        childrenNodes.push_back(p.pathNode);
    }

    //Add path to frontier
    PushFrontier(childrenNodes);

    while(!FrontierIsEmpty()) {
        //Get top of stack for DFS (LIFO)
        Node* currentNode = PopFrontier();
        //Add node-action pair to path - this setup works fine but clearly can be refactored to something better!
        PushPath(currentNode, GetAction(children, currentNode));

        //begin search again
        return DepthSearch(problem, currentNode);
    }
};

//Multi-node push
void DFS::PushFrontier(std::vector<Node*> newFrontier) {
    //Add node/action pairs to frontier
    for(auto n : newFrontier){
        frontier.push_back(n);
    }
}

//Single node push
void DFS::PushFrontier(Node* newFrontier) {
    //Add node/action pairs to frontier
    frontier.push_back(newFrontier);
}

Node* DFS::PopFrontier() {
    Node* removeNode = frontier[frontier.size()-1];
    frontier.pop_back();
    return removeNode;
}

bool DFS::GoalTest(Problem& problem, Node* node) {
    RenderCurrentMap(node, problem);
    return problem.GoalState == node;
}



void DFS::PushPath(Node* node, ActionType journeyAction) {
    currentPath.push_back(Path(node, journeyAction));
}

void DFS::PopPath() {
    currentPath.pop_back();
}