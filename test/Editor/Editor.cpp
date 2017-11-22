/* Tool for creating levels. Pressing numbers 1-4 creates SFML shapes of different colours, and 5 creates gray static objects (implented here as gray SFML shapes and the actual objects are created in EditorTest.cpp) */

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "fstream"
#include "Box2D/Box2D.h"
#define WIDTH 1000
#define HEIGHT 1000

int main() {

    // Context settings are used here to set the antialiasing level.
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT), "SFML test", sf::Style::Default, settings);

    //The width and height in 10x10 tiles
	int x = WIDTH/10;
	int y = HEIGHT/10;

	int A[y][x]={{0}}; //If 1000x1000 pixels and 100x100 tiles
	
	//Creating an empty level, x tiles wide, y tiles high
	sf::RectangleShape tiles[y][x];
	for(int i = 0; i < y; i++)
	  {
	  for(int j = 0; j < x; j++)
		{
		sf::RectangleShape rectangle(sf::Vector2f(10, 10));	
		rectangle.setPosition(j*10, i*10);
		rectangle.setFillColor(sf::Color::Black);
		tiles[i][j] = rectangle;
		}
	  }

    window.setFramerateLimit(200); // Set fps to be 200.

    b2Vec2 gravity(0.f, 0.0f); // Define gravity, in this case it will be zero.
    b2World world(gravity); // Define world.

    //Writing the matrix to file level1.txt
    std::ofstream f("./Level/level1.txt");

    // Main program loop.
    while (window.isOpen()) {
      world.Step(1/60.f, 8, 3); // This is used to simulate the world.
      //fps = 1.0/clock.getElapsedTime().asSeconds();
      //clock.restart();
        // sf::Event holds information about every event (a key press, mouse movement etc.)
        // which occurs during the program loop.
        sf::Event event;
        // Event loop handles all events which have occurred.
	
	
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:{
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                        case sf::Keyboard::S: //Saves matrix to the file "level1.txt"
				            for(int i = 0; i < y; i++) {
					            for(int j = 0; j < x; j++) {
						            f << A[i][j] << " ";
					            }
				            }
                            break;
                        default:
                            // Empty default case included to stop compiler from giving warnings.
                            break;
                    	}
                    	break;
                    	}
                default:
                    break;
            }
        }

    //Checking which tile the cursor is located at
    sf::Vector2i mpos = sf::Mouse::getPosition (window);
	int x2 = floor(mpos.x/10);
	int y2 = floor(mpos.y/10);

	if (x2 >= 0 && x2<x && y2 >= 0 && y2 < y) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			tiles[y2][x2].setFillColor(sf::Color::Black);
			A[y2][x2] = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
			tiles[y2][x2].setFillColor(sf::Color::Green);
			A[y2][x2] = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			tiles[y2][x2].setFillColor(sf::Color::White);	
			A[y2][x2] = 2;	  
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			tiles[y2][x2].setFillColor(sf::Color::Blue);
			A[y2][x2] = 3;	  
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
		{
			tiles[y2][x2].setFillColor(sf::Color(200,200,200,200));
			A[y2][x2] = 10;  
		}
	}
	
        // Clear previously displayed window, draw the new positions
  
        window.clear();
        
       	for(int i = 0; i < y; i++)
	  	{
	  		for(int j = 0; j < x; j++)
			{
				window.draw(tiles[i][j]);
			}
	  	}
        
        window.display();
    }
    return 0;
}
