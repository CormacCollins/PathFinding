//
// Created by mac on 20/04/17.
//

#include "MBAstar.h"

using namespace std;

Path* MBAstar::HeuristicFunction(Problem problem) {


    if((exploredPath.size()-1) >= MAX_PATHS)
    {
        RemoveWorstPathFromExplored(problem);
    }

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

void MBAstar::RemoveWorstPathFromExplored(Problem problem) {


    float lowestCost = 0;
    float templowestCost;
    float highestCost;
    Path* lowestPathToRemove;
    for(auto& a : exploredPath){
        float nodeStepCost = a->pathNode->PathCost
                             + a->pathNode->Parent->PathCost;

        //cost function to node f(n) = g(n) + h(n)
        templowestCost = (nodeStepCost + a->pathNode->goalCost);

        if(templowestCost > lowestCost) {
            lowestCost = templowestCost;
            lowestPathToRemove = a;
        }
    }

    //remove the node
    for(int i = 0; i < exploredPath.size()-1; i++){
        if(exploredPath[i]->pathNode == lowestPathToRemove->pathNode){
            nodeRemove = exploredPath[i]->pathNode;
            exploredPath.erase(exploredPath.begin()+i);
            break;
        }
    }

}

SolutionResponse MBAstar::Search(Problem& problem, Node* nodeSearch) {


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

            //Trims from goal - which will have reached if we are here
            trimmedPath = MBATrimPath(problem, exploredPath);
            solution = new SolutionResponse(trimmedPath, "success");

            //trimmedPath = TrimPath();
            return *solution;
        }

        searchNode = bestPath->pathNode;

        iterations++;

        if(iterations > ITERATION_MAX){
            SolutionResponse* s = new SolutionResponse("failure");
            return *s;
        }

    } while(!FrontierIsEmpty());

    //Frontier was empty so we did not find the goal
    std::cerr << "Could not find solution - empty child";
    solution = new SolutionResponse("failure");
    return *solution;

}

void MBAstar::RenderCurrentMap(Node* currentPosition, Problem& problem) {

    std::stringstream ss;
    std::string vis = "";

    std::vector<std::string> tempVec = std::vector<std::string>();
    for (int j = 0; j < stateList.size(); j++) {
        for (int i = 0; i < stateList[j].size(); i++) {

//            if (i > stateList[j].size()) {
//                ss << std::endl;
//            }
            if (stateList[j][i] == nodeRemove){ //newly added to remove previously added nodes
                ss << "D" << " | ";
                vis = "D";
            }
            else if (stateList[j][i] == problem.InitialState) {
                ss << "S" << " | ";
                vis = "S";
            }
            else if (stateList[j][i] == currentPosition) {
                ss << "H" << " | ";
                vis = "H";
            } else if (stateList[j][i] == problem.GoalState) {
                ss << "X" << " | ";
                vis = "X";
            } else if (stateList[j][i] == NULL) {
                ss << "W" << " | ";
                vis = "W";
            }
            else {
                ss << "1" << " | ";
                vis = "1";
            }
            tempVec.push_back(vis);
        }
    }

    //combine string groups to have all paths search
    if (stringPathVec.size() > 0) {
        for (int i = 0; i < tempVec.size()-1; i++) {
            if (tempVec[i] == "D") {
                stringPathVec[stringPathVec.size() - 1][i] = "1";
            }
            if (stringPathVec[stringPathVec.size() - 1][i] == "H") {
                tempVec[i] = "H";
            }
        }
    }
    stringPathVec.push_back(tempVec);

    // std::cout << std::endl << std::endl;
}

std::vector<Path*> MBAstar::MBATrimPath(Problem& problem, std::vector<Path*> explored) {
    std::vector<Path*> trimmedPathLocal;

    Node* startNode;
    for(auto* a : explored){
        if(a->pathNode == problem.GoalState){
            trimmedPathLocal.push_back(a);
            startNode = a->pathNode;
        }
    }

    while(startNode->Parent != NULL && startNode != problem.InitialState){
        startNode = startNode->Parent;
        vector<Path*> children = ExpandNode(startNode, problem);
        for(auto* path : children){
            if(path->pathNode == startNode->Parent){
                trimmedPathLocal.push_back(path);
            }
        }
    }

    //trimmedPathLocal = GetParentPath(startNode, problem, explored);

    //reverse paths from start to finish
    std::reverse(trimmedPathLocal.begin(), trimmedPathLocal.end());

    //Replace current path with the newly trimmed goal path
    return trimmedPathLocal;
}



std::vector<Path*> MBAstar::GetParentPath(Node* currentNode, Problem& problem, std::vector<Path*> explored) {
    int actionCount = 4;
    //Need to track path (nodes and actions)
    std::vector<Path*> successors;

    while(currentNode->Parent != NULL && currentNode != problem.InitialState) {
            //first in action count is LEFT
            for (int i = 0; i < actionCount; i++) {
                //Try action and return node from it
                Node* n = GetActionChild(currentNode, ActionType(i));

                //If returned null then we did not have a node for this action
                // OR if its in out current path we do not want to follow it - to avoid loops
                if (n == NULL || n == problem.InitialState) {
                    continue;
                }

                for(auto* a : explored) {
                    //we have gotten the parent so add and break
                    if (n == a->pathNode) {
                        n->Depth = currentNode->Depth + problem.PathCost;
                        n->PathCost = problem.PathCost;
                        n->Parent = currentNode;

                        //Add to vector of Path types
                        successors.push_back(new Path(n, ActionType(i)));
                        break;
                    }
                }
            }
        currentNode = currentNode->Parent;
    }
    return successors;
}
