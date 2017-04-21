//
// Created by mac on 9/04/17.
//

#include <iostream>
#include <chrono>
#include <thread>
#include "sfmlGUI.h"
#include "Parser.h"
#include "SearchTemplates/Astar.h"
#include "DFS.h"
#include "SearchTemplates/BFS.h"
#include "SearchTemplates/Greedy.h"
#include "RandomPaths.h"
#include "SearchTemplates/Bidirectional.h"
#include "SearchTemplates/MBAstar.h"
#include "SearchTemplates/GUIwrapper.h"
#include <fstream>

using namespace std;

//Gui functions
void ChangeColoursFinalPath(vector<sf::RectangleShape>& rectangleVec, int height, int width, int stateNum, SearchType s);
void ChangeColours(vector<sf::RectangleShape>& rectangleVec, int height, int width, int stateNum, SearchType s);

//Testing flags
bool IS_GUI = false;
bool TESTING_MODE = false;

int main(int argc, char *argv[]) {


    string searchType = "";
    string fileRead = "";

    if ( argc > 2)
    {
        fileRead = argv[1];
        searchType = argv[2];
        string temp = argv[3];
        if(temp == "GUI"){
            IS_GUI = true;
        }
    }
    else if ( argc < 2 )
    {
        cerr << "Missing argument!" << endl;
        cerr << "Please provide arg1 textfile and arg2 search method" << endl;
        cerr << "optional arg3=\"GUI\" for GUI representaiotn" << endl;
        return 1;
    }
    else{
        fileRead = argv[1];
        searchType = argv[2];
    }


    int SIMULATION_NO = 100;
    vector<vector<vector<int>>> listLevels = vector<vector<vector<int>>>();
    //Setup parsing object
    Parser pp;

    //Loop through newly random levels using A* to test if there is a solution

    RandomPaths r = RandomPaths();

    bool finishableLevel = false;

    if(TESTING_MODE) {
        for (; SIMULATION_NO > 0; SIMULATION_NO--) {

            while (!finishableLevel) {
                //Different height width limits in random level creating
                if (SIMULATION_NO >= 80) {
                    r.GetRandomSimulationPaths(8, 8);
                } else if (SIMULATION_NO >= 60) {
                    r.GetRandomSimulationPaths(12, 12);
                } else if (SIMULATION_NO >= 40) {
                    r.GetRandomSimulationPaths(15, 15);
                } else if (SIMULATION_NO >= 20) {
                    r.GetRandomSimulationPaths(17, 17);
                } else {
                    r.GetRandomSimulationPaths(20, 20);
                }

                //Create new map vector with parser function
                auto newMap = r.GetNewPath();
                pp.AddMapVector(newMap);

                //Run A* to test if it works
                //If it works we will use it
                Astar a = Astar(pp.nodeMatrix, pp.problem);
                auto res = a.Search(pp.problem, pp.problem.InitialState);
                if (res.ResOutcome() != "failure") {
                    finishableLevel = true;
                    listLevels.push_back(newMap);
                }
            }
            finishableLevel = false;
        }

        // -------------------------------------- //
        // Run all simulation levels on each Algo //
        // -------------------------------------- //
        std::ofstream dataFile;
        dataFile.open("/home/mac/IntroAI/pathFinding/output.txt");

        //For csv file format
        dataFile << "Test, " << "Algo, " << "Pass, " << "NodesExp, " << "Shortest " << endl;

        //Ready for looping again
        SIMULATION_NO = 100;
        SolutionResponse res;

        for (; SIMULATION_NO > 0; SIMULATION_NO--) {

            if (listLevels.empty()) {
                break;
            } else {
                //Create map vector
                pp.AddMapVector(listLevels[listLevels.size() - 1]);
                listLevels.pop_back();
            }

            Astar a = Astar(pp.nodeMatrix, pp.problem);
            res = a.Search(pp.problem, pp.problem.InitialState);
            if (res.ResOutcome() != "failure") {
                dataFile << SIMULATION_NO << ", ";
                dataFile << "Astar, " << "passed, " << a.GetExploredPath().size() << ", ";
                dataFile << a.GetTrimmedPath().size() << endl;
            }
            else{
                dataFile << SIMULATION_NO << ", ";
                dataFile << "Astar, " << "failed, " << a.GetExploredPath().size() << ", ";
                dataFile << 0 << endl;
            }

            Greedy g = Greedy(pp.nodeMatrix, pp.problem);
            res = g.Search(pp.problem, pp.problem.InitialState);
            if (res.ResOutcome() != "failure") {
                dataFile << SIMULATION_NO << ", ";
                dataFile << "Greedy, " << "passed, " << g.GetExploredPath().size() << ", ";
                dataFile << g.GetTrimmedPath().size() << endl;
            }
            else{
                dataFile << SIMULATION_NO << ", ";
                dataFile << "Greedy, " << "failed, " << g.GetExploredPath().size() << ", ";
                dataFile << 0 << endl;
            }

            BFS b = BFS(pp.nodeMatrix, pp.problem);
            res = b.Search(pp.problem, pp.problem.InitialState);
            if (res.ResOutcome() != "failure") {
                dataFile << SIMULATION_NO << ", ";
                dataFile << "BFS, " << "passed, " << b.GetExploredPath().size() << ", ";
                dataFile << b.GetTrimmedPath().size() << endl;
            }
            else{
                dataFile << SIMULATION_NO << ", ";
                dataFile << "BFS, " << "failed, " << b.GetExploredPath().size() << ", ";
                dataFile << 0 << endl;
            }

            DFS d = DFS(pp.nodeMatrix, pp.problem);
            res = d.Search(pp.problem, pp.problem.InitialState);
            if (res.ResOutcome() != "failure") {
                dataFile << SIMULATION_NO << ", ";
                dataFile << "DFS, " << "passed, " << d.GetExploredPath().size() << ", ";
                dataFile << d.GetTrimmedPath().size() << endl;
            }else{
                dataFile << SIMULATION_NO << ", ";
                dataFile << "DFS, " << "failed, " << d.GetExploredPath().size() << ", ";
                dataFile << 0 << endl;
            }

            Bidirectional bi = Bidirectional(pp.nodeMatrix, pp.problem);
            res = bi.Search(pp.problem, pp.problem.InitialState);
            if (res.ResOutcome() != "failure") {
                dataFile << SIMULATION_NO << ", ";
                dataFile << "BI-DIR, " << "passed, " << bi.GetExploredPath().size() << ", ";
                dataFile << 0 << endl;
            }else{
                dataFile << SIMULATION_NO << ", ";
                dataFile << "BI-DIR, " << "failed, " << bi.GetExploredPath().size() << ", ";
                dataFile << 0 << endl;
            }

            MBAstar mba = MBAstar(pp.nodeMatrix, pp.problem);
            res = mba.Search(pp.problem, pp.problem.InitialState);
            if (res.ResOutcome() != "failure") {
                dataFile << SIMULATION_NO << ", ";
                dataFile << "MBAstar, " << "passed, " << mba.GetExploredPath().size() << ", ";
                dataFile << 0 << endl;
            }else{
                dataFile << SIMULATION_NO << ", ";
                dataFile << "MBAstar, " << "failed, " << mba.GetExploredPath().size() << ", ";
                dataFile << 0 << endl;
            }

            if(SIMULATION_NO % 20 == 0) {
                SearchType *s;
                s = &a;
                GUIwrapper(pp, s, 3);
            }
        }
        dataFile.close();

    }
    else{
        //Not running tests
    }

    //Read text file
    std::ifstream in(fileRead);
    //Parse file
    //Will be available as NodeMap following this
    pp.ParseFile(in);


    //from previous interface, but number important for GUI
    int algoChoice;

    //cout << "Select algo: DFS(1), BFS(2), A*(3), Greedy-Best-First(4), Bidirectional(5), MBAstar(6)" << endl;
    SearchType* search1;

    if( searchType == "DFS"){
        algoChoice = 1;
        search1 = static_cast<DFS*>(search1);
        search1 = new DFS(pp.nodeMatrix, pp.problem);
    }
    else if ( searchType == "BFS") {
        algoChoice = 2;
        search1 = static_cast<BFS *>(search1);
        search1 = new BFS(pp.nodeMatrix, pp.problem);
    }
    else if (searchType == "A*"){
        algoChoice = 3;
        search1 = static_cast<Astar*>(search1);
        search1 = new Astar(pp.nodeMatrix, pp.problem);
    }
    else if(searchType == "Greedy"){
        algoChoice = 4;
        search1 = static_cast<Greedy*>(search1);
        search1 = new Greedy(pp.nodeMatrix, pp.problem);
    }
    else if(searchType == "Bi-directional"){
        algoChoice = 5;
        search1 = static_cast<Bidirectional*>(search1);
        search1 = new Bidirectional(pp.nodeMatrix, pp.problem);
    }
    else if(searchType == "MBA*") {
        algoChoice = 6;
        search1 = static_cast<MBAstar *>(search1);
        search1 = new MBAstar(pp.nodeMatrix, pp.problem);
    }
    else{
        cerr << "Incorrect search name - please try the following: DFS, BFS, A*, Greedy, Bi-directional, MBA*" << endl;
        return 1;
    }

    SolutionResponse res;

    // ---------------------------------
    //To be moved up to testing area
    // ---------------------------------
    if(TESTING_MODE) {
        //repeated simulations in testing mode
//        for(int i = 1; i <= SIMULATION_NO; i++) {
//            //Clock start to measure search run time
//            clock_t t;    t = clock();
//

//            res = search1->Search(pp.problem, pp.problem.InitialState);
//            t = clock() - t;
//            printf ("It took %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
//
//            //Clear all paths etc.
//            search1->Reset();
//        }
    }
    else{
        res = search1->Search(pp.problem, pp.problem.InitialState);
    }


    cout << fileRead << " " << searchType << " ";

    //If failure, simply provide outcome + nodes expanded
    if(res.ResOutcome() == "failure"){
        //No path available for Bidirectional
        if(algoChoice == 5) {
            search1 = static_cast<Bidirectional*>(search1);
            cout <<  search1->GetExploredPath().size() + search1->GetExploredPath().size() << endl;
            cout << "No Solution Found " << endl;
        }
        else
        {
            cout << search1->GetExploredPath().size() << endl;
            cout << "No Solution Found " << endl;
        }
        return 1;

    }
    else{

        //No path available for Bidirectional
        if(algoChoice == 5) {
            search1 = static_cast<Bidirectional*>(search1);
            cout << "successful " << endl;
            cout << search1->GetExploredPath().size() + search1->GetExploredPath().size() << endl;
        }
        else if(algoChoice == 6){
            search1 = static_cast<MBAstar*>(search1);
            cout << "successful " << endl;
            cout << search1->GetExploredPath().size() << endl;
        }
        else {
            string route = "";
            for (Path* p : res.GetActions()) {
                switch (p->pathAction) {
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
                route += "; ";
            }
            cout << search1->GetExploredPath().size() << endl << route << endl;
        }

    }

    // ----------------------- GUI Code ---------------------------//
    // ------------------------------------------------------------//


    if(!IS_GUI){
        cout << endl << "**Gui not enabled**" << endl;
        return 0;
    }
    else{
        GUIwrapper(pp, search1, algoChoice);
    }

}



