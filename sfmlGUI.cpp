//
// Created by mac on 9/04/17.
//

#include "sfmlGUI.h"

void sfmlGUI::Init(){
    //Create link to program in path finder and have evenet handler

    int width, height = 0;
    int const tileSize = 50;

    width = fwidth;
    height = fheight;


    std::cout << height << std::endl << width << std::endl;

    sf::RenderWindow window(sf::VideoMode(width*tileSize, height*tileSize), "SFML works!");

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


    while (window.isOpen())
    {
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

sfmlGUI::sfmlGUI() {

}
