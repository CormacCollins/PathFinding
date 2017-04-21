//
// Created by mac on 8/04/17.
//

#include "Astar.h"

using namespace std;

SolutionResponse Astar::Search(Problem& problem, Node* nodeSearch) {

    //To be returned solution
    SolutionResponse* solution;
    RenderCurrentMap(nodeSearch, problem);

    //First node so is the lowest
    Node* searchNode = nodeSearch;
    //Current distance from node
    currentLowestCostFunction = problem.InitialState->goalCost + problem.PathCost;

    do{
        vector<Path*> children = ExpandNode(searchNode, problem);

        //Add nodes from paths to frontier
        for (auto& p : children) {
            PushFrontier(p);
            PushPath(p);
            RenderCurrentMap(p->pathNode, problem);
        }

        //Gets best heuristic value from frontier
        Path* bestPath = HeuristicFunction(problem);

        if (GoalTest(problem, bestPath->pathNode)) {
            //Remove this to see the full Path search of A*

            trimmedPath = TrimPath(problem, exploredPath);
            solution = new SolutionResponse(trimmedPath, "success");

            //trimmedPath = TrimPath();
            return *solution;
        }

        searchNode = bestPath->pathNode;

    } while(!FrontierIsEmpty());

    //Frontier was empty so we did not find the goal
    std::cerr << "Could not find solution - empty child";
    solution = new SolutionResponse("failure");
    return *solution;

}

Path* Astar::HeuristicFunction(Problem problem) {

    Path* lowestPath = frontier[0];
    //Get Starting Path
    float tempLowestCost;
    //Heuristic check
    for(auto& child : frontier){
        float nodeStepCost = child->pathNode->PathCost
                             + child->pathNode->Parent->PathCost;

        //cost function to node f(n) = g(n) + h(n)
         tempLowestCost = (nodeStepCost + child->pathNode->goalCost);

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

Path* Astar::PopFrontier() {
    Path* removeNode = frontier[0];
    frontier.erase(frontier.begin());
    return removeNode;
}

//Multi-node push
void Astar::PushFrontier(std::vector<Path*> newFrontier) {
    //Add node/action pairs to frontier
    for(auto n : newFrontier){
        frontier.push_back(n);
    }
}

//Single node push
void Astar::PushFrontier(Path* newFrontier) {
    //Add node/action pairs to frontier
    frontier.push_back(newFrontier);
}

//pop specific node from frontier
void Astar::PopFrontierNodeSpecific(Path* path) {
    for(int i = 0; i < frontier.size(); i++){
        if(frontier[i] == path){
            frontier.erase(frontier.begin()+i);
            break;
        }
    }
}

std::vector<std::vector<std::string>>& Astar::GetStringPath() {
    return stringPathVec;
}

Astar::Astar() {}


