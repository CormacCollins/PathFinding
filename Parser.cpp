//
// Created by mac on 13/03/17.
//

#include "Parser.h"
#include <iostream>
#include <string>
#include <sstream>
#include <tuple>
#include <limits>
#include <algorithm>
#include <cstring>

void Parser::ParseFile(std::ifstream& file) {
    const int MAX_NUMBERS_PARSED = 4;
    std::string line;

    if(!file){
        std::cerr << "File could not be parsed please check it is formatted correctly";
    }

    std::cout << "Parsing File" << std::endl;
    //While file still good keep reading
    while(file.good()){

        //Begin getting lines from file
        while(getline(file, line)) {

            //loop through lines for special characters and parse data
            //once data reaches its end we break to next new line
            for (int i = 0; i < line.size();) {
                if (line[i] == '[' || line[i] == '(') {
                    int j = i + 1;

                    //size of 2nd dimension vector will be maximum 4 currently - we know the data will be like this
                    std::string tempValue[MAX_NUMBERS_PARSED];
                    //string val for parsing entire strings of number for each integer before adding to a vector as an int
                    int stringVal = 0;
                    //If char corresponds to a number we sum them or if a comma we still keep reading data
                    while ((line[j]) >= '0' && line[j] <= '9' || line[j] == ',') {
                        if (line[j] == ',') {
                            stringVal++;
                        } else {
                            //Get string value
                            tempValue[stringVal] += line[j];
                        }
                        j++;
                    }

                    //Add new vector ref to matrix
                    dataMatrix.push_back(std::vector<int>());

                    //get numbers and add them to vector
                    for (int x = 0; x < stringVal + 1; x++) {
                        int val = std::stoi(tempValue[x]);
                        //Add all values to 2nd dimension vector
                        dataMatrix.back().push_back(val);
                    }
                }
                break;
            }
        }
    }
    file.close();

    std::cout << "File Parse Completed successfully" << std::endl;

    std::cout << "Creating Node Matrix For DepthSearch...." << std::endl;
    //Called here so the user knows they can access the node-map created
    //Don't need multiple calls to setup
    SetupProblem();
    std::cout << "Node Matrix complete" << std::endl;

}

void Parser::SetupProblem() {

    int MAP_ROWS;
    int MAP_COLUMNS;
    int INITIAL_STATE[2];
    int GOAL_STATE[2];
    std::vector<std::tuple<int,int>> WALL_LIST;
    Problem newProblem;
    std::vector<std::vector<Node*>> newMatrix;

    //Taking all wall values (after first 3 rows) and creating a list of each individual cartesian coordinate
    for(int i = 0; i < dataMatrix.size(); i++){

        if(i <= 2){
            continue;
        }

        int x =dataMatrix[i][2];
        int y = dataMatrix[i][3];

        //Add all wall points to wall list
        for(int rangeY = 0; rangeY < y; rangeY++){
            for(int rangeX = 0; rangeX < x ; rangeX++){
                WALL_LIST.push_back(std::make_tuple(dataMatrix[i][0]+rangeX, dataMatrix[i][1]+rangeY));
                std::cout << dataMatrix[i][0]+rangeX << ", " << dataMatrix[i][1]+rangeY << std::endl;
            }
        }
    }

    //first row contains size of map
    if(!std::isnan(dataMatrix[0][0]) && !std::isnan(dataMatrix[0][1])){
        MAP_ROWS = dataMatrix[0][0];
        MAP_COLUMNS = dataMatrix[0][1];

        //For visualization access
        mapHeight = MAP_ROWS;
        mapWidth = MAP_COLUMNS;
    } else {
        std::cerr << "Data not formatted correctly - no map size";
        exit(1);
    }
    //Get initial state
    if(!std::isnan(dataMatrix[1][0]) && !std::isnan(dataMatrix[1][1])){
        INITIAL_STATE[0] =  dataMatrix[1][0];
        INITIAL_STATE[1] = dataMatrix[1][1];
    } else {
        std::cerr << "Data not formatted correctly - No Initial State value";
        exit(1);
    }
    //Get goal state
    if(!std::isnan(dataMatrix[2][0]) && !std::isnan(dataMatrix[2][1])){
        GOAL_STATE[0] =  dataMatrix[2][0];
        GOAL_STATE[1] = dataMatrix[2][1];
    } else {
        std::cerr << "Data not formatted correctly - No Goals State value";
        exit(1);
    }


    int tempGoalNodePos[] = {0, 0};
    int tempStartNodePos[] = {0, 0};
    //Create a Node Ptr for all data positions on map
    for(int i = 0; i < MAP_ROWS; i++){

//        if(std::isnan(dataMatrix[i][0])){
//            std::cerr << "Could not continue creating Node Map"
//                      << "Row " << i << " contained no elements";
//            break;
//        }

        //for creating vector of pointers
        std::vector<Node*> row;
        for(int j = 0; j < MAP_COLUMNS; j++){

            bool addWall = false;
            //Loop all wall locations, set flag to true if this coordinate is a wall
            for(auto tup : WALL_LIST)
            {
                auto t = std::make_tuple(j,i);
                if(tup == t ){
                    addWall = true;
                }
            }

            Node* n;

            // Add the initial and goal states
            // Node* added to problem, we now have a pointer reference
            // to the 'State' not just the coordinate
            if(INITIAL_STATE[0] == j && INITIAL_STATE[1] == i) {
                n = new Node();
                newProblem.InitialState = n;
                row.push_back(n);
                tempStartNodePos[0] = i;
                tempStartNodePos[1] = j;
            }
            else if(GOAL_STATE[0] == j && GOAL_STATE[1] == i) {
                n = new Node();
                newProblem.GoalState = n;
                row.push_back(n);
                tempGoalNodePos[0] = i;
                tempGoalNodePos[1] = j;
            }
            else if(addWall)
            {
                //Walls can be null values - not traversable
                addWall = false;
                row.push_back(NULL);
            }
            else{
                n = new Node();
                row.push_back(n);
            }
        }
        //Add new row to matrix full of ptr
        newMatrix.push_back(row);
    }

    // ------------------------------------------------
    // Need to work out heuristic distance (manhattan)
    // ------------------------------------------------



    int distBetweenGoalAndStart =
            (tempGoalNodePos[0] + tempGoalNodePos[1])
            - (tempStartNodePos[0] + tempStartNodePos[1]);

    //If neg number make it pos - goal is always a pos number distance from start
    distBetweenGoalAndStart = distBetweenGoalAndStart < 0
                              ? distBetweenGoalAndStart * -1 : distBetweenGoalAndStart;

    //0 from goal
    newMatrix[tempGoalNodePos[0]][tempGoalNodePos[1]]->goalCost = 0;

    //Calculated dist from goal
    newMatrix[tempStartNodePos[0]][tempStartNodePos[1]]->goalCost = distBetweenGoalAndStart;

    int zero = 0;
    //Add pathcosts to nodes for informed search
    for(int i = 0; i < MAP_ROWS; i++){
        for(int j = 0; j < MAP_COLUMNS; j++){

            //Add goalPathCOst
            if(newMatrix[i][j] != NULL)
            {
                auto a = std::pow((float)(i - tempGoalNodePos[0]) , 2);
                auto b = std::pow((float)(j - tempGoalNodePos[1]), 2);

                auto dist =  std::sqrt( (a) + (b));



                //Make pos value
                if(dist < 0){
                    dist = dist * -1;
                }

                if(dist == 0)
                    zero++;

                //node is now specific distance value from goal (can't be negative)
                newMatrix[i][j]->goalCost = dist;

            }
        }
    }



    //Assign to class properties
    problem = newProblem;
    nodeMatrix = newMatrix;

}

