//
// Created by mac on 20/04/17.
//

#include <SFML/Graphics/RectangleShape.hpp>

#include "../sfmlGUI.h"
#include <chrono>
#include "GUIwrapper.h"
#include "../Parser.h"
using namespace std;

GUIwrapper::GUIwrapper(Parser pp, SearchType* search1, int algoChoice ) {



    int width = pp.mapWidth;
    int height = pp.mapHeight;
    int const tileSize = 50;

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
                        trimmedPath = search1->GetTrimmedPath();
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

void GUIwrapper::ChangeColours(vector<sf::RectangleShape>& rectangleVec, int height, int width, int stateNum , SearchType s){
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

void GUIwrapper::ChangeColoursFinalPath(vector<sf::RectangleShape>& rectangleVec, int height, int width, int stateNum, SearchType s){
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

