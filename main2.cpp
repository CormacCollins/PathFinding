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
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

void ChangeColoursFinalPath(vector<sf::RectangleShape>& rectangleVec, int height, int width, int stateNum, SearchType s);
void ChangeColours(vector<sf::RectangleShape>& rectangleVec, int height, int width, int stateNum, SearchType s);

int main() {

    //Setup parsing object
    Parser pp;

    // Read text file
    std::ifstream in("/home/mac/IntroAI/pathFinding/parseFile.txt");

    //Parse file
    //Will be available as NodeMap following this
    pp.ParseFile(in);

    for(int i = 0; i < pp.dataMatrix.size(); i++){
        for(int j = 0; j < pp.dataMatrix[i].size(); j++){
            std::cout << pp.dataMatrix[i][j] << ",";
        }
        std::cout << std::endl;
    }


    int algoChoice;
    cout << "Select algo: DFS(1), BFS(2), A*(3)" << endl;
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
            default:
                cerr << "Error in choice" << endl;
                break;
    }

    //Pass in node map and problem (as defined by the parsing result)
    //Astar search1(pp.nodeMatrix, pp.problem);

    SolutionResponse res = search1->Search(pp.problem, pp.problem.InitialState);
    if(res.ResOutcome() == "failure"){
        cout << "Search failed depth search could not find solution" << endl;
        return 1;
    }
    else{
        string route = "";
        for(Path* p : res.GetActions()){
            switch(p->pathAction) {
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
        cout << "Lowest path: " << search1->GetTrimmedPath().size()-1 << endl;
        cout << "Nodes explored: " << search1->GetExploredPath().size()-1 << endl;
    }

    // ----------------------- GUI Code ---------------------------//
    // ------------------------------------------------------------//


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


    SearchType& s = static_cast<SearchType&>(*search1);

    ChangeColours(rectangleVector, height, width, 0, s);

    //Set window
    sf::RenderWindow window(sf::VideoMode(width*tileSize, height*tileSize), "SFML works!");

    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    std::chrono::time_point<std::chrono::system_clock> foo = now + std::chrono::milliseconds(1000);
    std::chrono::milliseconds sec(100);


    int stateRender = 0;
    long stateMax = search1->GetStringPath().size()-1;
    bool renderTrimmedPath = false;
    bool keepState = false;
    long exploredPathRenderCount = s.GetStringPath().size();

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
                ChangeColours(rectangleVector, height, width, stateRender, s);
            }
            else{
                //Above code will now not execute
                exploredPathRenderCount = 0;

                auto trimmedPath = s.TrimPath(pp.problem);
                //re-fill path strings for last rendering
                if(!renderTrimmedPath) {
                    //Set up new render
                    stateRender = 0;

                    s.GetStringPath().clear();
                    //Overrides string path with trimmed version for last rneder
                    for (auto& p : trimmedPath) {

                        search1->RenderCurrentMap(p->pathNode, pp.problem);
                    }
                    renderTrimmedPath = true;
                }

                ChangeColoursFinalPath(rectangleVector, height, width, stateRender, s);

                if(stateRender == trimmedPath.size()-1){
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

