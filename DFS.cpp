//
// Created by mac on 23/03/17.
//

#include "DFS.h"
#include <vector>
#include <algorithm>
#include <search.h>
#include "SearchTemplates/Action.h"
#include <iostream>
#include <sstream>
#include "SearchTemplates/SolutionResponse.h"

//LOOKING AT RETURNING ACTION-NODE AGAIN?


std::vector<Node*> DFS::ExpandNode(Node* currentNode, Problem problem) {
    int actionCount = 4;
    std::vector<Node*> successors;

    //get children and iterate
    ActionType arr[4] = {LEFT, RIGHT, UP, DOWN};
    for( int i = 0; i < actionCount; i++){
        //Try action and return node from it
        Node* n = GetChild(currentNode, ActionType(i));

        //If returned null then we did not have a node for this action
        // OR if its in out current path we do not want to follow it - to avoid loops
        if(n == NULL || IsInPath(n)) {
            continue;
        }

        n->_depth = currentNode->_depth + problem.PathCost;
        n->_pathcost = currentNode->_depth + problem.PathCost;
        n->_parent = currentNode;

        successors.push_back(n);
    }

    //no new nodes (ignored parent)
    if(successors.empty() || &successors == NULL){
        return successors;
    }
    return successors;
}

Node* DFS::GetChild(Node* node, ActionType action) {

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
            std::cerr << "Error with action look up";
            instruction = std::make_tuple(0,0);
            break;
    }

    //Get Node* for action stated - dereference for assigning
    return StateLookUp(node, instruction);
}

///Using Pointer Address comparisons to look up list of Node*
Node* DFS::StateLookUp(Node* node, std::tuple<int,int> instruction) {
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
                else if(stateList[i+std::get<0>(instruction)][j+std::get<1>(instruction)] == node->_parent){
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

//recursively call DepthSearch
SolutionResponse& DFS::Search(Problem& problem, Node* nodeSearch) {
    return DepthSearch(problem, nodeSearch);
}


SolutionResponse& DFS::DepthSearch(Problem& problem, Node* searchNode){

    //Goal check
    if (GoalTest(problem, searchNode)){
        SolutionResponse solution(Path, "success");
        return solution;
    }

    RenderCurrentMap(searchNode, problem);
    //Push first children onto frontier
    std::vector<Node*> children = ExpandNode(searchNode, problem);

    if(children.empty()){
        Path.pop_back();
        std::cerr << "Could not find solution - empty child";
        SolutionResponse solution("failed");
        return solution;
    }

    PushFrontier(children);

    while(!FrontierIsEmpty()) {
        //Get top of stack for DPS (LIFO)
        Node* currentNode = PopFrontier();
        Path.push_back(currentNode);

        //begin search again
        return DepthSearch(problem, currentNode);
    }
};

//Multi-node push
void DFS::PushFrontier(std::vector<Node*> newFrontier) {
    //Add node/action pairs to frontier
    for(auto n : newFrontier){
        frontier.push_back(n);
    }
}

//Single node push
void DFS::PushFrontier(Node* newFrontier) {
    //Add node/action pairs to frontier
    frontier.push_back(newFrontier);
}

bool DFS::FrontierIsEmpty() {
    return frontier.empty();
}

Node* DFS::PopFrontier() {
    Node* removeNode = frontier[frontier.size()-1];
    frontier.pop_back();
    //Adding this node to our currently traversed path
    Path.push_back(removeNode);
    return removeNode;
}

bool DFS::GoalTest(Problem& problem, Node* node) {
    RenderCurrentMap(node, problem);
    if(problem.GoalState == node){
        return true;
    }
    return false;
}

void DFS::RenderCurrentMap(Node* currentPosition, Problem problem) {
    //Parser test
    int i = 0;
    for(int j = 0; j <  stateList.size(); j++) {
        for (Node *a : stateList[j]) {
            std::stringstream ss;

            if (i > 10) {
                i = 0;
                ss << std::endl;
            }

            if(a ==  currentPosition){
                ss << "H" << " | ";
            }
            else if (a == problem.InitialState){
                ss << "#" << " | ";
            }
            else if (a == problem.GoalState){
                ss << "X" << " | ";
            }
            else if (a == NULL){
                ss << "W" << " | ";
            }
            else {
                ss << "0" << " | ";
            }


            std::cout << ss.str();
            i++;
        }
    }
    std::cout << std::endl << std::endl;
}

bool DFS::IsInPath(Node* node) {
    for(auto n : Path){
        if(n == node){
            return true;
        }
    }
    return false;
}

