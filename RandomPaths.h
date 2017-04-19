//
// Created by mac on 19/04/17.
//

#ifndef PATHFINDING_RANDOMPATHS_H
#define PATHFINDING_RANDOMPATHS_H

#include <vector>

using namespace std;

//Creates a vector of vector<int> ready to be created into a problem by the parser class
class RandomPaths {
private:
    vector<vector<int>> level;
    enum WALL_TYPE{LONG_SMALL, SHORT_SMALL, THICK_SMALL, THICK_LARGE};

public:
    void GetPath();
    void GetRandomSimulationPaths(int maxWidth, int maxHeight);
    vector<vector<int>> GetNewPath();
};


#endif //PATHFINDING_RANDOMPATHS_H
