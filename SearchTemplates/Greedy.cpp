//
// Created by mac on 14/04/17.
//

#include "Greedy.h"
using namespace std;

SolutionResponse Greedy::Search(Problem& problem, Node* nodeSearch) {

    //To be returned solution
    SolutionResponse* solution;
    RenderCurrentMap(nodeSearch, problem);
    Path newPath = Path(nodeSearch);
    Path* bestPath = &newPath;

    do{
        vector<Path*> children = ExpandNode(bestPath->pathNode, problem);

        //Add nodes from paths to frontier
        for (auto& p : children) {
            PushFrontier(p);
        }

        //Add to explored set
        bestPath = HeuristicFunction(frontier);
        PushPath(bestPath);

        //Add state for visualization
        RenderCurrentMap(bestPath->pathNode, problem);

        //Check for goal
        if (GoalTest(problem, bestPath->pathNode)) {
            trimmerPath = TrimPath(problem);
            solution = new SolutionResponse(trimmerPath, "success");
            return *solution;
        }

    } while(!FrontierIsEmpty());

    //Frontier was empty so we did not find the goal
    std::cerr << "Could not find solution - empty child";
    solution = new SolutionResponse("failure");
    return *solution;

}

Path* Greedy::HeuristicFunction(vector<Path*>& paths) {

    Path* lowestPath = paths[0];
    //Get Starting Path
    float lowestCost = lowestPath->pathNode->goalCost;
    //Heuristic check
    for(auto& child : paths){
        //cost function to node f(n) = h(n)
        float lowestCostTemp = child->pathNode->goalCost;

            //if new one is lower than the previous lowest it is now the lower
            if (lowestCostTemp < lowestCost) {
                lowestCost = lowestCostTemp;
                lowestPath = child;
            }
    }

    //remove lowest Path
    for(int i = 0; i < paths.size(); i++){
        if(paths[i] == lowestPath){
            paths.erase(paths.begin()+i);
            break;
        }
    }

    return lowestPath;
}

std::vector<Path*> Greedy::ExpandNode(Node* currentNode, Problem& problem) {
    int actionCount = 4;
    //Need to track path (nodes and actions)
    std::vector<Path*> successors;

    //first in action count is LEFT
    for( int i = 0; i < actionCount; i++){
        //Try action and return node from it
        Node* n = GetActionChild(currentNode, ActionType(i));


        //If returned null then we did not have a node for this action
        // OR if its in out current path we do not want to follow it - to avoid loops
        if(n == NULL || IsInCurrentPath(n)) {
            continue;
        }

        n->Depth = currentNode->Depth + problem.PathCost;
        n->PathCost = problem.PathCost;
        n->Parent = currentNode;

        //Add to vector of Path types
        successors.push_back(new Path(n, ActionType(i)));
    }

    return  successors;
}

Path* Greedy::PopFrontier() {
    Path* removeNode = frontier.back();
    frontier.erase(frontier.end()-1);
    return removeNode;
}