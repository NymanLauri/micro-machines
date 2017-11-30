/* Tool for creating levels. Pressing numbers 1-4 creates SFML shapes of different colours, and 5 creates gray static objects (implented here as gray SFML shapes and the actual objects are created in EditorTest.cpp) */

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "fstream"
#include "Box2D/Box2D.h"
#include "PhysicsObject.hpp"
#include "Settings.hpp"
#include "Constants.hpp"
#define WIDTH 1800
#define HEIGHT 1000
#define boxwidth 10

int main() {

    // Context settings are used here to set the antialiasing level.
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT), "SFML test", sf::Style::Default, settings);
	Settings s(WIDTH, HEIGHT, 180, 100);
    //The width and height in 10x10 tiles
	int x = s.screenWidth/boxwidth;
	int y = s.screenHeight/boxwidth;

	int A[y][x]; //If 1800x1000 pixels and 180x100 tiles
	std::vector<std::shared_ptr<PhysicsObject>> obstacles;

	//Creating an empty level, x tiles wide, y tiles high
	sf::RectangleShape* tiles[y][x];
	for(int i = 0; i < y; i++)
	  {
	  for(int j = 0; j < x; j++)
		{
		sf::RectangleShape* rectangle = new sf::RectangleShape(sf::Vector2f(boxwidth, boxwidth));	
		rectangle->setPosition((j)*boxwidth, i*boxwidth);
		rectangle->setFillColor(sf::Color(0, 123, 12, 255));
		tiles[i][j] = rectangle;
		A[i][j] = 0;
		}
	  }

    window.setFramerateLimit(200); // Set fps to be 200.

    b2Vec2 gravity(0.f, 0.0f); // Define gravity, in this case it will be zero.
    b2World world(gravity); // Define world.

    //Writing the matrix to file level1.txt
    std::ofstream f("./Level/level1.txt");
    //std::ofstream f("./Level/map1.txt");
    
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
	int x2 = floor(mpos.x/boxwidth);
	int y2 = floor(mpos.y/boxwidth);

	if (x2 >= 0 && x2<x && y2 >= 0 && y2 < y) {
		// Default settings for all static obstacles
            	b2BodyDef bd;
            	bd.position.Set(x2, s.worldHeight - y2);
            	b2FixtureDef fd;
            	fd.friction = 0.3;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			tiles[y2][x2]->setFillColor(sf::Color(0, 123, 12, 255));
			tiles[y2][x2]->setRotation(0);
			A[y2][x2] = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
			tiles[y2][x2]->setFillColor(sf::Color(128, 128, 128, 255));
			tiles[y2][x2]->setRotation(0);
			A[y2][x2] = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		  {
		    tiles[y2][x2]->setFillColor(sf::Color::White);
		    tiles[y2][x2]->setRotation(0);			
		    A[y2][x2] = 2;	  
		  }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		  {
		    tiles[y2][x2]->setFillColor(sf::Color(0, 123, 12, 255));
		    tiles[y2][x2]->setRotation(0);
		    A[y2][x2] = 10;

                    std::vector<std::pair<float,float>> bodyVertices = {
                        std::make_pair(0.0, -1.5),
                        std::make_pair(-1.0, -1.3),
                        std::make_pair(-2.0, -0.0),
                        std::make_pair(-1.4, 0.5),
                        std::make_pair(-0.4, 1.1),
                        std::make_pair(1.0, 1.5),
                        std::make_pair(2.0, 0.9),
                        std::make_pair(1.0, -0.7)
                    };
                    obstacles.push_back(std::make_shared<PhysicsObject>(world, s, bodyVertices, bd, fd, sf::Color(50,25,0,255)));
		  }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
		  {
		    tiles[y2][x2]->setFillColor(sf::Color(0, 123, 12, 255));
		    tiles[y2][x2]->setRotation(0);
		    A[y2][x2] = 11;

                        std::vector<std::pair<float,float>> bodyVertices = {
                            std::make_pair(0.0, -3.0),
                            std::make_pair(-2.0, -2.6),
                            std::make_pair(-4.0, -0.0),
                            std::make_pair(-2.8, 1.0),
                            std::make_pair(-0.8, 2.2),
                            std::make_pair(2.0, 3.0),
                            std::make_pair(4.0, 1.8),
                            std::make_pair(2.0, -1.4)
                        };
                        obstacles.push_back(std::make_shared<PhysicsObject>(world, s, bodyVertices, bd, fd, sf::Color(50,25,0,255)));
                    }

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
		  {
		    tiles[y2][x2]->setFillColor(sf::Color(0, 123, 12, 255));
		    tiles[y2][x2]->setRotation(0);
		    A[y2][x2] = 12;

                        std::vector<std::pair<float,float>> bodyVertices = {
                            std::make_pair(0.0, -3.0),
                            std::make_pair(-2.0, -2.6),
                            std::make_pair(-4.0, -0.0),
                            std::make_pair(-2.8, 1.0),
                            std::make_pair(-0.8, 2.2),
                            std::make_pair(2.0, 3.0),
                            std::make_pair(4.0, 1.8),
                            std::make_pair(2.0, -1.4)
                        };
                        obstacles.push_back(std::make_shared<PhysicsObject>(world, s, bodyVertices, bd, fd, sf::Color(50,25,0,255)));
                    }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
		  {
		    tiles[y2][x2]->setFillColor(sf::Color(0, 123, 12, 255));
		    tiles[y2][x2]->setRotation(0);
		    A[y2][x2] = 13;

                        std::vector<std::pair<float,float>> bodyVertices = {
                            std::make_pair(2.0, -4.0),
                            std::make_pair(0.0, -3.0),
                            std::make_pair(-2.0, -1.4),
                            std::make_pair(-4.0, 0.0),
                            std::make_pair(-4.0, 1.0),
                            std::make_pair(-2.0, 2.0),
                            std::make_pair(1.0, 4.4),
                            std::make_pair(4.0, -1.0)
                        };
                        obstacles.push_back(std::make_shared<PhysicsObject>(world, s, bodyVertices, bd, fd, sf::Color(50,25,0,255)));

                    }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
		  {
		    tiles[y2][x2]->setFillColor(sf::Color(0, 123, 12, 255));
		    tiles[y2][x2]->setRotation(0);
		    A[y2][x2] = 20;

		    auto physObjPtr = std::make_shared<PhysicsObject>(world, s, b2Vec2(20, 1), bd, fd, sf::Color(160,160,160,255));
		    obstacles.push_back(std::make_shared<PhysicsObject>(world, s, b2Vec2(20, 1), bd, fd, sf::Color(160,160,160,255)));
		  }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
		  {
		    tiles[y2][x2]->setFillColor(sf::Color(0, 123, 12, 255));
		    tiles[y2][x2]->setRotation(0);
		    A[y2][x2] = 21;

                        obstacles.push_back(std::make_shared<PhysicsObject>(world, s, b2Vec2(1, 20), bd, fd, sf::Color(160,160,160,255)));
		  }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
		  {
		    tiles[y2][x2]->setFillColor(sf::Color(0, 123, 12, 255));
		    tiles[y2][x2]->setRotation(0);
		    A[y2][x2] = 22;

                        auto physObjPtr = std::make_shared<PhysicsObject>(world, s, b2Vec2(20, 1), bd, fd, sf::Color(160,160,160,255));
                        physObjPtr->getBody()->SetTransform(b2Vec2(x2, s.worldHeight-y2), -45.0 * DEGTORAD);
                        obstacles.push_back(physObjPtr);
		  }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSlash))
		  {
		    tiles[y2][x2]->setFillColor(sf::Color(0, 123, 12, 255));
		    tiles[y2][x2]->setRotation(0);
		    A[y2][x2] = 23;

                        auto physObjPtr = std::make_shared<PhysicsObject>(world, s, b2Vec2(20, 1), bd, fd, sf::Color(160,160,160,255));
                        physObjPtr->getBody()->SetTransform(b2Vec2(x2, s.worldHeight-y2), 45.0 * DEGTORAD);
                        obstacles.push_back(physObjPtr);
		  }

		/*
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
		{
		  if((A[y2+1][x2] == 10 && A[y2][x2-1] == 10)){
		        tiles[y2][x2].setScale(1.5,1.5);
			tiles[y2][x2].setFillColor(sf::Color(200,200,200,200));
			tiles[y2][x2].setRotation(45);
			A[y2][x2] = 20;
		  }
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
		{
      		  if((A[y2-1][x2] == 10 && A[y2][x2+1] == 10)){
		  	tiles[y2][x2].setScale(1.5,1.5);
		        tiles[y2][x2].setFillColor(sf::Color(200,200,200,200));
		        tiles[y2][x2].setRotation(-45);
			A[y2][x2] = 30;  
		  }
		  if((A[y2][x2+1] == 10 && A[y2+1][x2] == 10)){
		  	tiles[y2][x2].setScale(1.5,1.5);
		        tiles[y2][x2].setFillColor(sf::Color(200,200,200,200));
		        tiles[y2][x2].setRotation(-45);
			tiles[y2+1][x2].setRotation(-90);
			A[y2][x2] = 30; 
		}
		}*/
	}
	
        // Clear previously displayed window, draw the new positions
  
        //window.clear(sf::Color::Green);
	window.clear();
        
       	for(int i = 0; i < y; i++)
	  	{
	  		for(int j = 0; j < x; j++)
			{
				window.draw(*tiles[i][j]);
			}
	  	}
        
	for(auto i: obstacles)
		i->drawTo(window,s);

        window.display();
    }
    return 0;
}
