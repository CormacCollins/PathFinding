//
// Created by mac on 26/03/17.
//

#ifndef PATHFINDING_SOLUTIONRESPONSE_H
#define PATHFINDING_SOLUTIONRESPONSE_H

#include <vector>
#include <string>
#include "Node.h"

class SolutionResponse {
public:

    //Solution in XY coords added to SolutionResponse wrapper
    SolutionResponse(std::vector<Node*> solution, std::string outcome){
        solutionActions = solution;
        responseOutcome = outcome;
    }
    //Used when just a failed response
    SolutionResponse(std::string outcome){
        responseOutcome = outcome;
    }

    std::vector<Node*> solutionActions;
    std::string responseOutcome;
};


#endif //PATHFINDING_SOLUTIONRESPONSE_H
