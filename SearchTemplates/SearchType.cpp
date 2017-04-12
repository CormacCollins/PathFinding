//
// Created by mac on 25/03/17.
//

#include "SearchType.h"

std::vector<Path> SearchType::ExpandNode(Node* currentNode, Problem& problem) {
    int actionCount = 4;
    //Need to track path (nodes and actions)
    std::vector<Path> successors;

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
        successors.push_back(Path(n, ActionType(i)));
    }

    return successors;
}

Node* SearchType::GetActionChild(Node *node, ActionType action) {

    ActionType a = action;
    //Add write to JSON file implementation?

    std::tuple<int,int> instruction;
    //Get lookup instructions
    switch(a){
        case ActionType::LEFT:
            instruction = std::make_tuple(0,-1);
            break;
        case ActionType::RIGHT:
            instruction = std::make_tuple(0,1);
            break;
        case ActionType::UP:
            instruction = std::make_tuple(-1,0);
            break;
        case ActionType::DOWN:
            instruction = std::make_tuple(1,0);
            break;
        default:
            std::cerr << "Error with action look up " << a << std::endl;
            instruction = std::make_tuple(0,0);
            break;
    }

    //Get Node* for action stated - dereference for assigning
    return StateLookUp(node, instruction);
}

///Using Pointer Address comparisons to look up list of Node*
Node* SearchType::StateLookUp(Node* node, std::tuple<int,int> instruction) {
    for(int i = 0; i < stateList.size(); i++){
        for(int j = 0; j < stateList[i].size(); j++){
            if(node == stateList[i][j]){

                //Check if this index exists in our 2d array
                if(i+std::get<0>(instruction) < 0 || i+std::get<0>(instruction) > stateList.size()-1 ||
                   j+std::get<1>(instruction) < 0 || j+std::get<1>(instruction) > stateList[i].size()-1) {
                    Node* n = NULL;
                    return n;
                }
                else if(stateList[i+std::get<0>(instruction)][j+std::get<1>(instruction)] == NULL){
                    Node* n = NULL;
                    return n;
                }
                else if(stateList[i+std::get<0>(instruction)][j+std::get<1>(instruction)] == node->Parent){
                    Node* n = NULL;
                    return n;
                }
                else{
                    return stateList[i+std::get<0>(instruction)]
                    [j+std::get<1>(instruction)];
                }
            }
        }
    }
}

void SearchType::RenderCurrentMap(Node* currentPosition, Problem& problem) {

    std::stringstream ss;
    std::string vis = "";

    std::vector<std::string> tempVec = std::vector<std::string>();
    for (int j = 0; j < stateList.size(); j++) {
        for (int i = 0; i < stateList[j].size(); i++) {

//            if (i > stateList[j].size()) {
//                ss << std::endl;
//            }
            if (stateList[j][i] == problem.InitialState) {
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
            } else {
                ss << "1" << " | ";
                vis = "1";
            }
            tempVec.push_back(vis);
        }
    }



    //combine string groups to have all paths search


    if (stringPathVec.size() > 0) {
        for (int i = 0; i < tempVec.size()-1; i++) {
            if (stringPathVec[stringPathVec.size() - 1][i] == "H") {
                tempVec[i] = "H";
            }

        }
    }
    stringPathVec.push_back(tempVec);

   // std::cout << std::endl << std::endl;
}

bool SearchType::IsInCurrentPath(Node *node) {
    for(Path& n : exploredPath){
        if(n.pathNode == node){
            return true;
        }
    }
    return false;
}

ActionType SearchType::GetAction(std::vector<Path> path, Node* nodeLookUp ) {
    for(Path& a : path){
        if(a.pathNode == nodeLookUp)
            return a.pathAction;
    }
    std::cerr << "Error in node to path look up" << std::endl;
}

Path& SearchType::GetPathFromNode(std::vector<Path> path, Node* nodeLookUp ) {
    for(Path& a : path){
        if(a.pathNode == nodeLookUp)
            return a;
    }
    std::cerr << "Error in node to path look up" << std::endl;
}

//Get nodes stores in current path
std::vector<Node*> SearchType::getNodes() {
    std::vector<Node*> currentNodePath;
    for(Path& p : exploredPath){
        currentNodePath.push_back(p.pathNode);
    }
    return currentNodePath;
}

bool SearchType::FrontierIsEmpty() {
    return frontier.empty();
}

void SearchType::PushPath(Node *node, ActionType journeyAction) {
    exploredPath.push_back(Path(node, journeyAction));
}

std::vector<Path> SearchType::TrimPath( Problem& problem) {
    std::vector<Path> trimmedPathLocal;

    std::vector<Path> pathCopy = exploredPath;

    if(&exploredPath == &pathCopy)
        std::cout << "de";


    //Loop through current path backwards - we want to work backwards from the goal node that we have found
    //E.g. if
    while(!pathCopy.empty()){

        //Get top of path stack (Goal) and follow parents back to start
        Path p = pathCopy[pathCopy.size()-1];

        //Start square has null parent :-
        //We don't add to path expanded
//        if(p.pathNode->Parent == NULL){
//            break;
//        }

        trimmedPathLocal.push_back(p);
        pathCopy.erase(pathCopy.end()-1);

        //Looping backwards checking nodes against node we have followed with action
        //Remove nodes that don't match the correct route
        while(pathCopy[pathCopy.size()-1].pathNode != p.pathNode->Parent){
            //remove from current path (trim)
            pathCopy.erase(pathCopy.end()-1);
            if(pathCopy.empty())
                break;
        }
    }

    //reverse paths from start to finish
    std::reverse(trimmedPathLocal.begin(), trimmedPathLocal.end());

    //Replace current path with the newly trimmed goal path
    return trimmedPathLocal;
}

bool SearchType::GoalTest(Problem& problem, Node* node) {
    return problem.GoalState == node;
}

std::vector<std::vector<std::string>>& SearchType::GetStringPath() {
    return stringPathVec;
}

SolutionResponse SearchType::Search(Problem& problem, Node* nodeSearch) {
    //Needs to be implemented by children classes
    return SolutionResponse();
}

int SearchType::PathsExplored() {
    exploredPath.size();
}

std::vector<Path> SearchType::GetTrimmedPath() {
    return trimmerPath;
}

std::vector<Path> SearchType::GetExploredPath() {
    return exploredPath;
}

