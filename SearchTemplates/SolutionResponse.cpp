//
// Created by mac on 26/03/17.
//

#include "SolutionResponse.h"

std::vector<Path> SolutionResponse::GetActions() {
    return solutionActions;
}

std::string SolutionResponse::ResOutcome() {
    return responseOutcome;
}
