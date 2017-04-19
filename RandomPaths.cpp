//
// Created by mac on 19/04/17.
//

#include <iostream>
#include "RandomPaths.h"
#include <stdlib.h>
#include <time.h>
#include <chrono>

using namespace std;

void RandomPaths::GetPath(){
//    vector<int> coordsTemp;
//    int tempX, tempY;
//    vector<int> tempVec;
//    cout << "Grid rows then columns" << endl;
//    cin >> tempX >> tempY;
//    tempVec = {tempX, tempY};
//    level.push_back(tempVec);
//
//    cout << "Start location X - Y" << endl;
//    cin >> tempX >> tempY;
//    tempVec = {tempX, tempY};
//    level.push_back(tempVec);
//
//    cout << "Goal location X - Y" << endl;
//    cin >> tempX >> tempY;
//    tempVec = {tempX, tempY};
//    level.push_back(tempVec);
//
//    int wallNumber = 0;
//    cout << "Wall number" << endl;
//    cin >> wallNumber;
//
//    for(int i = 1; i <= wallNumber; i++) {
//        cout << "Wall start location X - Y" << endl;
//        cin >> tempX >> tempY;
//        cout << "Size width - height" << endl;
//        int width, height;
//        cin >> width >> height;
//        vector<int> wall = {tempX, tempY, width, height};
//        level.push_back(wall);
//    }
}

vector<vector<int>> RandomPaths::GetNewPath() {
    return level;
}

void RandomPaths::GetRandomSimulationPaths(int maxWidth, int maxHeight) {
    int randHeight, randWidth = 0;
    int locationLimitX, locationLimitY = 0;
    auto seedTime = std::chrono::system_clock::now();
    //initialize random seed
    srand (time(NULL));


    vector<vector<int>> newLevel = vector<vector<int>>();
    newLevel.push_back(vector<int>());

    //Rand number within max ranges
    int tempH = rand() % (maxHeight - (maxHeight-3));
    randHeight = tempH > maxHeight-3 ? tempH : maxHeight-3;
    int tempW = rand() % (maxWidth - (maxWidth-3));
    randWidth = tempW > (maxWidth-3) ? tempW : maxWidth-3;
    locationLimitX = randWidth;
    locationLimitY = randHeight;

    //Random wall numbers

    int randWallNumber = (rand() % (4)-2)+3;

    // --------------- Random width / height -------------------- //
    // ** Rows first ** //
    newLevel.back().push_back(randHeight);
    newLevel.back().push_back(randWidth);
    //Add new vector ref to matrix
    newLevel.push_back(std::vector<int>());

    //Want position to be within 2 of the start of map at this stage
    randHeight = rand() % (2 - 0 +1);
    randWidth = rand() % (2 - 0 + 1);

    // ------------------- Random X - Y start --------------------- //
    newLevel.back().push_back(randWidth);
    newLevel.back().push_back(randHeight);
    //Add new vector ref to matrix
    newLevel.push_back(std::vector<int>());

    //Want position to be within 2 of the end of map at this stage
    randHeight = rand() % (locationLimitY - (locationLimitY-2) + 1) + locationLimitY-2;
    randWidth = rand() % (locationLimitX - (locationLimitX-2) + 1) + locationLimitY-2;

    // ------------------- Random X - Y goal --------------------- //
    newLevel.back().push_back(randWidth);
    newLevel.back().push_back(randHeight);

    if(randWallNumber > 0){
        //Add new vector ref to matrix
        newLevel.push_back(std::vector<int>());
    }

    int wallType;
    int tempY, tempX, tempWidth, tempHeight = 0;


    for(int j = 1; j <= randWallNumber; j++) {


        //E.g. get LONG_SHORT or THICK_LARGE
        wallType = rand() % (4);

        switch (WALL_TYPE(wallType)) {
            case
                WALL_TYPE::LONG_SMALL:
                //If values are under 0.5 we must make them 1
                tempHeight = (int)(locationLimitY * 0.6 > 1 ? locationLimitY * 0.6 : 1);
                tempWidth = (int)(locationLimitX * 0.05 > 1 ? locationLimitX * 0.05 : 1);
                //Start at random position ('2' is that we don't want to block the starting position)
                tempX = rand() % (locationLimitX);
                tempX = tempX < 1 ? 1 : tempX;
                tempY = rand() % (locationLimitY);
                tempY = tempY < 1 ? 1 : tempY;
                break;
            case
                WALL_TYPE::SHORT_SMALL:
                //If values are under 0.5 we must make them 1
                tempHeight = (int)(locationLimitY * 0.3 > 1 ? locationLimitY * 0.3 : 1);
                tempWidth = (int)(locationLimitX * 0.05 > 1 ? locationLimitX * 0.05 : 1);
                //Start at random position ('0.2' is that the width / height ('thickness') must be 'small' relative to maps
                tempX = rand() % (locationLimitX);
                tempX = tempX < 1 ? 1 : tempX;
                tempY = rand() % (locationLimitY);
                tempY = tempY < 1 ? 1 : tempY;
                break;
            case
                WALL_TYPE::THICK_LARGE:
                //If values are under 0.5 we must make them 1
                tempHeight = (int)(locationLimitY * 0.5 >= 1 ? locationLimitY * 0.5 : 1);
                tempWidth = (int)(locationLimitX * 0.5 >= 1 ? locationLimitX * 0.5 : 1);
                //Start at random position ('2' is that we don't want to block the starting position)
                tempX = rand() % (locationLimitX);
                tempX = tempX < 1 ? 1 : tempX;
                tempY = rand() % (locationLimitY);
                tempY = tempY < 1 ? 1 : tempY;
                break;
            case WALL_TYPE::THICK_SMALL:
                //If values are under 0.5 we must make them 1
                tempHeight = (int)(locationLimitY * 0.25 >= 1 ? locationLimitY * 0.25 : 1);
                tempWidth = (int)(locationLimitX * 0.25 >= 1 ? locationLimitX * 0.25 : 1);
                //Start at random position ('2' is that we don't want to block the starting position)
                tempX = rand() % (locationLimitX);
                tempX = tempX < 1 ? 1 : tempX;
                tempY = rand() % (locationLimitY);
                tempY = tempY < 1 ? 1 : tempY;
                break;
            default:
                cerr << "Could not read wall type correctly" << endl;
                break;
        }

        //add last vectors for wall
        newLevel.back().push_back(tempX);
        newLevel.back().push_back(tempY);
        newLevel.back().push_back(tempWidth);
        newLevel.back().push_back(tempHeight);

        if(j < randWallNumber){

            //Add new vector ref to matrix
            newLevel.push_back(std::vector<int>());
        }
    }

    level = newLevel;

}

