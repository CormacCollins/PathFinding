//
// Created by mac on 26/03/17.
//

#ifndef PATHFINDING_SOLUTIONRESPONSE_H
#define PATHFINDING_SOLUTIONRESPONSE_H

#include <vector>
#include <string>
#include "Node.h"
#include "Path.h"

class SolutionResponse {
public:

    SolutionResponse(std::string outcome="undefined"){
        responseOutcome = outcome;
    }
    //Solution in XY coords added to SolutionResponse wrapper
    SolutionResponse(std::vector<Path>& solution, std::string outcome){
        solutionActions = solution;
        responseOutcome = outcome;
    }

    std::vector<Path> GetActions();
    std::string ResOutcome();

    std::vector<Path> solutionActions;
    std::string responseOutcome;
};


#endif //PATHFINDING_SOLUTIONRESPONSE_H
