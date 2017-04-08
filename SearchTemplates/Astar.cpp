//
// Created by mac on 8/04/17.
//

#include "Astar.h"

using namespace std;

SolutionResponse Astar::Search(Problem& problem, Node *nodeSearch) {

    //To be returned solution
    SolutionResponse* solution;

    //Check if goal node
    if(GoalTest(problem, nodeSearch)){
        TrimPath();
        solution = new SolutionResponse(currentPath, "success");
        return *solution;
    }

    //Get children from new node with respective actions
    vector<Path> children = ExpandNode(nodeSearch, problem);

    if(children.empty() || children.size() == 0){
        std::cerr << "Could not find solution - empty child";
        solution = new SolutionResponse("failure");
        return *solution;
    }

    //Add nodes from paths to frontier
    for(auto& p : children){
        PushFrontier(p.pathNode);
    }

    //Gets our current lowest cost node + updates the overall lowest number

    while(!FrontierIsEmpty()) {
        //Gets best heuristic value from frontier
        lowestCostNode = HeuristicFunction();

        GoalTest(problem, lowestCostNode){

        }

        //Add Path to path list
        //Will need to change to get correct PATH -------------- !!!!!
        PushPath(lowestCostNode, GetAction(children, lowestCostNode));

        vector<Path> childrenTemp = ExpandNode(lowestCostNode, problem);

        //Add nodes from paths to frontier
        for(auto& p : childrenTemp){
            PushFrontier(p.pathNode);
        }
    }

    //Frontier was empty so we did not find the goal
    std::cerr << "Could not find solution - empty child";
    solution = new SolutionResponse("failure");
    return *solution;

}

Node* Astar::HeuristicFunction() {

    //Get first child for comparison
    int nodeStepCost = (frontier[0]->PathCost - frontier[0]->Parent->PathCost); // g(n)
    int lowest = (nodeStepCost + frontier[0]->Parent->goalCost);
    Node* lowestPath = frontier[0];

    //Heuristic check
    for(auto& child : frontier){
        nodeStepCost = frontier[0]->PathCost - frontier[0]->Parent->PathCost;

        //cost function to node f(n) = g(n) + h(n)
        int tempLowestCost = (nodeStepCost + frontier[0]->Parent->goalCost);

        //if new one is lower than the previous lowest it is now the lower
        if(tempLowestCost < currentLowestCostFunction)
            currentLowestCostFunction = tempLowestCost;
            lowestPath = child;

    }

    return lowestPath;
}

Node* Astar::PopFrontier() {
    Node* removeNode = frontier[0];
    frontier.erase(frontier.begin());
    return removeNode;
}

//Multi-node push
void Astar::PushFrontier(std::vector<Node*> newFrontier) {
    //Add node/action pairs to frontier
    for(auto n : newFrontier){
        frontier.push_back(n);
    }
}

//Single node push
void Astar::PushFrontier(Node* newFrontier) {
    //Add node/action pairs to frontier
    frontier.push_back(newFrontier);
}

