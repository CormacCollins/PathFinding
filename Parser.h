//
// Created by mac on 18/03/17.
//

#ifndef PATHFINDING_PARSER_H
#define PATHFINDING_PARSER_H

#include <fstream>
#include <vector>
#include "SearchTemplates/Node.h"
#include "SearchTemplates/SearchType.h"

///Parses text file in addition to function for setting up NodeMap and problem class
class Parser {
private:
    // Convert int 2d array to both:
    // 1.) NodeMap stored in 'nodeMatrix'
    // 2.) Store problem details in 'problem' such as goal and initial state Node*
    void SetupProblem();

public:
    int mapHeight;
    int mapWidth;
    //Designed to parse specific path file into 2d vector for easy access
    void ParseFile(std::ifstream& file);

    //Initial data parsed into standard data file
    std::vector<std::vector<int>> dataMatrix;

    //Values to provide a search algorithm
    Problem problem;
    std::vector<std::vector<Node*>> nodeMatrix;

    //For artificially created maps
    void AddMapVector(std::vector<std::vector<int>> newMap);
};

#endif //PATHFINDING_PARSER_H
