//
// Created by mac on 2/04/17.
//

#include "BFS.h"

SolutionResponse BFS::Search(Problem& problem, Node* nodeSearch) {
    SolutionResponse s = BreadthFirstSearch(problem, nodeSearch);
    return s;
}

SolutionResponse BFS::BreadthFirstSearch(Problem& problem, Node* searchNode){

    //Return list from each child expansion
    std::vector<Path> children;
    //Nodes we will retrieve from the children Pth return type
    std::vector<Node*> childrenNodes;
    //To be returned solution
    SolutionResponse* solution;

    //First node added to path (without action)
//    Path firstPath = Path();
//    firstPath.pathNode = searchNode;
//    exploredPath.push_back(firstPath);

    //Goal check
    if (GoalTest(problem, searchNode)){
        trimmerPath = TrimPath(problem);
        solution = new SolutionResponse(trimmerPath, "success");
        return *solution;
    }


    RenderCurrentMap(searchNode, problem);

    //Expand first node and add to frontier
    children = ExpandNode(searchNode, problem);
    for(auto& a: children){


        PushPath(a.pathNode, GetAction(children, a.pathNode));
        RenderCurrentMap(a.pathNode, problem);
        //Test before on frontier
        if (GoalTest(problem, a.pathNode)){
            trimmerPath = TrimPath(problem);
            solution = new SolutionResponse(trimmerPath, "success");
            return *solution;
        }

        //Add to frontier and add to path storage
        PushFrontier(a.pathNode);

    }

    //Main do while loop
    do {
        Node* n = PopFrontier();
        children = ExpandNode(n, problem);

        for(auto& p : children){

            PushPath(p.pathNode, GetAction(children, p.pathNode));
            RenderCurrentMap(p.pathNode, problem);

            //Goal check
            if(GoalTest(problem, p.pathNode)){
                PushPath(p.pathNode, GetAction(children, p.pathNode));
                trimmerPath = TrimPath(problem);
                solution = new SolutionResponse(trimmerPath, "success");
                return *solution;
            }

            PushFrontier(p.pathNode);
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



void BFS::PopPath() {
    exploredPath.pop_back();
}








