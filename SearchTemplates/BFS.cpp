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
    std::vector<Path*> children;
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
    for(auto* a: children){


        PushPath(a);
        RenderCurrentMap(a->pathNode, problem);
        //Test before on frontier
        if (GoalTest(problem, a->pathNode)){
            trimmerPath = TrimPath(problem);
            solution = new SolutionResponse(trimmerPath, "success");
            return *solution;
        }

        //Add to frontier and add to path storage
        PushFrontier(a);

    }

    //Main do while loop
    do {
        Path* p = PopFrontier();
        children = ExpandNode(p->pathNode, problem);

        for(auto& p : children){

            PushPath(p);
            RenderCurrentMap(p->pathNode, problem);

            //Goal check
            if(GoalTest(problem, p->pathNode)){
                PushPath(p);
                trimmerPath = TrimPath(problem);
                solution = new SolutionResponse(trimmerPath, "success");
                return *solution;
            }

            PushFrontier(p);
        }

    } while(!FrontierIsEmpty());

    std::cerr << frontier.size() << std::endl;
    //if children empty
    PopPath();
    std::cerr << "Could not find solution - empty child";
    solution = new SolutionResponse("failure");
    return *solution;
};

Path* BFS::PopFrontier() {
    Path* removePath = frontier[0];
    frontier.erase(frontier.begin());
    return removePath;
}

//Multi-node push
void BFS::PushFrontier(std::vector<Path*> newFrontier) {
    //Add node/action pairs to frontier
    for(auto n : newFrontier){
        frontier.push_back(n);
    }
}

//Single node push
void BFS::PushFrontier(Path* newFrontier) {
    //Add node/action pairs to frontier
    frontier.push_back(newFrontier);
}



void BFS::PopPath() {
    exploredPath.pop_back();
}








