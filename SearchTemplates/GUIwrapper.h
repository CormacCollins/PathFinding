//
// Created by mac on 20/04/17.
//

#ifndef PATHFINDING_GUIWRAPPER_H
#define PATHFINDING_GUIWRAPPER_H


#include "SearchType.h"
#include "vector"
using namespace std;

class GUIwrapper {
public:
    GUIwrapper(Parser pp, SearchType* search1, int algoChoice );
    void ChangeColours(vector<sf::RectangleShape>& rectangleVec, int height, int width, int stateNum , SearchType s);
    void ChangeColoursFinalPath(vector<sf::RectangleShape>& rectangleVec, int height, int width, int stateNum, SearchType s);
};


#endif //PATHFINDING_GUIWRAPPER_H
