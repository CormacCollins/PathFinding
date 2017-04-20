//
// Created by mac on 19/04/17.
//

#include "Bidirectional.h"

using namespace std;

SolutionResponse Bidirectional::Search(Problem& problem, Node* nodeSearch){
    auto s1 = BidirectionalSearch(problem);
    return s1;
}

SolutionResponse Bidirectional::BidirectionalSearch(Problem& problem){
    //To be returned solution
    SolutionResponse* solution;

    //Starting at both ends of the search
    RenderCurrentMap(problem.InitialState, problem);
    RenderCurrentMap(problem.GoalState, problem);


    //First node so is the lowest
    Node* searchNodeStart = problem.InitialState;
    Node* searchNodeEnd = problem.GoalState;

    //Current distance from node
    currentLowestCostFunction = problem.InitialState->goalCost + problem.PathCost;
    currentInvertedCostFunction = problem.GoalState->goalCost - problem.InitialState->goalCost;

    // -----------------------------------
    // 2 of everything for bidirectional!
    // -----------------------------------
    do{
        vector<Path*> children = BidirectionalExpandNode(searchNodeStart, problem, exploredPath);
        vector<Path*> childrenFromGoal = BidirectionalExpandNode(searchNodeEnd, problem, exploredPathFromGoal);

        //Add nodes from paths to START frontier
        for (auto& p : children) {
            PushFrontier(p, frontier);
            PushPathSpecific(p, exploredPath);
            RenderCurrentMap(p->pathNode, problem);
        }

        //Add nodes from paths to GOAL frontier
        for (auto& p : childrenFromGoal) {
            PushFrontier(p, frontierFromGoal);
            PushPathSpecific(p, exploredPathFromGoal);
            RenderCurrentMap(p->pathNode, problem);
        }

        //Gets best heuristic value from frontier
        Path* bestPath = HeuristicFunction();
        //Gets best heuristic value from frontier
        Path* bestPathFromGoal = HeuristicFunctionFromGoal(problem);

        cout << "best path start: " << currentLowestCostFunction << endl;
        cout << "best path from finish: " << currentInvertedCostFunction << endl;

        //Check if any intersection between frontier nodes
        if (BidirectionalGoalTest()) {

            //Get both paths and combine for the goals
//            trimmedPath = BidirectionalTrimPath(problem, exploredPath, endNodeStart);
//            trimmedPathFromGoal = BidirectionalTrimPath(problem, exploredPathFromGoal, endNodeGoal);
            //trimmedPath = CombineTrimmedPaths(trimmedPath, trimmedPathFromGoal);
            solution = new SolutionResponse(exploredPath, "success");

            return *solution;
        }

        searchNodeStart = bestPath->pathNode;
        searchNodeEnd = bestPathFromGoal->pathNode;

    } while(!FrontierIsEmpty() || !GoalFrontierIsEmpty());

    //Frontier was empty so we did not find the goal
    std::cerr << "Could not find solution - empty child";
    solution = new SolutionResponse("failure");
    return *solution;

}

Path* Bidirectional::HeuristicFunction() {

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
    PopFrontierNodeSpecific(lowestPath, frontier);

    return lowestPath;
}

//Find biggest cost (trying to get away from goal
Path* Bidirectional::HeuristicFunctionFromGoal(Problem problem) {

    Path* highestPath = frontierFromGoal[0];
    //Get Starting Path
    float tempHighestCost;
    //Heuristic check
    for(auto& child : frontierFromGoal){
        float nodeStepCost = child->pathNode->PathCost
                             + child->pathNode->Parent->PathCost;

        //cost function to node f(n) = g(n) + h(n)
        tempHighestCost = ((child->pathNode->goalCost - problem.InitialState->goalCost)  - nodeStepCost);

        //if new one is higher than the previous highest it is now the higher
        if(tempHighestCost > currentInvertedCostFunction) {
            currentInvertedCostFunction = tempHighestCost;
            highestPath = child;
        }
    }

    //Remove our chosen node from frontier as it is now the next expanded
    PopFrontierNodeSpecific(highestPath, frontierFromGoal);

    return highestPath;
}

Path* Bidirectional::PopFrontier(std::vector<Path*>& chosenFrontier) {
    Path* removeNode = chosenFrontier[0];
    chosenFrontier.erase(chosenFrontier.begin());
    return removeNode;
}

//Multi-node push
void Bidirectional::PushFrontier(std::vector<Path*> newNodes, std::vector<Path*>& chosenFrontier) {
    //Add node/action pairs to frontier
    for(auto n : newNodes){
        chosenFrontier.push_back(n);
    }
}

//Single node push
void Bidirectional::PushFrontier(Path* newFrontier, std::vector<Path*>& chosenFrontier) {
    //Add node/action pairs to frontier
    chosenFrontier.push_back(newFrontier);
}

//pop specific node from frontier
void Bidirectional::PopFrontierNodeSpecific(Path* path, std::vector<Path*>& chosenFrontier) {
    for(int i = 0; i < chosenFrontier.size(); i++){
        if(chosenFrontier[i] == path){
            chosenFrontier.erase(chosenFrontier.begin()+i);
            break;
        }
    }
}



std::vector<std::vector<std::string>>& Bidirectional::GetStringPath() {
    return stringPathVec;
}

bool Bidirectional::BidirectionalGoalTest() {

    for(auto* start : exploredPath){
        for(auto* goal : exploredPathFromGoal){
            if(start->pathNode == goal->pathNode){
                //Store the goals that the paths met
                endNodeStart = start;
                //Get parent of the meeting node so we don't count twice
                for(auto a : exploredPathFromGoal){
                    if(goal->pathNode->Parent == a->pathNode){
                        endNodeGoal = a;
                    }

                }

                return true;
            }
        }
    }
    return false;
}

std::vector<Path*> Bidirectional::CombinePaths(std::vector<Path*>& path1, std::vector<Path*>& path2) {
    vector<Path*> newPath = vector<Path*>();

    //fill up new vector with intertwined vectors
    while(!path1.empty() || path2.empty()) {

        if(!path1.empty()){
            auto p = path1[0];
            newPath.push_back(p);
            path1.erase(path1.begin());
        }

        if(!path2.empty()){
            auto p2 = path2[0];
            newPath.push_back(p2);
            path2.erase(path2.begin());
        }
    }

    return newPath;
}

std::vector<Path*> Bidirectional::CombineTrimmedPaths(std::vector<Path*>& path1, std::vector<Path*>& path2) {
    vector<Path*> newPath;

    //fill up new vector with intertwined vectors
    for(int i = 0; i < path1.size() || i < path2.size(); i++) {
        if(i < path1.size()){
            newPath.push_back(path1[i]);
        }

        if(i < path2.size()){
            newPath.push_back(path2[i]);
        }
    }

    return newPath;
}

bool Bidirectional::GoalFrontierIsEmpty() {
    return frontierFromGoal.empty();
}

void Bidirectional::PushPathSpecific(Path* path, std::vector<Path*>& chosenPath){
    chosenPath.push_back(path);
}

std::vector<Path*> Bidirectional::BidirectionalTrimPath(Problem& problem, std::vector<Path*> chosenPath, Path* startPath) {
    std::vector<Path*> trimmedPathLocal;

    //Loop through current path backwards - we want to work backwards from the goal node that we have found
    //E.g. if
    int i = 0;
    trimmedPathLocal.push_back(startPath);
    Node* parent = startPath->pathNode->Parent;

    while(parent->Parent != NULL && parent != problem.GoalState && parent != problem.InitialState){

        //find path that correseonds to parent and add it
        for(auto* a : chosenPath){
            if(a->pathNode == parent){
                trimmedPathLocal.push_back(a);
                //Now traverse up chain of parents
                parent = parent->Parent;
                break;
            }
        }

        i++;
    }

    //reverse paths from start to finish
    std::reverse(trimmedPathLocal.begin(), trimmedPathLocal.end());

    //Replace current path with the newly trimmed goal path
    return trimmedPathLocal;
}


std::vector<Path*> Bidirectional::GetExploredPathFromGoal() {
    return exploredPathFromGoal;
}

std::vector<Path *> Bidirectional::BidirectionalExpandNode(Node *currentNode, Problem& problem,  std::vector<Path*> pathCheck) {
        int actionCount = 4;
        //Need to track path (nodes and actions)
        std::vector<Path*> successors;

        //first in action count is LEFT
        for( int i = 0; i < actionCount; i++){
            //Try action and return node from it
            Node* n = GetActionChild(currentNode, ActionType(i));

            //If returned null then we did not have a node for this action
            // OR if its in out current path we do not want to follow it - to avoid loops
            if(n == NULL || IsInPath(n, pathCheck)) {
                continue;
            }

            n->Depth = currentNode->Depth + problem.PathCost;
            n->PathCost = problem.PathCost;
            n->Parent = currentNode;

            //Add to vector of Path types
            successors.push_back(new Path(n, ActionType(i)));
        }

        return successors;
}

bool Bidirectional::IsInPath(Node* node, std::vector<Path*> pathCheck) {
    for(auto* a : pathCheck){
        if(a->pathNode == node){
            return true;
        }
    }
    return false;
}

