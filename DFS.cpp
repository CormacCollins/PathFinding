//
// Created by mac on 23/03/17.
//

#include "DFS.h"

//recursively call DepthSearch
SolutionResponse DFS::Search(Problem& problem, Node* nodeSearch) {
    auto a = DepthSeach(problem, nodeSearch);
    return *a;
}

SolutionResponse* DFS::DepthSeach(Problem& problem, Node* nodeSearch){

    //Return list from each child expansion
    std::vector<Path> children;
    //Nodes we will retrieve from the children Pth return type
    std::vector<Node*> childrenNodes;
    //To be returned solution
    SolutionResponse* solution;

    //First node added to path (without action)
//    Path firstPath = Path();
//    firstPath.pathNode = nodeSearch;
//    exploredPath.push_back(firstPath);

    //Goal check
    if (GoalTest(problem, nodeSearch)){
        //trimmerPath = TrimPath(problem);
        SolutionResponse* s = new SolutionResponse(exploredPath, "success");
        return s;
    }

    RenderCurrentMap(nodeSearch, problem);
    //Push first children onto frontier
    children = ExpandNode(nodeSearch, problem);


    //If children then add them otherwise we will go and pop the frontier
    if(!children.empty()){

        //Extract Nodes form children path
        for(Path& p : children){
            childrenNodes.push_back(p.pathNode);
        }

        //Add path to frontier
        PushFrontier(childrenNodes);
    }

    while(!FrontierIsEmpty()) {
        //Get top of stack for DFS (LIFO)
        Node* currentNode = PopFrontier();
        //Add node-action pair to path - this setup works fine but clearly can be refactored to something better!
        PushPath(currentNode, GetAction(children, currentNode));

        //begin search again
        SolutionResponse* s =  DepthSeach(problem, currentNode);

        //New???
        //Remove from path if it wa sa failure
        if(s->responseOutcome == "failure"){
            PopPath();
        }

        return s;

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
    return problem.GoalState == node;
}



void DFS::PushPath(Node* node, ActionType journeyAction) {
    exploredPath.push_back(Path(node, journeyAction));
}

void DFS::PopPath() {
    exploredPath.pop_back();
}
