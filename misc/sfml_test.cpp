/* This is a short SFML test file for messing around, not intended to be used in the
 * project.
 * Compiled by typing:
 * g++ -g -Wall -o test sfml_test.cpp -lsfml-graphics -lsfml-window -lsfml-system -IBox2D -L<path-to-libBox2D.a> -lBox2D -std=c++11
 * For example, <path-to-libBox2D.a> could be /home/henry/micro-machines-5/misc
 */

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#define PI 3.14159265

int main() {
    // Context settings are used here to set the antialiasing level.
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    // Create 1000x1000 pixel window titled "SFML test" using above context settings.
    sf::RenderWindow window(sf::VideoMode(1000,1000), "SFML test", sf::Style::Default, settings);
    // Create a "circle of radius 20 with 3 corners", i.e., a triangle shape.
    sf::CircleShape shape(20.f, 3);
    // Transfer the origin of the triangle (the point around which the triangle rotates)
    // to the center of the triangle. (The default would be the top left corner of the shape.)
    shape.setOrigin(shape.getRadius(),shape.getRadius());
    // Move the triangle to the center coordinates of the window.
    shape.setPosition(500,500);
    shape.setFillColor(sf::Color::Green);
    window.setFramerateLimit(200); // Set fps to be 200.

    const float SCALE = 30.f;


    sf::Texture boxTexture; // This is a texture used to draw a Box2D-object to the window.
    boxTexture.loadFromFile("Enemy.png");
    b2Vec2 gravity(0.f, 0.0f); // Define gravity, in this case it will be zero.
    b2World world(gravity); // Define world.
    b2BodyDef myBodyDef; // Define body.
    myBodyDef.type = b2_dynamicBody; // Define the body to be dynamic, that is, we can apply force to it.
    myBodyDef.position.Set(10,5); // The initial position of the body.
    myBodyDef.angle = 0; // The initial angle of the body.
    b2Body* dynamicBody = world.CreateBody(&myBodyDef); // Here we create the body.
    b2PolygonShape boxShape;
    boxShape.SetAsBox(10,10); // Define a shape that represents a box.
    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    boxFixtureDef.friction = 2.0f;
    dynamicBody->CreateFixture(&boxFixtureDef);

    // Initialize a clock for measuring fps.
    //sf::Clock clock;
    //float fps;

    // Main program loop.
    while (window.isOpen()) {
      world.Step(1/60.f, 8, 3); // This is used to simulate the world.
      //fps = 1.0/clock.getElapsedTime().asSeconds();
      //clock.restart();
        // sf::Event holds information about every event (a key press, mouse movement etc.)
        // which occurs during the program loop.
        sf::Event event;
        // Event loop handles all events which have occurred.
	sf::Sprite sprite; // Create a sprite.
	sprite.setTexture(boxTexture);
	sprite.setOrigin(1.f,1.f);
	sprite.setPosition(SCALE*dynamicBody->GetPosition().x, SCALE*dynamicBody->GetPosition().y); // Set the position of the sprite to be the position of the Box2D rectangle.
	
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                // Key presses are handled here, excluding movement keys (see below).    
                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                        case sf::Keyboard::I:
                            // Print information to console for debugging purposes when I is pressed.
                            //std::cout << "fps: " << fps << std::endl;
                            std::cout << "rot: " << shape.getRotation() << std::endl;
                            std::cout << "x: " << shape.getPosition().x << ", y: " << shape.getPosition().y << std::endl;
                        default:
                            // Empty default case included to stop compiler from giving warnings.
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
        // Because of reasons explained in the SFML documentation ("smooth motion"), movement
        // keys are handled in the main program loop instead of the event loop, by checking
        // which keys are pressed at any given moment. The new position of the triangle is
        // calculated using sine and cosine from the cmath header.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            // Only allow rotations when up or down is pressed at the same time, since a
            // car can only turn when it is moving.
            shape.move(sin(shape.getRotation()*PI/180),-cos(shape.getRotation()*PI/180));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	      {
		shape.rotate(-0.5);
	      }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	      {
		shape.rotate(0.5);
	      }
        }   
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            shape.move(-0.5*sin(shape.getRotation()*PI/180),0.5*cos(shape.getRotation()*PI/180));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	      {
		shape.rotate(-0.5);
	      }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	      {
		shape.rotate(0.5);
	      }
        }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
	    dynamicBody->ApplyForce(b2Vec2(0,-50), dynamicBody->GetWorldCenter(), 1); // Apply force to the body.
        }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
	    dynamicBody->ApplyForce(b2Vec2(0,50), dynamicBody->GetWorldCenter(), 1);
        }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
	  dynamicBody->ApplyForce(b2Vec2(-50,0), dynamicBody->GetWorldCenter(), 1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
	  dynamicBody->ApplyForce(b2Vec2(50,0), dynamicBody->GetWorldCenter(), 1);
	}
        // Clear previously displayed window, draw the new position of the triangle to
        // the window and display the newly drawn window.
        window.clear();
	window.draw(sprite);
        window.draw(shape);
        window.display();
    }
    return 0;
}
