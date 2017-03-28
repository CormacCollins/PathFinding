#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include "Parser.h"
#include "DFS.h"
#include <sstream>

int main() {

    //Setup parsing object
    Parser pp;

    // Read text file
    std::ifstream in("/home/mac/DSP/AIintro/parseFile.txt");

    //Parse file
    //Will be available as NodeMap following this
    pp.ParseFile(in);

    for(int i = 0; i < pp.dataMatrix.size(); i++){
        for(int j = 0; j < pp.dataMatrix[i].size(); j++){
            std::cout << pp.dataMatrix[i][j] << ",";
        }
        std::cout << std::endl;
    }


    //Pass in node map and problem (as defined by the parsing result)
    DFS search1(pp.nodeMatrix, pp.problem);


//    //Parser test
//    int i = 0;
//    for(int j = 0; j < pp.nodeMatrix.size(); j++) {
//        for (Node *a : pp.nodeMatrix[j]) {
//            std::stringstream ss;
//
//            if (i > 10) {
//                i = 0;
//                ss << std::endl;
//            }
//
//            if (a == pp.problem.InitialState){
//                ss << "#" << " | ";
//            }
//            else if (a == pp.problem.GoalState){
//                ss << "X" << " | ";
//            }
//            else if (a == NULL){
//                ss << "W" << " | ";
//            }
//            else {
//                ss << "0" << " | ";
//            }
//
//            i++;
//            std::cout << ss.str();
//        }
//    }

    search1.DepthSearch(pp.problem, pp.problem.InitialState);
}