#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include "Parser.h"
#include "DFS.h"
#include "SearchTemplates/BFS.h"
#include <sstream>

using namespace std;

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
    BFS search1(pp.nodeMatrix, pp.problem);

    SolutionResponse res = search1.Search(pp.problem, pp.problem.InitialState);
    if(res.ResOutcome() == "failure"){
        cout << "Search failed depth search could not find solution" << endl;
    }
    else{
        string route = "";
        for(Path& p : res.GetActions()){
            switch(p.pathAction) {
                case ActionType::LEFT:
                    route += "LEFT";
                    break;
                case ActionType::RIGHT:
                    route += "RIGHT";
                    break;
                case ActionType::UP:
                    route += "UP";
                    break;
                case ActionType::DOWN:
                    route += "DOWN";
                    break;
                default:
                    break;
            }
            route += ", ";

        }
        cout << "Search successful!" << endl << route << endl;
    }

}