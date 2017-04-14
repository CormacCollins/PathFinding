//
// Created by mac on 23/03/17.
//

#include "DFS.h"

//recursively call DepthSearch
SolutionResponse DFS::Search(Problem& problem, Node* nodeSearch) {
    //Depth search requires paths passed around
    Path* openingPath = new Path(nodeSearch);
    auto a = DepthSeach(problem, openingPath);
    return *a;
}

SolutionResponse* DFS::DepthSeach(Problem& problem, Path* newPath){

    //Return list from each child expansion
    std::vector<Path*> children;
    //Nodes we will retrieve from the children Pth return type
    std::vector<Node*> childrenNodes;
    //To be returned solution
    SolutionResponse* solution;

    //Add node to new path
    Path* currentPath = newPath;

    //First node added to path (without action)
//    Path firstPath = Path();
//    firstPath.pathNode = nodeSearch;
//    exploredPath.push_back(firstPath);

    //Goal check
    if (GoalTest(problem, currentPath->pathNode)){
        trimmerPath = TrimPath(problem);
        SolutionResponse* s = new SolutionResponse(trimmerPath, "success");
        return s;
    }

    RenderCurrentMap(currentPath->pathNode, problem);

    do{
        children = ExpandNode(currentPath->pathNode, problem);

        if(!children.empty()){
            //Add path to frontier
            PushFrontier(children);
        }

        //Get top of stack for DFS (LIFO)
        if(!FrontierIsEmpty()) {
            currentPath = PopFrontier();
            PushPath(currentPath);
        }


        //begin search again
        solution =  DepthSeach(problem, currentPath);

        //New???
        //Remove from path if it wa sa failure
        if(solution->responseOutcome == "failure"){
            // PopFrontier();
        }else
        {
            //success
            return solution;
        }
    } while(!FrontierIsEmpty());

    return solution;
};

//Multi-node push
void DFS::PushFrontier(std::vector<Path*> newFrontier) {
    //Add node/action pairs to frontier
    for(auto n : newFrontier){
        frontier.push_back(n);
    }
}

//Single node push
void DFS::PushFrontier(Path* newFrontier) {
    //Add node/action pairs to frontier
    frontier.push_back(newFrontier);
}

Path* DFS::PopFrontier() {
    Path* removeNode = frontier[frontier.size()-1];
    frontier.pop_back();
    return removeNode;
}

bool DFS::GoalTest(Problem& problem, Node* node) {
    return problem.GoalState == node;
}

void DFS::PushPath(Path* path) {
    exploredPath.push_back(path);
}

void DFS::PopPath() {
    exploredPath.pop_back();
}
