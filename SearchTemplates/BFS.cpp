//
// Created by mac on 2/04/17.
//

#include "BFS.h"

SolutionResponse BFS::Search(Problem& problem, Node* nodeSearch) {
    SolutionResponse s = BreadthFirstSearch(problem, nodeSearch);

    //Show final path
    for(Path& p : currentPath){
        RenderCurrentMap(p.pathNode, problem);
    }
    return s;
}

SolutionResponse BFS::BreadthFirstSearch(Problem& problem, Node* searchNode){

    //Return list from each child expansion
    std::vector<Path> children;
    //Nodes we will retrieve from the children Pth return type
    std::vector<Node*> childrenNodes;
    //To be returned solution
    SolutionResponse* solution;
    //Goal check
    if (GoalTest(problem, searchNode)){
        TrimPath();
        solution = new SolutionResponse(currentPath, "success");
        return *solution;
    }

    //Expand first node and add to frontier
    children = ExpandNode(searchNode, problem);
    for(auto& a: children){
        if (GoalTest(problem, searchNode)){
            TrimPath();
            solution = new SolutionResponse(currentPath, "success");
            return *solution;
        }

        //Add to frontier and add to path storage
        PushFrontier(a.pathNode);
        PushPath(a.pathNode, GetAction(children, a.pathNode));
    }

    //Main do while loop
    do {
        Node* n = PopFrontier();
        children = ExpandNode(n, problem);
        for(auto& p : children){
            //Goal check
            if(GoalTest(problem, p.pathNode)){
                PushPath(p.pathNode, GetAction(children, p.pathNode));
                TrimPath();
                solution = new SolutionResponse(currentPath, "success");
                return *solution;
            }

            PushFrontier(p.pathNode);
            PushPath(p.pathNode, GetAction(children, p.pathNode));
            RenderCurrentMap(p.pathNode, problem);
        }
    } while(!FrontierIsEmpty());

    std::cerr << frontier.size() << std::endl;
    //if children empty
    PopPath();
    std::cerr << "Could not find solution - empty child";
    solution = new SolutionResponse("failure");
    return *solution;
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

void BFS::TrimPath() {
    std::vector<Path> trimmedPath;


    //Loop through current path backwards - we want to work backwards from the goal node that we have found
    //E.g. if
    while(!currentPath.empty()){

        //Get top of path stack (Goal) and follow parents back to start
        Path p = currentPath[currentPath.size()-1];
        trimmedPath.push_back(p);

        currentPath.erase(currentPath.end());

        //Looping backwards checking nodes against node we have followed with action
        //Remove nodes that don't match the correct route
        while(currentPath[currentPath.size()-1].pathNode != p.pathNode->_parent){
            //remove from current path (trim)
            currentPath.erase(currentPath.end());
            if(currentPath.empty())
                break;
        }
    }

    //reverse paths from start to finish
    std::reverse(trimmedPath.begin(), trimmedPath.end());

    //Replace current path with the newly trimmed goal path
    currentPath = trimmedPath;
}








