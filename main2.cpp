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

using namespace std;

//Gui functions
void ChangeColoursFinalPath(vector<sf::RectangleShape>& rectangleVec, int height, int width, int stateNum, SearchType s);
void ChangeColours(vector<sf::RectangleShape>& rectangleVec, int height, int width, int stateNum, SearchType s);

//Testing flags
bool IS_GUI = true;
bool TESTING_MODE = false;

int main() {
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
                    r.GetRandomSimulationPaths(10, 10);
                } else if (SIMULATION_NO >= 60) {
                    r.GetRandomSimulationPaths(15, 10);
                } else if (SIMULATION_NO >= 40) {
                    r.GetRandomSimulationPaths(20, 20);
                } else if (SIMULATION_NO >= 20) {
                    r.GetRandomSimulationPaths(13, 13);
                } else {
                    r.GetRandomSimulationPaths(12, 12);
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

        //TODO: Fix up DFS, setup write to csv file class with (initial row followed by data of: nodes explored vs time complexity

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
                cerr << "passed - Node expanded: ";
                cerr << a.GetExploredPath().size() - 1 << endl;
            }
            Greedy g = Greedy(pp.nodeMatrix, pp.problem);
            res = a.Search(pp.problem, pp.problem.InitialState);
            if (res.ResOutcome() != "failure") {
                cerr << "passed - Node expanded: ";
                cerr << a.GetExploredPath().size() - 1 << endl;
            }
            BFS b = BFS(pp.nodeMatrix, pp.problem);
            res = a.Search(pp.problem, pp.problem.InitialState);
            if (res.ResOutcome() != "failure") {
                cerr << "passed - Node expanded: ";
                cerr << a.GetExploredPath().size() - 1 << endl;
            }
            DFS d = DFS(pp.nodeMatrix, pp.problem);
            res = a.Search(pp.problem, pp.problem.InitialState);
            if (res.ResOutcome() != "failure") {
                cerr << "passed - Node expanded: ";
                cerr << a.GetExploredPath().size() - 1 << endl;
            }
        }
    }
    else{
        //Not running tests
    }


    //Read text file
    std::ifstream in("/home/mac/IntroAI/pathFinding/parseFile.txt");

    //Parse file
    //Will be available as NodeMap following this
    pp.ParseFile(in);

    int algoChoice;
    cout << "Select algo: DFS(1), BFS(2), A*(3), Greedy-Best-First(4), Bidirectional(5), MBAstar(6)" << endl;
    SearchType* search1;
    cin >>  algoChoice;
        switch (algoChoice) {
            case 1:
                search1 = static_cast<DFS*>(search1);
                search1 = new DFS(pp.nodeMatrix, pp.problem);
                break;
            case 2:
                search1 = static_cast<BFS*>(search1);
                search1 = new BFS(pp.nodeMatrix, pp.problem);
                break;
            case 3:
                search1 = static_cast<Astar*>(search1);
                search1 = new Astar(pp.nodeMatrix, pp.problem);
                break;
            case 4:
                search1 = static_cast<Greedy*>(search1);
                search1 = new Greedy(pp.nodeMatrix, pp.problem);
                break;
            case 5:
                search1 = static_cast<Bidirectional*>(search1);
                search1 = new Bidirectional(pp.nodeMatrix, pp.problem);
                break;
            case 6:
                search1 = static_cast<MBAstar*>(search1);
                search1 = new MBAstar(pp.nodeMatrix, pp.problem);
                break;
            default:
                cerr << "Error in choice" << endl;
                break;
    }

    SolutionResponse res;

    // ---------------------------------
    //To be moved up to testing area
    // ---------------------------------
    if(TESTING_MODE) {
        //repeated simulations in testing mode
        for(int i = 1; i <= SIMULATION_NO; i++) {
            //Clock start to measure search run time
            clock_t t;    t = clock();

            //TODO: time-out response for DFS
            res = search1->Search(pp.problem, pp.problem.InitialState);
            t = clock() - t;
            printf ("It took %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);

            //Clear all paths etc.
            search1->Reset();
        }
    }
    else{
        res = search1->Search(pp.problem, pp.problem.InitialState);
    }

    if(res.ResOutcome() == "failure"){
        cout << "Search failed depth search could not find solution" << endl;
        return 1;
    }
    else{

        //No path available for Bidirectional
        if(algoChoice == 5) {
            search1 = static_cast<Bidirectional *>(search1);
            cout << "Search successful!" << endl;
            cout << "Nodes explored: " << search1->GetExploredPath().size() + search1->GetExploredPath().size() << endl;
        }
        else if(algoChoice == 6){
            search1 = static_cast<MBAstar*>(search1);
            cout << "Search successful!" << endl;
            cout << "Nodes explored: " << search1->GetExploredPath().size() << endl;
        }
        else {
            string route = "";
            for (Path *p : res.GetActions()) {
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
                route += ", ";

                cout << "Search successful!" << endl << route << endl;
                cout << "Best path: " << search1->GetTrimmedPath().size() << endl;
                cout << "Nodes explored: " << search1->GetExploredPath().size() << endl;
            }
        }

    }

    // ----------------------- GUI Code ---------------------------//
    // ------------------------------------------------------------//


    if(!IS_GUI){
        cout << endl << "**Gui not enabled**" << endl;
        return 0;
    }


    int width = pp.mapWidth;
    int height = pp.mapHeight;
    int const tileSize = 50;


    std::cout << height << std::endl << width << std::endl;



    std::vector<sf::RectangleShape> rectangleVector = std::vector<sf::RectangleShape>();

    for(int i = 0; i < height; i ++){
        for(int j = 0; j < width; j++){
            //Ad shape
            sf::RectangleShape rectangle(sf::Vector2f(tileSize, tileSize));
            rectangle.setFillColor(sf::Color::White);
            rectangle.setOutlineThickness(2);
            rectangle.setOutlineColor(sf::Color::Black);
            rectangle.setPosition(j * tileSize, i * tileSize);
            rectangleVector.push_back(rectangle);
        }
    }


    //SearchType& s = static_cast<SearchType&>(*search1);

    ChangeColours(rectangleVector, height, width, 0, *search1);

    //Set window
    sf::RenderWindow window(sf::VideoMode(width*tileSize, height*tileSize), "SFML works!");

    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    std::chrono::time_point<std::chrono::system_clock> foo = now + std::chrono::milliseconds(1000);
    std::chrono::milliseconds sec(100);

    int stateRender = 0;
    long stateMax = search1->GetStringPath().size()-1;
    bool renderTrimmedPath = false;
    bool keepState = false;
    long exploredPathRenderCount = search1->GetStringPath().size();

    while (window.isOpen())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
            return 0;
        }


        std::clock_t newClock = std::clock();
        //Timer check every 1000 milliseconds
        auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - foo).count();
        if(diff > 0){

            foo = std::chrono::system_clock::now() + std::chrono::milliseconds(100);

            if(!keepState) {
                stateRender++;
            }

            if(stateRender < exploredPathRenderCount){
                ChangeColours(rectangleVector, height, width, stateRender, *search1);
            } //if greedy type we don't trim the path, it only ever follows one path
            else {
                //Above code will now not execute
                exploredPathRenderCount = 0;

                if(!renderTrimmedPath) {

                    std::vector<Path*> trimmedPath;

                    //Chose bidrectional
                    if(algoChoice == 5){
//                        //Static cast to get spcific function form child class
//                        Bidirectional* biSearch = static_cast<Bidirectional*>(search1);
//                        trimmedPath = biSearch->TrimPath(pp.problem, search1->GetExploredPath());
//                        auto trimmedPathFromGoal = biSearch->TrimPath(pp.problem, biSearch->GetExploredPathFromGoal());
//                        trimmedPath = biSearch->CombineTrimmedPaths(trimmedPath, trimmedPathFromGoal);
                          stateRender = search1->GetTrimmedPath().size()-1;
                        keepState = true;
                        break;
                    }
                    else{
                        trimmedPath = search1->TrimPath(pp.problem, search1->GetExploredPath());
                    }

                    //re-fill path strings for last rendering

                    //Set up new render
                    stateRender = 0;

                    search1->GetStringPath().clear();
                    //Overrides string path with trimmed version for last rneder
                    for (auto& p : trimmedPath) {

                        search1->RenderCurrentMap(p->pathNode, pp.problem);
                    }
                    renderTrimmedPath = true;
                }

                ChangeColoursFinalPath(rectangleVector, height, width, stateRender, *search1);
                if(stateRender == search1->GetTrimmedPath().size()-1){
                    keepState = true;
                }
            }

        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        for(int i = 0; i < rectangleVector.size(); i++) {
            window.draw(rectangleVector[i]);
        }

        window.display();
    }
}

void ChangeColours(vector<sf::RectangleShape>& rectangleVec, int height, int width, int stateNum , SearchType s){
    int index = 0;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){

            //cerr << s.GetStringPath()[stateNum][index] << endl;
            if(s.GetStringPath()[stateNum][index] == "S"){
                rectangleVec[index].setFillColor(sf::Color::Blue);
            }
            else if(s.GetStringPath()[stateNum][index] == "1"){
                rectangleVec[index].setFillColor(sf::Color::White);
            }
            else if(s.GetStringPath()[stateNum][index] == "W"){
                rectangleVec[index].setFillColor(sf::Color::Black);
            }
            else if(s.GetStringPath()[stateNum][index] == "H"){
                rectangleVec[index].setFillColor(sf::Color::Red);
            }
            else if(s.GetStringPath()[stateNum][index] == "X"){
                rectangleVec[index].setFillColor(sf::Color::Green);
            }
            index++;
        }
    }
}

void ChangeColoursFinalPath(vector<sf::RectangleShape>& rectangleVec, int height, int width, int stateNum, SearchType s){
    int index = 0;
    for(int i = 0; i < height; i++){

        if(s.GetTrimmedPath().size()-1 == 0){
            break;
        }

        for(int j = 0; j < width; j++){

            //cerr << s.GetStringPath()[stateNum][index] << endl;
            if(s.GetStringPath()[stateNum][index] == "S"){
                rectangleVec[index].setFillColor(sf::Color::Blue);
            }
            else if(s.GetStringPath()[stateNum][index] == "1"){
                rectangleVec[index].setFillColor(sf::Color::White);
            }
            else if(s.GetStringPath()[stateNum][index] == "W"){
                rectangleVec[index].setFillColor(sf::Color::Black);
            }
            else if(s.GetStringPath()[stateNum][index] == "H"){
                rectangleVec[index].setFillColor(sf::Color::Yellow);
            }
            else if(s.GetStringPath()[stateNum][index] == "X"){
                rectangleVec[index].setFillColor(sf::Color::Green);
            }

            index++;
        }
    }
}

