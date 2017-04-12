//
// Created by mac on 8/04/17.
//

#include "Astar.h"

using namespace std;

SolutionResponse Astar::Search(Problem& problem, Node* nodeSearch) {

    //To be returned solution
    SolutionResponse* solution;
    RenderCurrentMap(nodeSearch, problem);

//    //First node added to path (without action)
//    Path firstPath = Path();
//    firstPath.pathNode = nodeSearch;
//    exploredPath.push_back(firstPath);

    //First node so is the lowest
    lowestCostNode = nodeSearch;
    //Current distance from node
    currentLowestCostFunction = problem.InitialState->goalCost + problem.PathCost;

    do{
        vector<Path> children = ExpandNode(lowestCostNode, problem);

        //Add nodes from paths to frontier
        for (auto& p : children) {
            PushFrontier(p.pathNode);
            PushPath(p.pathNode, p.pathAction);
            RenderCurrentMap(p.pathNode, problem);
        }

        //Gets best heuristic value from frontier
        lowestCostNode = HeuristicFunction();

        if (GoalTest(problem, lowestCostNode)) {
            //Remove this to see the full Path search of A*

            trimmerPath = TrimPath(problem);
            solution = new SolutionResponse(trimmerPath, "success");

            //trimmerPath = TrimPath();
            return *solution;
        }

    } while(!FrontierIsEmpty());

    //Frontier was empty so we did not find the goal
    std::cerr << "Could not find solution - empty child";
    solution = new SolutionResponse("failure");
    return *solution;

}

Node* Astar::HeuristicFunction() {

    Node* lowestPath = frontier[0];
    //Get Starting Path
    float tempLowestCost;
    //Heuristic check
    for(auto& child : frontier){
        float nodeStepCost = child->PathCost + child->Parent->PathCost;

        //cost function to node f(n) = g(n) + h(n)
         tempLowestCost = (nodeStepCost + child->goalCost);

        if(child->goalCost == 0){
            cout << "fe";
        }

        //if new one is lower than the previous lowest it is now the lower
        if(tempLowestCost < currentLowestCostFunction) {
            currentLowestCostFunction = tempLowestCost;
            lowestPath = child;
        }
    }

    //Remove our chosen node from frontier as it is now the next expanded
    PopFrontierNodeSpecific(lowestPath);

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

//pop specific node from frontier
void Astar::PopFrontierNodeSpecific(Node* node) {
    for(int i = 0; i < frontier.size(); i++){
        if(frontier[i] == node){
            frontier.erase(frontier.begin()+i);
            break;
        }
    }
}

std::vector<std::vector<std::string>>& Astar::GetStringPath() {
    return stringPathVec;
}

